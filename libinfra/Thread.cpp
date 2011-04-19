#include <infra/Thread.h>

Thread::Thread() {
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
}

Thread::~Thread() {
	ReturnValue ret;
	ret = pthread_attr_destroy(&attr);

	if (ret != RET_GOOD)
		std::cout << AT << " Destroy the thread\n";
}

void Thread::setParameters(void* (*routine)(void*), void* params) {
	entry	= routine;
	arg	= params;
}

ReturnValue Thread::start() {
	ReturnValue rc;

	// run the thread
	rc = pthread_create(&thread, &attr, entry, arg);
	if (rc) {
		// TODO: Change to LOG
		std::cout << "ERROR: return code from pthread_create() - "
			  << rc << '\n';
		exit(EXIT_FAILURE);
	}
	else
		// TODO: Change to LOG
		std::cout << "Successfully created\n";

	return rc;
}

ReturnValue Thread::cancel() {
	ReturnValue ret;
	
	ret = pthread_cancel(thread);

	return ret;
}

ReturnValue Thread::join() {
	ReturnValue rc;

	// It's possible that thread will be canceled and the thread
	// is not being joined yet. pay attention
	rc = pthread_join(thread, NULL);
	if (rc != RET_GOOD) {
		errno = rc;
		perror("pthread_join");
	}

	return rc;
}

ReturnValue Thread::setAffinity(int cores) {
#if defined(__linux__)
	// initialize cpuset variable with all zero
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
		
	// TODO: support multiple core
	CPU_SET(cores, &cpuset);
	
	ReturnValue ret;
	// set pthread affinity
	ret = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if (ret != RET_GOOD) {
		// TODO: log error message 
		std::cout << "Fail to set affinity"; 
		errno = ret;
		perror("pthread_setaffinity_np");
		return RET_FAIL;
	}
	
	// TODO: Log the affinity
	std::cout << "set to core " << cores << '\n';
	return RET_GOOD;
#elif defined(__MACH__)
	// TODO: implemant Mac specific code
	std::cout << "setAffinity is not supported on OSX yet\n"; 
	return RET_FAIL;
#else
	#error "What's your operating system?"
#endif
}
