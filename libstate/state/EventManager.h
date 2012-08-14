// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <map>

class IEvent;

class EventManager {
public:
	static EventManager* instance();
	static void destroy();
	virtual ~EventManager();

	IEvent* createEvent(const std::string& name,
		const std::string& type);
	void deleteEvent(const std::string& name);

private:
	EventManager();
	static EventManager* instance_;

	typedef std::map<std::string, IEvent*(*)(const std::string&)> NameToTypeMap;
	typedef NameToTypeMap::iterator NameToTypeMapIterator;
	typedef std::map<std::string, IEvent*> NameToEventMap;
	typedef NameToEventMap::iterator NameToEventMapIterator;

	NameToTypeMap mapNameToEventTypes_;
	NameToEventMap mapNameToEvents_;
	
	template <typename T> IEvent* typeCreator(const std::string& name);
};

#endif // EVENTMANAGER_H

