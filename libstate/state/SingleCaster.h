// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef SINGLECASTER_H
#define SINGLECASTER_H

#include <state/ICaster.h>

class IEvent;
class State;

class SingleCaster : public ICaster {
public:
	SingleCaster();
	~SingleCaster();

	// public methods
	virtual bool cast(const State* fromState, IEvent* event);
};

#endif // SINGLECASTER_H

