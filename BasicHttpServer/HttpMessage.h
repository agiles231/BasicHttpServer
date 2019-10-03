#pragma once
#include <map>
#include <string>
#include <sstream>
#include "HttpHeader.h"
#include "HttpHeaderCategorizer.h"

namespace HttpServerNS {


	class HttpMessage
	{
	private:

		std::map<std::string, HttpHeader> headers;
		std::map<std::string, HttpHeader> generalHeaders;
		std::map<std::string, HttpHeader> messageHeaders;
		std::map<std::string, HttpHeader> entityHeaders;
		std::string messageBody;

		/*
		* Merges value from @other into @header
		*/
	protected:
		HttpHeaderCategorizer categorizer;
		virtual bool isMessageHeader(const HttpHeader& header, const HttpHeaderCategory category) const = 0 { return false; };
	public:
		HttpMessage(const std::map<std::string, HttpHeader>& headers, const std::string& messageBody);
		HttpMessage();
		~HttpMessage();


		bool containsHeader(const HttpHeader& header) const;
		bool containsHeader(const std::string& name) const;
	
		HttpHeader& getHeader(const std::string& name);
		HttpHeader getHeader(const std::string& name) const;
		std::string getHeaderValue(const std::string& name) const;

		std::string getMessageBody() const { return messageBody; }
		virtual std::string getHttpMessage() const = 0;

		virtual std::string getHttpStartLine() const = 0;

		std::string getHttpHeaders() const {
			std::stringstream s = std::stringstream();
			for (auto headersIt = generalHeaders.cbegin(); headersIt != generalHeaders.end(); headersIt++) {
				HttpHeader header = headersIt->second;
				s << header.getName() << ": " << header.getValue() << "\r\n";
			}
			for (auto headersIt = messageHeaders.cbegin(); headersIt != messageHeaders.end(); headersIt++) {
				HttpHeader header = headersIt->second;
				s << header.getName() << ": " << header.getValue() << "\r\n";
			}
			for (auto headersIt = entityHeaders.cbegin(); headersIt != entityHeaders.end(); headersIt++) {
				HttpHeader header = headersIt->second;
				s << header.getName() << ": " << header.getValue() << "\r\n";
			}
			return s.str();
		}

		std::map<std::string, HttpHeader> getHeaders() const { return headers; }
		std::map<std::string, HttpHeader> getGeneralHeaders() const { return generalHeaders; }
		std::map<std::string, HttpHeader> getMessageHeaders() const { return messageHeaders; }
		std::map<std::string, HttpHeader> getEntityHeaders() const { return entityHeaders; }

	};
	std::ostream& operator<<(std::ostream &o, const HttpMessage* m);

}

