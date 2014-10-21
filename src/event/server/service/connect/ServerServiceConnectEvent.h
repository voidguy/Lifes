
#pragma once

#include "../ServerServiceEvent.h"


class ServerServiceConnectEvent: public ServerServiceEvent {
public:		
	ServerServiceConnectEvent(const Connect &connect);

public:
	const Handler &getHandler() const override;

private:
	static const Handler handler = Handler();

	Connect connect;

};
