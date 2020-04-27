#include "hello.h"
#include "request_wrapper.h"

namespace ntq {

	RouteKey RouteHello::route_key() {
		return RouteKey("/hello", HttpMethodGet);
	}

	int RouteHello::Process(RequestWrapper* request) {
		request->set_status_code(200);
		request->send_content("OK");
		return 0;
	}

} // namespace ntq


