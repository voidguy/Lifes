
#pragma once

#include "../PlayerEvent.h"

class PlayerMoveEvent: public PlayerEvent {

public:
	PlayerMoveEvent(Player &who, Location &from, Location &to);

public:
	HandlerList getHandlerList();

	bool isCancelled();
	void setCancelled(bool cancel);

public:
	Location getFrom();
	Location getTo();
	void setFrom(const Location &from);
	void setTo(const Location &to);

private:
	Location from;
	Location to;
	HandlerList handler_list;


};
