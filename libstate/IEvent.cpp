// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/IEvent.h>

IEvent::IEvent(const std::string& name, const std::string& type)
	: name_(name)
	, type_(type) {
}

IEvent::~IEvent() {
}

std::string IEvent::name() const {
	return name_;
}

std::string IEvent::type() const {
	return type_;
}
