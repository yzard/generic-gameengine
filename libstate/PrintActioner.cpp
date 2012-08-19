// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/PrintActioner.h>
#include <state/IEvent.h>

#include <iostream>

PrintActioner::PrintActioner() {
}

PrintActioner::~PrintActioner() {
}

bool PrintActioner::act(IEvent* event) {
	std::cout << "Name: " << event->name() << " Type: " << event->type() <<
		std::endl;
}

