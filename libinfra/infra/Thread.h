#ifndef __INFRA_THREAD_H__
#define __INFRA_THREAD_H__

#include <Global.h>
#include <pthread.h>

class Thread {
private:
	pthread_t	thread;
	pthread_attr_t	attr;
	void*(*entry)(void*);
	void*		arg;
public:
	Thread();

	~Thread();

	// set the parameters 
	// 1. entry function
	// 2. parameters that passed to the function
	void setParameters(void* (*routine)(void*), void* params);

	// start the thread
	ReturnValue start();

	// cancel the running thread
	ReturnValue cancel();

	// join the thread, blocking current thread to wait this
	// thread.
	ReturnValue join();

	// detach the thread
	ReturnValue detach();

	ReturnValue setAffinity(int cores);
};

#endif /* __INFRA_THREAD_H__ */

