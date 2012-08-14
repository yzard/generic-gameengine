#include <infra/ThreadPool.h>

// the static variable for instance, make sure the instance to be
// only one
ThreadPool* ThreadPool::m_pInstance	= NULL;

// Singleton, ensure there is always only one instance
ThreadPool* ThreadPool::Instance(uint32_t number) {
	if (m_pInstance == NULL) {
		m_pInstance = new ThreadPool(number);
		m_pInstance->initialize();
	}

	return m_pInstance;
}

// initialize function
void ThreadPool::initialize() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return;
	}

	uint32_t i;

	// Thread Agent structure initialization
	for (i = 0; i < m_size; i++) {
		// ThreadPool id
		m_threadAgents[i].setId(i);

		// at the beginning, the thread is not running
		m_threadAgents[i].setRunning(false);
	}

	// set the entry point and parameters
	for (i = 0; i < m_size; i++) {
		m_pThreads[i].setParameters(
			&ThreadPool::entry,
			static_cast<void*>(&m_threadAgents[i])
		);
	}

	// Start create threads
	for (i = 0; i < m_size; i++) {
		// TODO: Change to LOG
		std::cout << AT << "Creating thread[" << i << "] - ";

		// actually start the thread
		m_pThreads[i].start();
	}
}

// destroy the threadpool
void ThreadPool::deinitialize() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return;
	}

	// destroy the instance of Threadpool is there is one
	delete m_pInstance;
	m_pInstance = NULL;
}

// static entry function
void* ThreadPool::entry(void* data) {
	Task**		ppTask;
	ThreadAgent*	threadAgent 	= static_cast<ThreadAgent*>(data);
	uint32_t 	threadAgentID	= threadAgent->getId(); 
	Queue<Task*>&	taskQueue	= m_pInstance->m_pQueues[threadAgentID];
	uint32_t	receivedNumber;
	ReturnValue	returnValue;
	
	while (true) {
		receivedNumber = taskQueue.get(ppTask);
		if (receivedNumber == 0) {
			// if didn't receive anything, then sleep for a while
			// and continue
			sleep(0.01);
			continue;
		}
		else if (receivedNumber > 1) {
			// TODO: change to log
			// if received something wrong, exit
			std::cerr << "Error: the thread cannot get the task!\n"; 
			break;
		}
		else if (receivedNumber < 0) {
			std::cerr << "Error: queue gave negative size\n";
			break;
		}
		
		// if received only 1 task, then it's correct
		// before the thread is running, set the thread to be
		// state running
		threadAgent->setRunning(true);
	
		// run task
		try {
			// then run the task and get return value
			returnValue = (*ppTask)[0].run();

			// dealing with the ret
			if (returnValue != RET_GOOD)
				throw returnValue;
		}
		catch(ReturnValue i) {
			// TODO: change to LOG
			std::cout << "Warning: exit status " << returnValue
				  << "\n"; 
		}
		catch(...) {
			// TODO: change to LOG
			// catch all other exceptions
			std::cerr << "Error: catched unhandled exception\n";	
		}

		// thread is done, finished running, so set the thread state to
		// be not running.
		threadAgent->setRunning(false);
	}
	pthread_exit(NULL);
}


// Those are non-static functions

ThreadPool::ThreadPool(uint32_t number) {
	// check if the number threads is too many
	if (number > MAX_NUM_THREADS) number = MAX_NUM_THREADS;

	// detection thread
	m_detectThread	= new Thread;

	// allocate number of threads and mutexes
	m_pThreads	= new Thread[number];
	m_pMutexes	= new Mutex[number];

	// initialize the queues for each thread 
	m_pQueues	= new Queue<Task*>[number];

	// allocate threadId memory
	m_threadAgents	= new ThreadAgent[number];

	// assign number with size
	m_size		= number;
}

ThreadPool::~ThreadPool() {
	delete m_detectThread;	

	delete[] m_pThreads;
	delete[] m_pQueues;
	delete[] m_pMutexes;
	delete[] m_threadAgents;
}

void ThreadPool::JoinAll() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return;
	}

	// TODO: use LOG instead
	std::cout << AT << "Joining all threads\n";
	for (uint32_t i = 0; i < m_size; i++) {
		// join the thread
		m_pThreads[i].join();
	}

	// since all the threads done their jobs
	// de-allocate the space
	deinitialize();
}

ReturnValue ThreadPool::CancelAll() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return RET_FAIL;
	}

	ReturnValue ret;

	// stop all the threads
	for (uint32_t i = 0; i < m_pInstance->m_size; i++) {
		std::cout << AT << "Canceling thread[" << i << "]";
		ret = (m_pInstance->m_pThreads[i]).cancel();
		std::cout << " Exit code: " << ret << std::endl;
	}

	std::cout << AT << "All the threads canceled\n";

	return RET_GOOD; 
}

void ThreadPool::add(Task* pTask, uint32_t id) {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return;
	}


	// if the id exceed the number of threads, mod it
	if (id > m_size)
		id = id % m_size;

	// lock the mutex
	m_pMutexes[id].lock();

	// add the mutex to queue according to the task
	m_pQueues[id].put(static_cast<Task**>(&pTask));

	// unlock the mutex
	m_pMutexes[id].unlock();
}

// assign the specific thread (id) to running on core
ReturnValue ThreadPool::setAffinity(uint32_t id, int cores) {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return RET_FAIL;
	}

	ReturnValue ret;
	std::cout << AT << "Setting thread[" << id << "] affinity: ";

	// set affinity
	ret = m_pThreads[id].setAffinity(cores);
	return ret;
}

uint32_t ThreadPool::size() const {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return 0;
	}

	return m_size;
}

// deadlock detection
// TODO: try to optimize it, loop detection
void ThreadPool::detection() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) {
		std::cout << "Please initialize first\n";
		return;
	}

	std::set<uint32_t> threadIdSet;
	Mutex* locking;

	for (uint32_t head = 0; head < m_size; ++head) {
		threadIdSet.clear();
		uint32_t current = head;
		bool loop = false;

		while (true) {
			// if the thread is already kept in the threadIdSet,
			// then loop detected.
			if (threadIdSet.find(current) != threadIdSet.end()) {
				loop = true;
				break;
			}

			threadIdSet.insert(current);
			locking = m_threadAgents[current].getLocking();
			bool found = false;

			// find which thread is holding the "locking"
			uint32_t i;
			for (i = 0; i < m_size; ++i) {
				std::set<Mutex*>& locked
					= m_threadAgents[i].getLocked();
				// if find the locking one 
				if (locked.find(locking) == locked.end())
					found = true;
			}

			if (true == found)
				// go next thread
				current = i;
			else
				// if not found, then the chain is end
				break;
		}

		if (true == loop) {
			// deadlock thread detected;
			std::cout << "!!! deadlock detected !!!\n";
		}
	}
}



