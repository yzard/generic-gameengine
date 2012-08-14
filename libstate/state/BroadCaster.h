// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <state/ICaster.h>

class IEvent;
class State;

class BroadCaster : ICaster {
public:
	BroadCaster();
	virtual ~BroadCaster();

	virtual bool cast(const State* fromState, IEvent* event);
};

#endif // BROADCASTER_H

