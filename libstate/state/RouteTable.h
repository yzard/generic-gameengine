// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef ROUTETABLE_H
#define ROUTETABLE_H

#include <state/State.h>
#include <state/Route.h>
#include <state/IValidator.h>

#include <string>
#include <map>
#include <set>

class RouteTable {
public:
	static RouteTable* instance();
	static void destroy();
	virtual ~RouteTable();

	virtual bool addRoute(const Route& route, IValidator* validator = 0);
	virtual bool delRoute(const Route& route);

	virtual IValidator* getValidator(const Route& route);

	virtual void getToStates(const State&, std::set<State*>&);
	virtual void getFromStates(const State&, std::set<State*>&);

private:
	RouteTable();
	static RouteTable* instance_;

	typedef std::map<std::string, std::set<std::string> > StateMap;
	typedef StateMap::iterator StateMapIterator;
	typedef StateMap::const_iterator StateMapConstIterator;

	// map route to validator
	std::map<Route, IValidator*> mapRouteToValidator;

	// map state name to set of state
	StateMap mapFromStateToToStates;
	StateMap mapToStateToFromStates;

};

#endif // ROUTETABLE_H

