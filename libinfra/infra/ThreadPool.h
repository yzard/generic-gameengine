#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <pthread.h>
#include "Task.h"

#define DEFAULT_NUM_THREADS 5
#define MAX_NUM_THREADS 255

/*
The thread pool is using POSIX thread libraries,
if want use other threads, modify ThreadPool.h and ThreadPool.cpp
*/

class ThreadPool {
public:
	ThreadPool(uint32_t numOfThread = DEFAULT_NUM_THREADS);
	~ThreadPool();

private:
	void initialize();
	void deinitialize();
	void addTask(Task task);

	pthread_t* threadPool;

	// Task queue
	TaskNode* head;
	TaskNode* tail;

	pthread_mutex_t mutex_queue;
		
	uint32_t numOfThread;
	uint32_t numOfWorkingThread;
	uint32_t numOfSleepingThread;
}


#endif /* __THREADPOOL_H__ */
