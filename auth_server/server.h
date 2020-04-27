#pragma once

#include <string>
#include "boost.h"
#include "connection.h"
#include "request_handler.h"
#include "io_context_pool.h"

namespace ntq {

	class HttpServer 
		: private boost::noncopyable {
	public:
		explicit HttpServer(std::size_t thread_pool_size);
		~HttpServer();

		void Start(const std::string& address, const std::string& port);
		RequestHandler& request_handler();

	private:
		void StartAccept();

		IoContextPool io_context_pool_;
		net::signal_set signals_;
		tcp::acceptor acceptor_;
		ConnectionPtr new_connection_;
		RequestHandler request_handler_;
	};

} // namespace ntp


