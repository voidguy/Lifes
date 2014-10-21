
#pragma once

class Handler  {

public:
	handler();

public:
	const std::vector<Listener> &getListeners() const;
	void regist(Listener listener);
	void unregist(Listener listener);

	static const std::vector<Handler> &getHandlerList() const;

private:
	static std::vector<Handler> handlerlist_vector; 
	static std::map<Event, Listener> event_listener_map;


};
