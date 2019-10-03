#pragma once
#include <string>
#include <sstream>
#include "HttpHeader.h"
#include "HttpMessage.h"

namespace HttpServerNS {
	class HttpResponse : public HttpMessage
	{
	private:
		int statusCode;
	protected:
		bool isMessageHeader(const HttpHeader& header, const HttpHeaderCategory category) const override {
			if (category == RESPONSE)
				return true;
			return false;
		}
	public:
		HttpResponse(const int statusCode, const std::map<std::string, HttpHeader>& headers, const std::string& messageBody);
		~HttpResponse() {};

		int getStatusCode() const { return statusCode; }
		std::map<std::string, HttpHeader> getResponseHeaders() const { return getMessageHeaders(); }

		std::string getHttpStartLine() const override {
			std::stringstream s = std::stringstream();
			s << "HTTP/1.1 " << getStatusCode() << " OK";
			return s.str();
		}
		std::string getHttpMessage() const override;
	};

}
