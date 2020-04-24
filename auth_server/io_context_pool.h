#pragma once


#include <list>
#include <vector>

#include "boost.h"


namespace ntq {

	class IoContextPool 
		: private boost::noncopyable {
		typedef boost::shared_ptr<net::io_context> IoContextPtr;
		typedef net::executor_work_guard<net::io_context::executor_type> IoWork;
	public:
		explicit IoContextPool(std::size_t pool_size = 10);

		void Start();
		void Stop();

		net::io_context& get();
		net::io_context& first();

	private:
		std::vector<IoContextPtr> io_contexts_;
		std::list<IoWork> works_;
		std::size_t next_io_context_;
	};

} // namespace ntq

