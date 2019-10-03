#include "HttpResponse.h"
#include "HttpHeaderCategorizer.h"

namespace HttpServerNS {


	HttpResponse::HttpResponse(const int statusCode, const std::map<std::string, HttpHeader>& headers, const std::string& messageBody) : HttpMessage(headers, messageBody)
	{
		this->statusCode = statusCode;
	}

	std::string HttpResponse::getHttpMessage() const {
		std::stringstream s = std::stringstream();
		s << "HTTP/1.1 " << getStatusCode() << " OK";
		s << getHttpHeaders();
		s << "\r\n";
		s << getMessageBody();
		return s.str();
	}
}
