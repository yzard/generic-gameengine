// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/StateFactory.h>

StateFactory::StateFactory() {
}

StateFactory::~StateFactory() {
}

StateFactory& StateFactory::instance() {
	if (!instance)
		instance = new StateFactory();

	return *instance;
}


