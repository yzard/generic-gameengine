// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/BroadCaster.h>
#include <state/State.h>
#include <state/RouteTable.h>

#include <set>

BroadCaster::BroadCaster() {
}

BroadCaster::~BroadCaster() {
}

bool BroadCaster::cast(const State* fromState, IEvent* event) {
	//const RouteTable* routeTable = RouteTable::instance();

	std::set<State*> toStates;
	//routeTable->getToStates(*fromState, toStates);
	for(std::set<State*>::iterator it = toStates.begin();
		it != toStates.end(); ++it) {
		State* toState = *it;
		toState->onReceive(event);
	}
}
