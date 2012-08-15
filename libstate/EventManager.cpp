// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/EventManager.h>
#include <state/IEvent.h>

#include <iostream>

#include <state/MaskMessageEvent.h>

EventManager* EventManager::instance_ = NULL;
EventManager* EventManager::instance() {
	if (!instance_)
		instance_ = new EventManager();
	return instance_;
}

void EventManager::destroy() {
	if (instance_)
		delete instance_;
}

template <typename T>
IEvent* EventManager::typeCreator(const std::string& name) {
	return new T(name);	
}

// non-static members
EventManager::EventManager() {
#define REGISTER_EVENT_TYPE(TYPE) \
	mapNameToEventTypes_[#TYPE] = &typeCreator<TYPE>();

	// register event type
	// 1. should have header file
	// 2. should derived from class IEvent
	// 3. the constructor should only have one parameter std::string
	REGISTER_EVENT_TYPE(MaskMessageEvent);
}

EventManager::~EventManager() {
	NameToEventMapIterator it;	
	for (it = mapNameToEvents_.begin();
		it != mapNameToEvents_.end(); ++it) {
		delete it->second;
	}

	mapNameToEvents_.clear();
	mapNameToEventTypes_.clear();
}

IEvent* EventManager::createEvent(const std::string& name,
	const std::string& type) {
	NameToTypeMapIterator typeIt = mapNameToEventTypes_.find(type);
	if (typeIt == mapNameToEventTypes_.end()) {
		std::cout << "Doesn't support event type \"" << type << "\""
			<< std::endl;
		return 0;
	}

	NameToEventMapIterator eventIt = mapNameToEvents_.find(name);
	if (eventIt != mapNameToEvents_.end()) {
		std::cout << "Event \"" << name << "\" already exists!"
			<< std::endl;
		return eventIt->second;
	}

	IEvent* newEvent = (typeIt->second)(name);
	mapNameToEvents_[name] = newEvent;
	return newEvent;
}

void EventManager::deleteEvent(const std::string& name) {
	NameToEventMapIterator eventIt = mapNameToEvents_.find(name);
	if (eventIt == mapNameToEvents_.end()) {
		std::cout << "Event \"" << name << "\" doesn't exists!"
			<< std::endl;
		return;
	}

	delete eventIt->second;
	return;
}


