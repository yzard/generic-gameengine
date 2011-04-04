#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <infra/Task.h>
#include <infra/Queue.h>
#include <pthread.h>

#define DEFAULT_NUM_THREADS 	5
#define MAX_NUM_THREADS		255

/*
The thread pool is using POSIX thread libraries,
if want use other threads, modify ThreadPool.h and ThreadPool.cpp
*/

class ThreadPool {
public:
	// this is the method to get instance
	static ThreadPool* Instance(uint32_t num = DEFAULT_NUM_THREADS);

	// the destroy function for the ThreadPool, singleton
	static void Destroy();

	// don't have to be virtual since the threadpool should
	// be an implementation of Object
	~ThreadPool();
	
	// Add task to the thread pool
	// the Task** means an array of (Task*), whereas Task* is
	// the pointer to the Task instance, you can pass
	// the number of (Task*) you want add to the function
	void add(Task** ppTask, uint32_t number);

	// return the size of threads
	uint32_t size() const;

	// the method for join all the threads
	void JoinAll();

	// set affinity
	ReturnValue setAffinity(uint32_t num, int core);

private:
	// the threadpool should be singleton
	// so let the construct to be private
	ThreadPool(){};
	ThreadPool(uint32_t num);

	// copy constructor is private
	ThreadPool(ThreadPool const&){};
	
	// assignment operator is private
	ThreadPool& operator=(ThreadPool const&){};

	// the function that will run when thread
	// is created
	static void* m_run(void* data);

private:
	// the entities of threads
	static pthread_t* 	m_pThreads;
	static pthread_mutex_t*	m_pMutexes;
	// the queue for each thread
	static Queue<Task*>*	m_pQueues;

	// pthread attribute and status
	pthread_attr_t		m_attr;
	void*			m_status;

	// the number of the threads in the threadpool 
	uint32_t		m_size;

	// the single instance of this class
	static ThreadPool*	m_pInstance;
};


#endif /* __THREADPOOL_H__ */
