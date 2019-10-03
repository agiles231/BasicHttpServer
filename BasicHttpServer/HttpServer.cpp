#pragma comment(lib, "ws2_32.lib")
#include "HttpServer.h"
#include <iostream>
//#include "Ws2tcpip.h"
#include <WinSock2.h>

namespace HttpServerNS {

	HttpServer::HttpServer(std::string ipAddress, int port) {
		this->ipAddress = ipAddress;
		this->listeningPort = port;
	}
	HttpServer::~HttpServer()
	{
	}
	
	void HttpServer::start() {
	}
	void HttpServer::shutdown()
	{
	}
}
