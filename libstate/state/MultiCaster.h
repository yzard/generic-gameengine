// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef MULTICASTER_H
#define MULTICASTER_H

#include <state/ICaster.h>

class IEvent;
class State;

class MultiCaster : public ICaster {
public:
	MultiCaster();
	virtual ~MultiCaster();

	virtual bool cast(const State* fromState, IEvent* event);
};

#endif // MULTICASTER_H

