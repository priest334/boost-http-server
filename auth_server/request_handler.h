#pragma once


#include "boost.h"
#include "request_wrapper.h"
#include "route_table.h"

namespace ntq {

	class RequestHandler : 
		private boost::noncopyable {
	public:	
		void AddRouteHandler(RouteHandlerPtr route_handler);
		void Process(boost::shared_ptr<RequestWrapper> request);

	private:
		RouteTable route_table_;
	};
}



