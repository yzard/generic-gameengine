#include <signal.h>
#include <infra/ThreadPool.h>
#include <infra/ExampleTask.h>
#include <infra/Debugging.h>

void signalHandler(int sig) {
	ThreadPool* pool = ThreadPool::Instance();
	pool->deinitialize();
}

int main() {
	ThreadPool* pool = ThreadPool::Instance();
	pool->initialize();
	
	// Register the signal handler
	signal(SIGINT, signalHandler);

	//ExampleTask** tasks = new ExampleTask*[10];

	//pool->add(tasks, 10);

	int i = 1;
	TRACE(i);

	// Join all
	pool->JoinAll();

	std::cout << "Quit" << std::endl;
	return 0;
}
