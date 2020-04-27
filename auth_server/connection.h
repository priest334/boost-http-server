#pragma once


#include "boost.h"
#include "request_handler.h"

namespace ntq {

	class Connection :
		public boost::enable_shared_from_this<Connection>,
		private boost::noncopyable {
	public:
		Connection(tcp::socket&& socket, RequestHandler& request_handler);
		~Connection();

		tcp::socket& socket();
		http::request<http::string_body>& request();

		void Start();
		void SendResponse(http::response<http::string_body>&& resp);

	private:
		void DoRead();
		void OnRead(const beast::error_code& ec, std::size_t bytes_transferred);
		void OnWrite(bool close, const beast::error_code& ec, std::size_t bytes_transferred);
		void DoClose();

		beast::tcp_stream stream_;
		beast::flat_buffer buffer_;
		http::request<http::string_body> request_;
		boost::shared_ptr<void> response_;
		RequestHandler& request_handler_;
	};


	typedef boost::shared_ptr<Connection> ConnectionPtr;
} // namespace ntq

