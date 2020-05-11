#include "request_handler.h"
#include "boost.h"
#include "connection.h"


namespace ntq {
	void RequestHandler::AddRouteHandler(RouteHandlerPtr route_handler) {
		route_table_.Add(route_handler->route_key(), route_handler);
	}

	void RequestHandler::Process(boost::shared_ptr<RequestWrapper> request) {
		std::string path = request->path();
		int method = request->method();
		RouteKey route_key(path, method);
		RouteHandlerPtr handler = route_table_.Get(route_key);
		if (handler) {
			if (method==HttpMethodHead && handler->IsEnableProcessHead()) {
				handler->ProcessHead(request.get());
			} else {
				handler->Process(request.get());
			}
		} else {
			request->set_status_code(404);
			request->send_content("Not Found");
		}
	}
}


