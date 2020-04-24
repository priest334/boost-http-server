#pragma once

#include "boost.h"

namespace ntq {
	
	class RequestHandler : 
		private boost::noncopyable {
	public:
		template <class ResponseSender>
		void HandleRequest(const http::request<http::string_body>& request, ResponseSender&& dosend) {
			http::response<http::string_body> response{ http::status::ok, request.version() };
			response.set(http::field::server, "server/0.1");
			response.content_length(0);
			response.keep_alive(request.keep_alive());
			//response.keep_alive(false);
			response.body() = "";

			dosend(std::move(response));
		}

	private:

	};
}



