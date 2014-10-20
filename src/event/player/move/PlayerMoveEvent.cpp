
#include "PlayerMoveEvent.h"


PlayerMoveEvent::PlayerMoveEvent(const Player &who, Location from, Location to) 
	: player(who), from(from), to(to) {
}

HandlerList PlayerMoveEvent::getHandlerList() {
	return handler_list;	
}


bool PlayerMoveEvent::isCancelled() {
	return false;
}
void PlayerMoveEvent::setCancelled(bool cancel) {	
}
const Location &PlayerMoveEvent::getFrom() {
	return from;
}
const Location &PlayerMoveEvent::getTo() {
	return from;
}
void PlayerMoveEvent::setFrom(const Location &from) {
	this->from = from;
}
void PlayerMoveEvent::setTo(const Location &to) {
	this->to = to;
}

