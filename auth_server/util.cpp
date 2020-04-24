#include "util.h"

#include <iostream>
#include <locale>
#include "boost.h"

namespace ntq {
	void ShowTimestamp(const char* what) {
		boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
		boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
		facet->format("%Y-%m-%dT%H:%M:%S.%f");
		std::ostringstream ss;
		ss.imbue(std::locale(std::locale::classic(), facet));
		ss << now;
		std::cout << what << ": " << ss.str() << std::endl;
	}
} // namespace ntq


