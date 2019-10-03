#pragma once

#include "HttpMessageBuilder.h"
#include "HttpResponse.h"

namespace HttpServerNS {
	class HttpResponseBuilder : public HttpMessageBuilder
	{
	private:
		int statusCode;
	public:
		HttpResponseBuilder();
		~HttpResponseBuilder();

		void setStatusCode(int statusCode) { this->statusCode = statusCode; }
		int getStatusCode() { return statusCode; }

		HttpResponse* build() { return new HttpResponse(statusCode, getHeaders(), getMessageBody()); }
	};

}
