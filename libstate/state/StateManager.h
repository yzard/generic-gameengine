// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <string>
#include <map>

class State;
class IActioner;
class ICaster;

class StateManager {
public:
	static StateManager* instance();
	static void destroy();
	virtual ~StateManager();

	State* createState(const std::string& name, ICaster* caster = 0,
		IActioner* actioner = 0);
	void deleteState(const std::string& name);

	State* getState(const std::string& name);

private:
	StateManager();
	static StateManager* instance_;

	std::map<std::string, State*> mapStateNameToState_;
};

#endif // STATEMANAGER_H

