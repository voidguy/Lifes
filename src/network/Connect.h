
#pragma once

#include <netinet/in.h>

class Connect {
public:
	Connect(int conn_fd, sockaddr_in remote_addr);

	std::string getRemoteIp();
	uint16_t getRemotePort();
	int getConnectFd();

private:
	int conn_fd,
	sockaddr_in remote_addr;

};