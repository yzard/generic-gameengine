#include "infra/ThreadPool.h"

void ThreadPool::ThreadPool(int numOfThreads) {
	// allocate number of threads
	threadPool = new Thread[numOfThreads];

	// Initialize the threads
	head = NULL;
	tail = NULL;
}

void ThreadPool::addTask(Task task) {

}
