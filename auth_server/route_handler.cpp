#include "route_handler.h"
#include "request_wrapper.h"

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

	int RouteKey::method() const {
		return method_;
	}

	std::string const RouteKey::path() const {
		return path_;
	}

	bool RouteHandler::IsEnableProcessHead() {
		return true;
	}

	int RouteHandler::ProcessHead(RequestWrapper* request) {
		request->set_status_code(200);
		request->send_content("");
		return 0;
	}


} // namespace ntq



