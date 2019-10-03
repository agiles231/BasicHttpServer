#pragma once
#include "HttpHeader.h"
#include "HttpMessage.h"
#include "HttpHeaderCategorizer.h"
#include <map>

namespace HttpServerNS {
	class HttpMessageBuilder
	{
	private:

		std::map<std::string, HttpHeader> headers;
		std::map<std::string, HttpHeader> generalHeaders;
		std::map<std::string, HttpHeader> messageHeaders;
		std::map<std::string, HttpHeader> entityHeaders;

		std::string messageBody;

		void mergeHeader(HttpHeader& header, HttpHeader other);

	public:
		HttpMessageBuilder();
		~HttpMessageBuilder();

		bool containsHeader(const HttpHeader& header) const;
		bool containsHeader(const std::string& name) const;
		void addHeader(const HttpHeader& header);
		void addHeader(const std::string& name, const std::string& value);
		bool removeHeader(const HttpHeader& header);
		bool removeHeader(const std::string& name);

		void setHeader(const HttpHeader& header);
		void setHeader(const std::string& name, const std::string& value);
		HttpHeader& getHeader(const std::string& name);
		HttpHeader getHeader(const std::string& name) const;
		std::string getHeaderValue(const std::string& name) const;

		std::map<std::string, HttpHeader> getHeaders() const { return headers; }

		void setMessageBody(std::string messageBody) { this->messageBody = messageBody; }
		std::string getMessageBody() const { return messageBody; }
	};

}
