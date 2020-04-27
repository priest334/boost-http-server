#pragma once

#include <string>

namespace ntq {
	class Request {
	public:
		virtual std::string path() const = 0;
		virtual int method() const = 0;
		virtual std::string body() const = 0;
		virtual std::string header(const std::string& name) const = 0;
		virtual std::string query(const std::string& key) const = 0;
		virtual bool HasHeader(const std::string& name) const = 0;
		virtual bool HasQuery(const std::string& key) const = 0;

		// Respone
		virtual void set_status_code(int code) = 0;
		virtual void set_header(const std::string& name, const std::string& value) = 0;
		virtual void append_header(const std::string& name, const std::string& value) = 0;
		virtual void send_content(const std::string& content) = 0;
	};

} // namespace ntq

