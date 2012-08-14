// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/Route.h>
#include <state/State.h>

Route::Route(const State* fromState, const State* toState)
	: fromState_(fromState)
	, toState_(toState) {
}

Route::~Route() {
}

const State* Route::fromState() const {
	return fromState_;
}

const State* Route::toState() const {
	return toState_;
}

std::ostream& operator<<(std::ostream& os, const Route& route) {
	os << route.toState() << " -> " << route.toState();	
	return os;
}

bool Route::operator==(const Route& rhs) const {
	return (this->fromState_->id() == rhs.fromState_->id() && 
		this->toState_->id() == rhs.toState_->id());
}

bool Route::operator<(const Route& rhs) const {
	if (this->fromState_->id() < rhs.fromState_->id())
		return true;
	else if (this->fromState_->id() > rhs.fromState_->id())
		return false;

	if (this->toState_->id() < rhs.toState_->id())
		return true;
	else if (this->toState_->id() > rhs.toState_->id())
		return false;

	return false;
}

