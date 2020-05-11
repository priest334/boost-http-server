#pragma once

#include "boost.h"

namespace ntq {
	class Connection;


	class RequestWrapper 
		: public boost::enable_shared_from_this<RequestWrapper>, 
		private boost::noncopyable {
	public:
		RequestWrapper(boost::shared_ptr<ntq::Connection> connection);
		http::request<http::string_body>& request() const;
		std::string path() const;
		int method() const;
		std::string body() const;
		std::string header(const std::string& name) const;
		std::string query(const std::string& key) const;
		bool HasHeader(const std::string& name) const;
		bool HasQuery(const std::string& key) const;

		void set_status_code(int code);
		void set_header(const std::string& name, const std::string& value);
		void append_header(const std::string& name, const std::string& value);
		void send_content(const std::string& content);
	private:
		boost::shared_ptr<Connection> connection_;
		http::response<http::string_body> response_;
		std::string path_;
		std::string query_string_;
	};


} // namespace ntq


