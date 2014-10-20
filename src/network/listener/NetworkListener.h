
#pragma once

#include "../Network.h"

class NetworkListener: public Network {
public:
	NetworkListener();

public:
	Accept();
	

private:
	int listen_fd;
};

