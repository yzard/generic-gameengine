#ifndef __INFRA_THREADPOOL_H__
#define __INFRA_THREADPOOL_H__

#include <infra/ThreadAgent.h>
#include <infra/Thread.h>
#include <infra/Mutex.h>
#include <infra/Task.h>
#include <infra/Queue.h>

#define DEFAULT_THREAD_ID	0
#define DEFAULT_NUM_THREADS 	8
#define MAX_NUM_THREADS		1024

/*
The thread pool is using POSIX thread libraries,
if want use other threads, modify ThreadPool.h and ThreadPool.cpp
*/

class ThreadPool {
public:
	// this is the method to get instance
	static ThreadPool* Instance(uint32_t num = DEFAULT_NUM_THREADS);

	// don't have to be virtual since the threadpool should
	// be an implementation of Object
	~ThreadPool();
	
	// Add task to the thread pool
	// the Task* means an pointer to a Task instance, you can pass
	// which thread you want add.
	void add(Task* pTask, uint32_t id = DEFAULT_THREAD_ID);

	// return the size of threads
	uint32_t size() const;

	// the method for join all the threads
	void JoinAll();

	// the method for cancel all the threads
	ReturnValue CancelAll();

	// set affinity
	ReturnValue setAffinity(uint32_t num, int core);

private:
	// the threadpool should be singleton
	// so let the construct to be private
	ThreadPool(){};
	ThreadPool(uint32_t num);

	// initialize function, static
	void initialize();

	// the destroy function for the ThreadPool, singleton
	// need be static too
	void deinitialize();

	// copy constructor is private
	ThreadPool(ThreadPool const&){};
	
	// assignment operator is private
	ThreadPool& operator=(ThreadPool const&){};

	// the function that will run when thread
	// is created
	static void* entry(void* data);

	// deadlock detection, may have other purpose detection
	// but right the detection of deadlock will be implemented.
	// this function will create a thread to do periodically
	// check for deadlocks.
	void detection();

private:
	Thread*			m_detectThread;

	// the entities of threads
	Thread*			m_pThreads;
	Mutex*			m_pMutexes;

	// the queue for each thread
	Queue<Task*>*		m_pQueues;

	// ThreadAgent
	ThreadAgent*		m_threadAgents;

	// pthread attribute and status
	pthread_attr_t		m_attr;

	// the number of the threads in the threadpool 
	uint32_t		m_size;

	// the single instance of this class
	static ThreadPool*	m_pInstance;
};


#endif /* __INFRA_THREADPOOL_H__ */
