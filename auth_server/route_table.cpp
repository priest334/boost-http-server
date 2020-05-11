#include "route_table.h"

#include "boost.h"
#include "route_handler.h"
#include "request_wrapper.h"

namespace ntq {
	void RouteTable::Add(const RouteKey& route_key, RouteHandlerPtr route_handler) {
		route_handler_table_[route_key] = route_handler;
		if (route_handler->IsEnableProcessHead()) {
			route_handler_table_[RouteKey(route_key.path(), HttpMethodHead)] = route_handler;
		}
	}

	RouteHandlerPtr RouteTable::Get(const RouteKey& route_key) const {
		auto iter = route_handler_table_.find(route_key);
		if (iter != route_handler_table_.end()) {
			return iter->second;
		}
		return nullptr;
	}




} // namespace ntq



