// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef IVALIDATOR_H
#define IVALIDATOR_H

class State;
class IEvent;

class IValidator {
public:
	virtual bool validate(const State* fromState, IEvent* event) = 0;
};

#endif // IVALIDATOR_H

