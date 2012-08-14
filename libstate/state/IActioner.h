// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef IACTIONER_H
#define IACTIONER_H

class IEvent;

class IActioner {
public:
	virtual bool act(IEvent* event) = 0;
};

#endif // IACTIONER_H

