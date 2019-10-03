#include "HttpHeader.h"
#include "HttpMessageBuilder.h"


namespace HttpServerNS {

	// constructors
	HttpMessageBuilder::HttpMessageBuilder()
	{
	}


	HttpMessageBuilder::~HttpMessageBuilder()
	{
	}

	// publics

	bool HttpMessageBuilder::containsHeader(const HttpHeader& header) const {
		return containsHeader(header.getName());
	}

	bool HttpMessageBuilder::containsHeader(const std::string& name) const {
		return headers.find(name) != headers.end();
	}

	void HttpMessageBuilder::addHeader(const HttpHeader& header) {
		if (containsHeader(header)) {
			mergeHeader(getHeader(header.getName()), header);
		} else {
			headers.insert(std::pair<std::string, HttpHeader>(header.getName(), header));
		}
	}
	void HttpMessageBuilder::addHeader(const std::string& name, const std::string& value) {
		addHeader(HttpHeader(name, value));
	}
	bool HttpMessageBuilder::removeHeader(const HttpHeader& header) {
		return removeHeader(header.getName());
	}
	bool HttpMessageBuilder::removeHeader(const std::string& name) {
		std::map<std::string, HttpHeader>::iterator headersIt;
		for (headersIt = headers.begin(); headersIt != headers.end(); headersIt++) {
			if (headersIt->first == name) {
				headers.erase(headersIt->first);
				return true;
			}
		}
		return false;
	}

	void HttpMessageBuilder::setHeader(const HttpHeader& header) {
		std::map<std::string, HttpHeader>::iterator it = headers.find(header.getName());
		if (it != headers.end()) {
			headers.erase(it);
		}
		headers.insert(std::pair<std::string, HttpHeader>(header.getName(), header));

	}
	void HttpMessageBuilder::setHeader(const std::string& name, const std::string& value) {
		setHeader(HttpHeader(name, value));
	}
	HttpHeader& HttpMessageBuilder::getHeader(const std::string& name) {
		return headers.find(name)->second;
	}
	HttpHeader HttpMessageBuilder::getHeader(const std::string& name) const {
		return headers.find(name)->second;
	}
	std::string HttpMessageBuilder::getHeaderValue(const std::string& name) const {
		return getHeader(name).getValue();
	}

	//privates
	void HttpMessageBuilder::mergeHeader(HttpHeader& header, HttpHeader other) {
		header.addValue(other.getValue());
	}
}
