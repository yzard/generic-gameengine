// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef ROUTE_H
#define ROUTE_H

// Route is the literally route from one state to another

#include <iostream>
#include <string>

class State;

class Route {
public:
	Route(const State* fromState, const State* toState);
	~Route();

	const State* fromState() const; 
	const State* toState() const;

	friend std::ostream& operator<<(std::ostream& os,
		const Route& route);

	bool operator==(const Route& lhs) const;
	bool operator<(const Route& lhs) const;

private:
	const State* fromState_;
	const State* toState_;
};

#endif // ROUTE_H

