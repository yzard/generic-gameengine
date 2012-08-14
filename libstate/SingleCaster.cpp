// vim: tabstop=8 shiftwidth=8 noexpandtab

#include <state/SingleCaster.h>
#include <state/RouteTable.h>

SingleCaster::SingleCaster() {
}

SingleCaster::~SingleCaster() {
}

bool SingleCaster::cast(const State* fromState, IEvent* event) {
	RouteTable* routeTable = RouteTable::instance();

	std::set<State*> toStates;
	routeTable->getToStates(*fromState, toStates);
	for(std::set<State*>::iterator it = toStates.begin();
		it != toStates.end(); ++it) {
		State* toState = *it;
		Route route(fromState, toState);

		IValidator* validator = routeTable->getValidator(route);
		if (validator && !validator->validate(fromState, event))
			continue;

		// if validation successed, send to next state, and end
		// the loop
		toState->onReceive(event);
		break;
	}
	return true;
}
