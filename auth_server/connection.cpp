#include "connection.h"

#include <chrono>
#include <iostream>
#include "util.h"

namespace ntq {

	Connection::Connection(tcp::socket&& socket, RequestHandler& request_handler)
		: stream_(std::move(socket)),
		request_handler_(request_handler) {
	}


	Connection::~Connection() {
	}

	tcp::socket& Connection::socket() {
		return stream_.socket();
	}

	http::request<http::string_body>& Connection::request() {
		return request_;
	}

	void Connection::Start() {
		auto self = shared_from_this();
		net::dispatch(stream_.get_executor(), beast::bind_front_handler(&Connection::DoRead, shared_from_this()));
	}

	void Connection::SendResponse(http::response<http::string_body>&& resp) {
		auto aresp = boost::make_shared<http::response<http::string_body> >(std::move(resp));
		response_ = aresp;
		http::async_write(stream_, *aresp, beast::bind_front_handler(&Connection::OnWrite, shared_from_this(), aresp->need_eof()));
	}

	void Connection::DoRead() {
		request_ = {};
		stream_.expires_after(std::chrono::seconds(30));
		http::async_read(stream_, buffer_, request_, beast::bind_front_handler(&Connection::OnRead, shared_from_this()));
	}

	void Connection::OnRead(const beast::error_code& ec, std::size_t bytes_transferred) {
		boost::ignore_unused(bytes_transferred);
		if (ec == http::error::end_of_stream)
			return DoClose();

		if (ec)
			return PrintError(ec, "read");

		auto request = boost::make_shared<RequestWrapper>(shared_from_this());
		request_handler_.Process(request);
	}

	void Connection::OnWrite(bool close, const beast::error_code& ec, std::size_t bytes_transferred) {
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return PrintError(ec, "write");

		if (close) {
			return DoClose();
		}
	}

	void Connection::DoClose() {
		beast::error_code ec;
		stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
	}
} // namespace ntq



