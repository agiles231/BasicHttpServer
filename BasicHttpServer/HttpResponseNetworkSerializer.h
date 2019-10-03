#pragma once
#include <ostream>
#include "HttpResponse.h"

namespace HttpServerNS {
	class HttpResponseNetworkSerializer
	{
	public:
		HttpResponseNetworkSerializer();
		~HttpResponseNetworkSerializer();

		void serialize(const HttpResponse& response, std::ostream& o);
	};

}
