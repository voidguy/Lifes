
#include "NetworkConnectPool.h"

NetworkConnectPool::NetworkConnectPool(): 
	NetworkConnectPool(NetworkConnectPool::default_max_events, NetworkConnectPool::default_wait_timeout) {
}


NetworkConnectPool::NetworkConnectPool(int max_events, int wait_timeout):
	max_events(max_events), 
	wait_timeout(wait_timeout), 
	wait_event_list(nullptr) {
}

NetworkConnectPool::~NetworkConnectPool() {
	if (wait_event_list) {
		delete[] wait_event_list;
	}
}

void NetworkConnectPool::setMaxEvents(int max_events) {
	if (this->max_events == max_events || max_events <= 0) {
		return;
	}
	this->max_events = max_events;
	delete[] wait_event_list;
	wait_event_list = new epoll_event[max_events];
}

bool NetworkConnectPool::initPool() {
	if (max_events <= 0) {
		max_events = default_max_events;
	}
	if (wait_timeout <= 0) {
		wait_timeout = default_wait_timeout;
	}
	wait_event_list = new epoll_event[max_events];
}


bool NetworkConnectPool::checkSocket() {
	int fds = epoll_wait(epoll_fd, wait_event_list, max_events, wait_timeout);
	if (fds < 0) {
		return false;
	}
	for(int i = 0; i < fds; ++i) {
		Event *event_ptr = reinpreter_cast<Event *>(wait_event_list[i].data.ptr);
		auto listeners = event_ptr->getHandler()->getListeners();
		for(const Listener &listener: listeners) {
			listener->callEvent(*event_ptr);
		}
	}

	return true;
}