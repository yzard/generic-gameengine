// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/RouteTable.h>
#include <state/StateManager.h>

// static members
RouteTable* RouteTable::instance_ = NULL;
RouteTable* RouteTable::instance() {
	if (!instance_)
		instance_ = new RouteTable();

	return instance_;
}

void RouteTable::destroy() {
	if (instance_)
		delete instance_;
}

// non-static functions

RouteTable::RouteTable() {
}

RouteTable::~RouteTable() {
}

bool RouteTable::addRoute(const Route& route, IValidator* validator) {
	const State* fromState = route.fromState();
	const State* toState = route.toState();

	if (!fromState) {
		std::cout << "state \"" << fromState
			<< "\" doesn't exists!" << std::endl;
		return false;
	}

	if (!toState) {
		std::cout << "state \"" << toState
			<< "\" doesn't exists!" << std::endl;
		return false;
	}

	if (mapRouteToValidator.find(route) != mapRouteToValidator.end()) {
		std::cout << "Route \"" << route
			<< "\" already exists!" << std::endl;
		return false;
	}

	// 1. add route to validator
	mapRouteToValidator[route] = validator;
	mapFromStateToToStates[fromState->name()].insert(toState->name());
	mapToStateToFromStates[toState->name()].insert(fromState->name());
}

bool RouteTable::delRoute(const Route& route) {
	if (mapRouteToValidator.find(route) == mapRouteToValidator.end()) {
		std::cout << "Route \"" << route
			<< "\" is not in route table!" << std::endl;
		return false;
	}
	mapRouteToValidator.erase(route);
	
	const State* fromState = route.fromState();
	const State* toState = route.toState();

	mapFromStateToToStates[fromState->name()].erase(toState->name());
	mapToStateToFromStates[toState->name()].erase(fromState->name());
}

IValidator* RouteTable::getValidator(const Route& route) {
	if (mapRouteToValidator.find(route) == mapRouteToValidator.end()) {
		std::cout << "Route \"" << route
			<< "\" is not in route table!" << std::endl;
		return 0;
	}

	return mapRouteToValidator[route];
}

void RouteTable::getToStates(const State& fromState,
	std::set<State*>& toStates) {
	// if didn't found, then just return
	const std::string& fromStateName = fromState.name();
	StateMapConstIterator it = mapFromStateToToStates.find(fromStateName);
	if (it == mapFromStateToToStates.end()) {
		std::cout << "RouteTable:: state \"" << fromState
			<< "\" didn't directed to any other state" << std::endl;
		return;
	}
	
	StateManager* stateManager = StateManager::instance();
	toStates.clear();
	const std::set<std::string>& toStateNames =
		mapFromStateToToStates[fromStateName];
	for (std::set<std::string>::const_iterator it = toStateNames.begin();
		it != toStateNames.end(); ++it) {
		const std::string& stateName = *it;
		State* state = stateManager->getState(stateName);
		if (state)
			toStates.insert(state);	
	}
	return;
}

void RouteTable::getFromStates(const State& toState,
	std::set<State*>& fromStates) {
	// if didn't found, then just return
	const std::string& toStateName = toState.name();
	StateMapConstIterator it = mapToStateToFromStates.find(toStateName);
	if (it == mapToStateToFromStates.end()) {
		std::cout << "RouteTable:: state \"" << toState
			<< "\" didn't have any other state directed to"
			<< std::endl;
		return;
	}
	
	StateManager* stateManager = StateManager::instance();
	fromStates.clear();
	const std::set<std::string>& fromStateNames =
		mapToStateToFromStates[toStateName];
	for (std::set<std::string>::const_iterator it = fromStateNames.begin();
		it != fromStateNames.end(); ++it) {
		const std::string& fromState = *it;
		State* state = stateManager->getState(fromState);
		if (state)
			fromStates.insert(state);	
	}
	return;
}
