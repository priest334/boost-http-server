#include "request_wrapper.h"
#include "connection.h"

namespace ntq {
	RequestWrapper::RequestWrapper(boost::shared_ptr<ntq::Connection> connection) : connection_(connection) {
	}

	http::request<http::string_body>& RequestWrapper::request() const{
		return connection_->request();
	}

	std::string RequestWrapper::path() const {
		return request().target().to_string();
	}

	int RequestWrapper::method() const {
		return (int)request().method();
	}

	std::string RequestWrapper::body() const {
		return request().body();
	}

	std::string RequestWrapper::header(const std::string& name) const {
		return "";
	}

	std::string RequestWrapper::query(const std::string& key) const {
		return "";
	}

	bool RequestWrapper::HasHeader(const std::string& name) const {
		return false;
	}

	bool RequestWrapper::HasQuery(const std::string& key) const {
		return false;
	}

	void RequestWrapper::set_status_code(int code) {
		response_.result(http::status(code));
		response_.keep_alive(request().keep_alive());
	}

	void RequestWrapper::set_header(const std::string& name, const std::string& value) {
	}

	void RequestWrapper::append_header(const std::string& name, const std::string& value) {
	}

	void RequestWrapper::send_content(const std::string& content) {
		response_.body() = content;
		response_.content_length(content.length());

		connection_->SendResponse(std::move(response_));
	}

} // namespace ntq


