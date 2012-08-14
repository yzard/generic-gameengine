// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef IRECEIVER_H
#define IRECEIVER_H

class IEvent;

class IReceiver {
public:
	virtual void onReceived(IEvent* event) = 0;
};

#endif // IRECEIVER_H

