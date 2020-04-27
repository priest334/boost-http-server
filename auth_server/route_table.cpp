#include "route_table.h"

namespace ntq {


	void RouteTable::Add(const RouteKey& route_key, RouteHandlerPtr&& route_handler) {
		route_handler_table_[route_key] = std::move(route_handler);
	}

	RouteHandlerPtr RouteTable::Get(const RouteKey& route_key) const {
		auto iter = route_handler_table_.find(route_key);
		if (iter != route_handler_table_.end()) {
			return iter->second;
		}
		return nullptr;
	}




} // namespace ntq



