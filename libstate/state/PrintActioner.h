// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef PRINTACTIONER_H
#define PRINTACTIONER_H

#include <state/IActioner.h>

class PrintActioner : public IActioner {
public:
	PrintActioner();
	virtual ~PrintActioner();

	virtual bool act(IEvent* event);
};

#endif // PRINTACTIONER_H

