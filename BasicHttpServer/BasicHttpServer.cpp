#include "BasicHttpServer.h"

namespace HttpServerNS {

	BasicHttpServer::BasicHttpServer(std::string ipAddress, int port, int maxThreads, int shutdownPort) : BasicHttpServer(ipAddress, maxThreads, 1, { port }, shutdownPort) {
	}
	BasicHttpServer::BasicHttpServer(std::string ipAddress, int maxThreads, int listeningThreads, int* listeningPorts, int shutdownPort) {

	}


	BasicHttpServer::~BasicHttpServer()
	{
	}

	void BasicHttpServer::start() {
		WSAData wsaData;
		WORD dllVersion = MAKEWORD(2, 1);
		if (WSAStartup(dllVersion, &wsaData) != 0) {
			MessageBoxA(NULL, "Winsock startup failed", "Error",MB_OK | MB_ICONERROR);
		}


		std::thread shutdownThread = std::thread(&awaitShutdownCommand, this);
		shutdownThread.detach();

		for (int i = 0; i < listenerCount; i++) {
			std::thread t = std::thread(::listen(listeners[i], SOMAXCONN));
			t.detach();
		}
		running = true;
		std::thread t = std::thread(&BasicHttpServer::listen, this, listeners);
		WSACleanup();
	}

	void BasicHttpServer::shutdown(SOCKET listener) {
		running = false;
		if (listener != INVALID_SOCKET) {
			::shutdown(listener, SD_BOTH);
			closesocket(listener);
		}
	}
	void BasicHttpServer::shutdown() {
		for (int i = 0; i < listenerCount; i++) {
			shutdown(listeners[i]);
		}
	}

	void BasicHttpServer::listen(int index) {
		SOCKADDR_IN addr;
		int addrLen = sizeof(addr);
		in_addr inAddress;
		addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
		addr.sin_port = htons(listeningPorts[index]);
		addr.sin_family = AF_INET; // ipv4

		listeners[index] = socket(AF_INET, SOCK_STREAM, NULL);
		bind(listeners[index], (SOCKADDR*)&addr, addrLen);
		::listen(listeners[index], SOMAXCONN);
		SOCKET clientConnection ;
		while (running) {
			clientConnection = accept(listeners[index], (SOCKADDR*)&addr, &addrLen);
			if (clientConnection  == INVALID_SOCKET) {
				std::cout << "Failed to accept client's connection." << std::endl;
			}
			else {
				if (currentThreadCount == maxThreadCount) {
					closesocket(clientConnection);
				}
				else {
					std::cout << "Client Connected!" << std::endl;
					HttpRequest* request = NULL;
					std::thread t = std::thread(&handleRequest, this, request, clientConnection);
					t.detach();
					clientConnection = INVALID_SOCKET;
				}
			}
		}

	}

	void BasicHttpServer::handleRequest(HttpRequest* request, SOCKET clientConnection) {
		HttpResponseBuilder builder = HttpResponseBuilder();
		builder.setStatusCode(200);
		builder.addHeader("Content-Type", "text/html;charset=UTF-8");
		builder.addHeader("Connection", "keep-alive");
		std::string body = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Tranistional//EN\">\n<html><head><title>Servlet Life Cycle</title></head>\n<body>\nn is 2999 and m is 440\n</body>\n</html>";
		builder.addHeader("Content-Length", std::to_string(body.length()));
		builder.addHeader("Date", "Tues, 22 Jan 2019 23:27:15 GMT");
		builder.addHeader("Server", "BasicHttpServer 0.1");
		builder.addHeader("Bearer", "abc");
		builder.setMessageBody(body);
		HttpMessage* response = builder.build();
		std::string buffer = response->getHttpMessage();
		int sendStatus = send(clientConnection , buffer.c_str(), strlen(buffer.c_str()), NULL);
		if (sendStatus == 0) {
			std::cout << "Something went wrong.";
		}
		closesocket(clientConnection);
	}

	void BasicHttpServer::awaitShutdownCommand() {
		WSAData wsaData;
		WORD dllVersion = MAKEWORD(2, 1);
		if (WSAStartup(dllVersion, &wsaData) != 0) {
			MessageBoxA(NULL, "Winsock startup failed", "Error",MB_OK | MB_ICONERROR);
		}

		SOCKADDR_IN addr;
		int addrLen = sizeof(addr);
		in_addr inAddress;
		addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
		addr.sin_port = htons(shutdownListeningPort);
		addr.sin_family = AF_INET; // ipv4

		shutdownListener = socket(AF_INET, SOCK_STREAM, NULL);
		bind(shutdownListener, (SOCKADDR*)&addr, addrLen);
		::listen(shutdownListener, 1);

		SOCKET shutdownConnection ;
		running = true;
		while (running) {
			shutdownConnection = accept(shutdownListener, (SOCKADDR*)&addr, &addrLen);
			if (shutdownConnection  == INVALID_SOCKET) {
				std::cout << "Failed to accept shutdown connection." << std::endl;
			}
			else {
				std::cout << "Shutdown command received. Beginning shutdown." << std::endl;
				shutdown();
				shutdownConnection = INVALID_SOCKET;
			}
		}
		WSACleanup();
		this->shutdown();
	}
}
