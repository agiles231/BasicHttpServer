#include "HttpHeader.h"


namespace HttpServerNS {

	HttpHeader::HttpHeader(std::string name, std::string value)
	{
		this->name = name;
		this->value = value;
	}


	HttpHeader::~HttpHeader()
	{
	}
}
