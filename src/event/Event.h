
#pragma once

#include "Handler.h"

class Event {

public:
    Event();
    Event(bool is_async);


public:
    std::string getEventName();

    bool isAsync();

	Priority getPriority();

public:
    virtual const Handler &getHandler() const = 0;

private:
	bool is_async;

public:
	enum Priority {
		LOWEST	= 4;
		LOW		= 6;
		NORMAL	= 8;
		HIGH	= 10;
		HIGHEST	= 12;
		MONITOR	= 14;
	};
	enum Result {
		DEFAULT	= 0; 
		ALLOW	= 1;
		DENY	= 2;
	}

};
