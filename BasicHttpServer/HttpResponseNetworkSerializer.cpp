#include "HttpResponseNetworkSerializer.h"


namespace HttpServerNS {

	HttpResponseNetworkSerializer::HttpResponseNetworkSerializer()
	{
	}


	HttpResponseNetworkSerializer::~HttpResponseNetworkSerializer()
	{
	}

	void HttpResponseNetworkSerializer::serialize(const HttpResponse& response, std::ostream& o) {
		o << "HTTP/1.1 " << response.getStatusCode() << " OK" << std::endl;
	}
}
