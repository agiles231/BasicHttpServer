#pragma once
#include "HttpMessage.h"
#include <string>

namespace HttpServerNS {
	class HttpRequest : public HttpMessage
	{
	private:
		std::string method;
		std::string path;
		std::map<std::string, HttpHeader> requestHeaders;
	protected:
		bool isMessageHeader(const HttpHeader& header, const HttpHeaderCategory category) const override {
			if (category == REQUEST)
				return true;
			return false;
		}
	public:
		HttpRequest(const std::string& method, const std::string& path, const std::map<std::string, HttpHeader>& headers, const std::string& messageBody);
		~HttpRequest();

		std::string getMethod() const { return method; }
		std::string getPath() const { return path; }
		std::map<std::string, HttpHeader> getRequestHeaders() const { return getMessageHeaders(); }

		std::string getHttpStartLine() const override {
			return method + " " + path + " HTTP/1.1\r\n";
		}
		std::string getHttpMessage() const override;
	};

}
