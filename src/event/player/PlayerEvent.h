
#pragma once

#include "../Event.h"

class PlayerEvent: public Event {

public:
    PlayerEvent(Player &who);

public:
    Player getPlayer();

protected:
    Player player;

};
