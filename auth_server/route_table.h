#pragma once

#include <map>
#include <string>
#include "boost.h"
#include "route_handler.h"

namespace ntq {

	class RouteTable : private boost::noncopyable {		
	public:
		void Add(const RouteKey& route_key, RouteHandlerPtr&& route_handler);
		RouteHandlerPtr Get(const RouteKey& route_key) const;
	private:
		std::map<RouteKey, RouteHandlerPtr> route_handler_table_;
	};

} // namespace ntq



