	
#include "Connect.h"

Connect::Connect(int conn_fd, sockaddr_in remote_addr): conn_fd(conn_fd), remote_addr(remote_addr) {

}

std::string Connect::getRemoteIp() {
	return std::string(inet_ntoa(remote_addr.sin_addr));
}

uint16_t Connect::getRemotePort() {
	return remote_addr.sin_port;
}

int Connect::getConnectFd() {
	
}

