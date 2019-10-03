#include "HttpMessage.h"
#include <iostream>


namespace HttpServerNS {

	//publics
	HttpMessage::HttpMessage(const std::map<std::string, HttpHeader>& headers, const std::string& messageBody) {
		categorizer = HttpHeaderCategorizer();
		this->headers = headers;
		this->messageBody = messageBody;
		std::map<std::string, HttpHeader>::const_iterator headersIt;
		for (headersIt = headers.begin(); headersIt != headers.end(); headersIt++) {
			HttpHeader header = headersIt->second;
			HttpHeaderCategory category = categorizer.categorize(header);
			if (category == GENERAL) {
				generalHeaders.insert(std::pair<std::string, HttpHeader>(header.getName(), header));
			}
			if (this->isMessageHeader(header, category)) {
				messageHeaders.insert(std::pair<std::string, HttpHeader>(header.getName(), header));
			}
			if (category == ENTITY) {
				entityHeaders.insert(std::pair<std::string, HttpHeader>(header.getName(), header));
			}
		}
	}
	HttpMessage::HttpMessage()
	{
		headers = std::map<std::string, HttpHeader>();
	}


	HttpMessage::~HttpMessage()
	{
	}

	bool HttpMessage::containsHeader(const HttpHeader& header) const {
		return containsHeader(header.getName());
	}

	bool HttpMessage::containsHeader(const std::string& name) const {
		return headers.find(name) != headers.end();
	}

	HttpHeader& HttpMessage::getHeader(const std::string& name) {
		return headers.find(name)->second;
	}
	HttpHeader HttpMessage::getHeader(const std::string& name) const {
		return headers.find(name)->second;
	}
	std::string HttpMessage::getHeaderValue(const std::string& name) const {
		return getHeader(name).getValue();
	}


	// globals
	std::ostream& operator<<(std::ostream &o, const HttpMessage* m) {
		return o << m->getHttpMessage();
	}
}
