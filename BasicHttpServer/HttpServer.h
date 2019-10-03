#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include <exception>
#include <thread>
#include <map>
#include <iostream>
#include <WinSock2.h>
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpResponseBuilder.h"

namespace HttpServerNS {

	class HttpServer
	{
	protected:
		std::string ipAddress;
		bool running;

		int maxThreadCount;
		int currentThreadCount;

		virtual void handleRequest(HttpRequest* request, SOCKET clientConnection) = 0;
	public:
		HttpServer(std::string ipAddress, int port);
		virtual ~HttpServer();

		bool isRunning() const { return running; };

		int getMaxThreadCount() const { return maxThreadCount; }
		int getCurrentThreadCount() const { return currentThreadCount; }

		virtual void start() = 0;
		virtual void shutdown() = 0;
		virtual void restart() { if (isRunning()) shutdown(); start(); }

		/*template<typename R, std::enable_if<std::is_base_of<HttpResponse, R>::value>::type* = nullptr, typename P,
			typename std::enable_if<std::is_base_of<HttpRequest, P>::value>::type* = nullptr>
			virtual bool mapRequestExecution(const std::string& url, R(requestHandler)(P)) = 0;*/
	};

	/*template<typename T, typename std::enable_if<std::is_base_of<HttpResponse, T>::value>::type* = nullptr>
	T Foo(T bar)
	{
		return T();
	} */
};

