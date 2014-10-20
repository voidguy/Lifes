
#pragma once

#include <stdint.h>
#include <string>

class Server {
public:
	Server();
	Server(uint16_t port, std::string ip);

public:
	union Version {
		struct {
			uint16_t minor_version;
			uint16_t major_version;
		} v;
		uint32_t version;
	};


public:
	std::string getName();
	Version getVersion();
	uint16_t getPort();
	std::string getIp();

	bool init();
	bool start();

private:
	bool initNetworkListen();

private:
	static const Version version = {{1,0}};
	uint16_t port;
	std::string ip;
	int listen_fd;
	ConnectPoll connect_poll;
};
