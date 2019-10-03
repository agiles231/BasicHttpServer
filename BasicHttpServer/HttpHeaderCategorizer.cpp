#include "HttpHeaderCategorizer.h"

namespace HttpServerNS {

	const char* const HttpHeaderCategorizer::CONTENT_TYPE = "Content-Type";

	HttpHeaderCategorizer::HttpHeaderCategorizer()
	{
	}


	HttpHeaderCategorizer::~HttpHeaderCategorizer()
	{
	}
	HttpHeaderCategory HttpHeaderCategorizer::categorize(const HttpHeader& header) const {
		std::string name = header.getName();
		HttpHeaderCategory category = GENERAL;
		if (isGeneralHeader(header)) {
			category = GENERAL;
		}
		else if (isRequestHeader(header)) {
			category = REQUEST;
		}
		else if (isResponseHeader(header)) {
			category = RESPONSE;
		}
		else {
			category = ENTITY;
		}
		return category;
	}

	bool HttpHeaderCategorizer::isGeneralHeader(const HttpHeader& header) const {
		return true;
	}
	bool HttpHeaderCategorizer::isRequestHeader(const HttpHeader& header) const {
		return true;
	}
	bool HttpHeaderCategorizer::isResponseHeader(const HttpHeader& header) const {
		return true;
	}
	bool HttpHeaderCategorizer::isEntityHeader(const HttpHeader& header) const {
		return !(isGeneralHeader(header) || isRequestHeader(header) || isResponseHeader(header));
	}
}
