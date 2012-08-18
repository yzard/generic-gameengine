#include <Debugging.h>
#include <infra/ThreadPool.h>
#include <infra/ExampleTask.h>

#include <signal.h>

void signalHandler(int sig) {
	ThreadPool* pool = ThreadPool::Instance();

	// JoinAll will deal with the memory de-allocation
	// if all the threads are safely quited.
	// so calling CancelAll here is fine
	pool->CancelAll();
}

int main() {
	ThreadPool* pool = ThreadPool::Instance();
	
	// Register the signal handler
	signal(SIGINT, signalHandler);

	//ExampleTask** tasks = new ExampleTask*[10];
	//pool->add(tasks, 10);
	
	// Join all
	pool->JoinAll();

	std::cout << "Quit" << std::endl;
	return 0;
}
