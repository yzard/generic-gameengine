// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef ICASTER_H
#define ICASTER_H

class IEvent;
class State;

class ICaster {
public:
	virtual bool cast(const State* fromState, IEvent* event) = 0;
};

#endif // ICASTER_H

