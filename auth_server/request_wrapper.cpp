#include "request_wrapper.h"
#include "connection.h"

namespace ntq {
	RequestWrapper::RequestWrapper(boost::shared_ptr<ntq::Connection> connection) : connection_(connection) {
		set_header("Server", "x/1.0");
		std::string uri = request().target().to_string();
		std::string::size_type fq = uri.find('?');
		path_ = uri.substr(0, fq);
		if (fq != std::string::npos) {
			query_string_ = uri.substr(fq + 1);
		}
	}

	http::request<http::string_body>& RequestWrapper::request() const{
		return connection_->request();
	}

	std::string RequestWrapper::path() const {
		return path_;
	}

	int RequestWrapper::method() const {
		return (int)request().method();
	}

	std::string RequestWrapper::body() const {
		return request().body();
	}

	std::string RequestWrapper::header(const std::string& name) const {
		auto iter = request().find(name);
		if (iter != request().end()) {
			return iter->value().to_string();
		}
		return "";
	}

	std::string RequestWrapper::query(const std::string& key) const {
		if (!query_string_.empty()) {
			std::string qkey = key + '=';
			size_t fp = query_string_.find(qkey);
			if (fp != std::string::npos) {
				size_t vp = fp + qkey.length();
				size_t fp1 = query_string_.find('&', fp);
				return (fp1 != std::string::npos) ? query_string_.substr(vp, fp1 - vp) : query_string_.substr(vp);
			}
		}
		return "";
	}

	bool RequestWrapper::HasHeader(const std::string& name) const {
		auto iter = request().find(name);
		return iter != request().end();
	}

	bool RequestWrapper::HasQuery(const std::string& key) const {
		if (!query_string_.empty()) {
			std::string qkey = key + '=';
			size_t fp = query_string_.find(qkey);
			return (fp != std::string::npos);
		}
		return false;
	}

	void RequestWrapper::set_status_code(int code) {
		response_.result(http::status(code));
		response_.keep_alive(request().keep_alive());
	}

	void RequestWrapper::set_header(const std::string& name, const std::string& value) {
		response_.set(name, value);
	}

	void RequestWrapper::append_header(const std::string& name, const std::string& value) {
		response_.insert(name, value);
	}

	void RequestWrapper::send_content(const std::string& content) {
		response_.body() = content;
		response_.content_length(content.length());

		connection_->SendResponse(std::move(response_));
	}

} // namespace ntq


