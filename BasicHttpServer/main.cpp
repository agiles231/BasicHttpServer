#pragma comment(lib, "ws2_32.lib")
#include "HttpServer.h"
#include "BasicHttpServer.h"

using namespace HttpServerNS;
void detectShutdown(HttpServer* server) {
}
int main() {
	HttpServer* server = new BasicHttpServer("192.168.0.103", 1111, 2, 1112);
	std::thread t = std::thread(detectShutdown, server);
	t.detach();
	server->start();
	delete server;
	return 0;
}

