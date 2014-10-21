
#pragma once

#include "../event/Event.h"

class Listener {

public:
	bool callEvent(Event event);
	bool isIgnoringCancelled();

	Event::Priority getPriority();

};
