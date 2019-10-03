#pragma once
#include "HttpHeader.h"
namespace HttpServerNS {

	enum HttpHeaderCategory {
		GENERAL,
		REQUEST,
		RESPONSE,
		ENTITY
	};

	class HttpHeaderCategorizer
	{
	private:
		static const char* const CONTENT_TYPE;
	public:
		HttpHeaderCategorizer();
		~HttpHeaderCategorizer();

		HttpHeaderCategory categorize(const HttpHeader& header) const;
		bool isGeneralHeader(const HttpHeader& header) const;
		bool isRequestHeader(const HttpHeader& header) const;
		bool isResponseHeader(const HttpHeader& header) const;
		bool isEntityHeader(const HttpHeader& header) const;

	};
}
