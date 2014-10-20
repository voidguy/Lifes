
#pragma once

#include "../Network.h"
#include <sys/epoll.h>

class NetworkConnectPool: public Network {
public:
	NetworkConnectPool();
	NetworkConnectPool(int max_events, int wait_timeout);
	~NetworkConnectPool();

public:
	bool checkSocket();
	void setMaxEvents(int max_events);
	bool initPool();


private:


private:
	int epoll_fd;
	epoll_event *wait_event_list;
	int max_events;
	int wait_timeout;

	static const default_max_events 	=  10000;
	static const default_wait_timeout 	=  100;
};