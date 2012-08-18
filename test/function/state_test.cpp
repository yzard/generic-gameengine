// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <iostream>
#include <cstdlib>

#include <state/EventManager.h>
#include <state/RouteTable.h>
#include <state/State.h>
#include <state/StateManager.h>
#include <state/PrintActioner.h>
#include <state/SingleCaster.h>
#include <state/MultiCaster.h>
#include <state/BroadCaster.h>
#include <state/ByteStream.h>
#include <state/PrintActioner.h>
#include <state/UDPSenderActioner.h>


void usage(const char* program) {
	std::cout << "usage: " << program << " <options>"	<< std::endl;
	std::cout << "option:"					<< std::endl;
	std::cout << "-h                       this message"	<< std::endl;
}

int main(int argc, char* argv[]) {
	// options default value
	
	int c;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
		case '?':
		default:
			usage(argv[0]);
			return EXIT_SUCCESS;
		}
	}

	// process non-option parameters
	for (int i = optind; i < argc; ++i) {
		std::cout << "Non-option argument " << argv[i] << std::endl;
		return EXIT_FAILURE;
	}

	// singletons
	RouteTable* routeTable 		= RouteTable::instance();
	StateManager* manager 		= StateManager::instance();
	EventManager* eventManager 	= EventManager::instance();

	// actioners
	static PrintActioner printActioner;
	static UDPSenderActioner udpSenderActioner("127.0.0.1", 1025);

	// casters
	static SingleCaster 	singleCaster;
	static MultiCaster 	multiCaster;
	static BroadCaster 	broadCaster;

	// states
	State* A = manager->createState("A", &singleCaster);
	State* B = manager->createState("B", &multiCaster);
	State* C = manager->createState("C", &multiCaster);
	State* D = manager->createState("D", &multiCaster);
	State* E = manager->createState("E", &broadCaster);
	State* F = manager->createState("F", 0, &udpSenderActioner);

	// route table
	routeTable->addRoute(Route(A, B));
	routeTable->addRoute(Route(B, C));
	routeTable->addRoute(Route(C, D));
	routeTable->addRoute(Route(D, E));
	routeTable->addRoute(Route(D, F));

	IEvent* event = eventManager->createEvent("foobar", "MaskMessageEvent");
	if (!event)
		return EXIT_FAILURE;

	for (;;) {
		sleep(1);
		A->onReceive(event);
	}

	// destroy
	RouteTable::destroy();
	StateManager::destroy();
	EventManager::destroy();

	return EXIT_SUCCESS;
}
