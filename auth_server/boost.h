#pragma once

#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/beast.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>


namespace asio = boost::asio;
namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

