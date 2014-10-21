


class PlayerAnimationEvent: public PlayerEvent {

public:
	PlayerAnimationEvent(Player &who);

public:
	static HandlerList  getHandlerList();
	HandlerList getHandlers();
	boolean isCancelled();
	void setCancelled(boolcancel);

public:
	PlayerAnimationType getAnimationType();

};