
#include "ServerServiceConnectEvent.h"

ServerServiceConnectEvent::ServerServiceConnectEvent(const Connect &connect)
	: ServerServiceEvent(), connect(connect) {
};

const Handler &ServerServiceConnectEvent::getHandler() const {
	return this->handler;
}

