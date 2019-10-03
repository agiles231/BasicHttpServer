#pragma once
#include "HttpServer.h"

namespace HttpServerNS {
	class BasicHttpServer : public HttpServer
	{
	private:
		void awaitShutdownCommand();
		void listen(int index);
		void shutdown(SOCKET listener);
		std::map<std::string, std::function<HttpResponse* (const HttpRequest&, SOCKET)>> mappings;

		int maxThreads;
		int currentThreads;
		std::map<int, std::thread> threads;
		std::map<int, SOCKET> threadSockets;

		int listenerCount;
		int* listeningPorts;
		SOCKADDR_IN* addr;
		SOCKET* listeners;

		int shutdownListeningPort;
		SOCKADDR_IN addr;
		SOCKET shutdownListener;
	protected:
		virtual void handleRequest(HttpRequest* request, SOCKET clientConnection) override;
	public:
		BasicHttpServer(std::string ipAddress, int port, int maxThreads, int shutdownPort);
		BasicHttpServer(std::string ipAddress, int maxThreads, int listeningThreads, int* listeningPorts, int shutdownPort);
		~BasicHttpServer();
		virtual void start() override;
		virtual void shutdown() override;
		virtual void restart() override { HttpServer::restart(); }

		virtual bool mapRequestHandler(const std::string& path, std::function<HttpResponse* (const HttpRequest&, SOCKET)> requestHandler) {
			mappings.insert(std::pair<std::string, std::function<HttpResponse* (const HttpRequest&, SOCKET)>>(path, requestHandler));
			return true;
		}
		//virtual bool mapRequestExecution(const std::string& url, std::function<HttpResponse* (HttpRequest*)> requestHandler) override;
		//template<typename T> virtual bool mapRequestExecution(const std::string& url, T requestHandler) override;
	};

}
