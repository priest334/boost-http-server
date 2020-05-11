#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

namespace ntq {
	class RequestWrapper;

	typedef enum _HttpMethod {
		HttpMethodUnknown = 0,
		HttpMethodGet = 2,
		HttpMethodHead = 3,
		HttpMethodPost = 4
	} HttpMethod;

	class RouteKey {
	public:
		RouteKey();
		explicit RouteKey(const std::string& path, int method = HttpMethodGet);
		virtual ~RouteKey();
		friend bool operator<(const ntq::RouteKey& l, const ntq::RouteKey& r);
		int method() const;
		std::string const path() const;
	private:
		int method_;
		std::string path_;
	};


	
	class RouteHandler 
		: public boost::enable_shared_from_this<RouteHandler> {
	public:
		virtual RouteKey route_key() = 0;
		virtual int Process(RequestWrapper* request) = 0;
		virtual bool IsEnableProcessHead();
		virtual int ProcessHead(RequestWrapper* request);
	};

	typedef boost::shared_ptr<RouteHandler> RouteHandlerPtr;
} // namespace ntq



