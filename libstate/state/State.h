// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <iostream>
#include <string>

#include <state/IReceiver.h>

class IActioner;
class IEvent;
class ICaster;

class State : public IReceiver {
public:
	State(const std::string& name, IActioner* actioner,
		ICaster* caster);
	~State();

	virtual void onReceive(IEvent* event);
	uint32_t id() const;
	std::string name() const;

	friend std::ostream& operator<<(std::ostream& os, const State& state);

private:
	std::string 	name_;
	uint32_t 	id_;

	IActioner* 	actioner_;
	ICaster* 	caster_;

	static uint32_t counter_;
};

#endif // STATE_H

