#include "io_context_pool.h"


namespace ntq {

	IoContextPool::IoContextPool(std::size_t pool_size/* = 10*/)
		: next_io_context_(0) {
		std::size_t size = pool_size;
		if (size <= 0 || size > 128)
			size = 8;
		for (std::size_t i = 0; i < size; i++) {
			IoContextPtr io_context = boost::make_shared<net::io_context>();
			io_contexts_.push_back(io_context);
			works_.push_back(net::make_work_guard(*io_context));
		}
	}

	void IoContextPool::Start() {
		std::vector<boost::shared_ptr<boost::thread> > threads;
		for (std::size_t i = 0; i < io_contexts_.size(); i++) {
			boost::shared_ptr<boost::thread> thread =
				boost::make_shared<boost::thread>(boost::bind(&boost::asio::io_context::run, io_contexts_[i]));
			threads.push_back(thread);
		}

		for (std::size_t i = 0; i < threads.size(); ++i) {
			threads[i]->join();
		}
	}

	void IoContextPool::Stop() {
		for (std::size_t i = 0; i < io_contexts_.size(); i++) {
			io_contexts_[i]->stop();
		}
	}

	net::io_context& IoContextPool::get() {
		net::io_context& io_context = *io_contexts_[next_io_context_];
		++next_io_context_;
		if (next_io_context_ == io_contexts_.size())
			next_io_context_ = 0;
		return io_context;
	}

	net::io_context& IoContextPool::first() {
		return *io_contexts_[0];
	}

} // namespace ntq
