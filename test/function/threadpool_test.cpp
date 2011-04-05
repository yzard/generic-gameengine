#include <signal.h>
#include <infra/ThreadPool.h>

void signalHandler(int sig) {
	ThreadPool* pool = ThreadPool::Instance();
	pool->Destroy();
}

int main() {
	ThreadPool* pool = ThreadPool::Instance();
	
	// Register the signal handler
	signal(SIGINT, signalHandler);

	std::cout << "A\n";

	// Join all
	pool->JoinAll();

	std::cout << "B\n";

	std::cout << "Quit" << std::endl;
	return 0;
}
