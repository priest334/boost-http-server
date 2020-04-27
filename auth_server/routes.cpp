#include "routes.h"
#include "server.h"
#include "hello.h"

namespace ntq {

	void InitRoutes(HttpServer* server) {
		server->request_handler().AddRouteHandler(boost::make_shared<RouteHello>());
	}

} // namespace ntq

