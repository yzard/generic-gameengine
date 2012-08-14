// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/StateManager.h>

#include <iostream>

// static members
StateManager* StateManager::instance_ = NULL;
StateManager* StateManager::instance() {
	if (!instance_)
		instance_ = new StateManager();
	return instance_;
}

void StateManager::destroy() {
	if (instance_)
		delete instance_;
}

// non-static members

StateManager::StateManager() {
}

StateManager::~StateManager() {
	map<std::string, State*>::iterator it;

	for (it = mapStateNameToState_.begin();
		it != mapStateNameToState_.end(); ++it) {
		delete it->second;
	}
}

State* StateManager::createState(const std::string& name,
	IActioner* actioner, ICaster caster) {
	map<std::string, State*>::iterator it = mapStateNameToState_.find(name);
	if (it != mapStateNameToState_.end()) {
		std::cout << "StateManager::createSate: state \"" << name
			<< "\" already exists" << std::endl;
		return mapStateNameToState_[name];
	}

	State* newState = new State(name, actioner, caster);
	mapStateNameToState_[name] = newState;
	return newState;
}

void StateManager::deleteState(const std::string& name) {
	map<std::string, State*>::iterator it = mapStateNameToState_.find(name);
	if (it == mapStateNameToState_.end()) {
		std::cout << "StateManager::delete: state \"" << name
			<< "\" doesn't exists" << std::endl;
		return;
	}

	State* state = mapStateNameToState_[name];
	mapStateNameToState_.erase(name);
	delete state;
}

State* StateManager::getState(const std::string&  name) {
	map<std::string, State*>::iterator it = mapStateNameToState_.find(name);
	if (it == mapStateNameToState_.end()) {
		std::cout << "StateManager::getState: state \"" << name
			<< "\" doesn't exists" << std::endl;
		return NULL;
	}

	return mapStateNameToState_[name];
}
