// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/State.h>
#include <state/IActioner.h>
#include <state/ICaster.h>

uint32_t State::counter_ = 0;

State::State(const std::string& name, IActioner* actioner,
	ICaster* caster)
	: id_(++counter_)
	, name_(name)
	, actioner_(actioner)
	, caster_(caster) {
}

State::~State() {
}

std::string State::name() const {	
	return name_;
}

uint32_t State::id() const {
	return id_;
}

void State::onReceive(IEvent* event) {
	if (actioner_)
		actioner_->act(event);

	if (caster_)
		caster_->cast(this, event);
}

std::ostream& operator<<(std::ostream& os, const State& state) {
	os << state.name_ << "(" << state.id_ << ")";
	return os;
}
