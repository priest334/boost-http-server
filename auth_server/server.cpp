#include "server.h"

#include <iostream>
#include <vector>
#include <locale>

#include "util.h"


namespace ntq {
	HttpServer::HttpServer(std::size_t thread_pool_size)
		: io_context_pool_(thread_pool_size),
		signals_(io_context_pool_.first()),
		acceptor_(io_context_pool_.first()),
		new_connection_() {
	}

	HttpServer::~HttpServer() {
		io_context_pool_.Stop();
	}

	void HttpServer::Start(const std::string& address, const std::string& port) {
		signals_.add(SIGINT);
		signals_.add(SIGTERM);
		signals_.add(SIGABRT);
#if defined(SIGQUIT)
		signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
		signals_.async_wait([this](const boost::system::error_code&, int){
			io_context_pool_.Stop();
		});

		// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
		tcp::resolver resolver(io_context_pool_.first());
		tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();

		StartAccept();

		io_context_pool_.Start();
	}


	void HttpServer::StartAccept() {
		acceptor_.async_accept(io_context_pool_.get(), [this](const boost::system::error_code& ec, tcp::socket socket) {
			if (ec) {
				PrintError(ec, "accept");
			} else {
				new_connection_.reset(new Connection(std::move(socket), request_handler_));
				new_connection_->Start();
			}
			// Accept another connection
			StartAccept();
		});
	}



} // namespace ntq


