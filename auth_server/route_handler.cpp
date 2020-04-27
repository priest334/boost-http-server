#include "route_handler.h"

namespace ntq {

	RouteKey::RouteKey() : method_(HttpMethodUnknown), path_("") {
	}

	RouteKey::RouteKey(const std::string& path, int method/* = HttpMethodGet*/)
		: method_(method), path_(path) {
	}

	RouteKey::~RouteKey() {
	}

	bool operator<(const ntq::RouteKey& l, const ntq::RouteKey& r) {
		if (l.path_ < r.path_)
			return true;
		else if (l.path_ > r.path_)
			return false;
		else
			return l.method_ < r.method_;
	}


} // namespace ntq



