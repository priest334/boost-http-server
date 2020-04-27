#pragma once

#include "route_handler.h"

namespace ntq {
	class RouteHello : public RouteHandler {
	public:
		RouteKey route_key();
		int Process(RequestWrapper* request);
	};

} // namespace ntq


