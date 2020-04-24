#include "connection.h"

#include <chrono>
#include <iostream>

#include "util.h"

namespace ntq {

	Connection::ResponseSender::ResponseSender(Connection& self) : self_(self) {
	}

	void Connection::ResponseSender::operator()(http::response<http::string_body>&& resp) {
		auto aresp = std::make_shared<http::response<http::string_body> >(std::move(resp));
		self_.response_ = aresp;
		http::async_write(self_.stream_, *aresp, beast::bind_front_handler(&Connection::OnWrite, self_.shared_from_this(), aresp->need_eof()));
	}

	Connection::Connection(tcp::socket&& socket, RequestHandler& request_handler)
		: stream_(std::move(socket)),
		request_handler_(request_handler),
		response_sender_(*this) {
	}


	Connection::~Connection() {
	}

	tcp::socket& Connection::socket() {
		return stream_.socket();
	}

	void Connection::Start() {
		auto self = shared_from_this();
		net::dispatch(stream_.get_executor(), beast::bind_front_handler(&Connection::DoRead, shared_from_this()));
	}

	void Connection::DoRead() {
		request_ = {};
		stream_.expires_after(std::chrono::seconds(30));
		http::async_read(stream_, buffer_, request_, beast::bind_front_handler(&Connection::OnRead, shared_from_this()));
	}

	void Connection::OnRead(const beast::error_code& ec, std::size_t bytes_transferred) {
		boost::ignore_unused(bytes_transferred);
		// This means they closed the connection
		if (ec == http::error::end_of_stream)
			return DoClose();

		if (ec)
			return PrintError(ec, "read");

		// Send the response
		request_handler_.HandleRequest(request_, response_sender_);
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



