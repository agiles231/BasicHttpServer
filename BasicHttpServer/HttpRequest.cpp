#include "HttpRequest.h"
#include <sstream>


namespace HttpServerNS {

	HttpRequest::HttpRequest(const std::string& method, const std::string& path, const std::map<std::string, HttpHeader>& headers, const std::string& messageBody)
		: HttpMessage(headers, messageBody)
	{
		this->method = method;
		this->path = path;
	}


	HttpRequest::~HttpRequest()
	{
	}

	std::string HttpRequest::getHttpMessage() const {
		std::stringstream s = std::stringstream();
		s << method << " " << path << " HTTP/1.1\r\n";
		s << getHttpHeaders() << "\r\n";
		s << getMessageBody();
		return s.str();
	}
}
