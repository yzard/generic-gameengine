#include <infra/ThreadPool.h>

// the static variable for instance, make sure the instance to be
// only one
ThreadPool* ThreadPool::m_pInstance	= NULL;
Thread* ThreadPool::m_pThreads		= NULL;
Mutex* ThreadPool::m_pMutexes		= NULL;
Queue<Task*>* ThreadPool::m_pQueues	= NULL;
ThreadAgent* ThreadPool::m_threadAgents	= NULL;
Thread* ThreadPool::m_detectThread	= NULL;

// Singleton, ensure there is always only one instance
ThreadPool* ThreadPool::Instance(uint32_t number) {
	if (m_pInstance == NULL)
		m_pInstance = new ThreadPool(number);

	return m_pInstance;
}

// initialize function
void ThreadPool::initialize() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) return;

	uint32_t i;

	// Thread Agent structure initialization
	for (i = 0; i < m_pInstance->m_size; i++) {
		// ThreadPool id
		m_threadAgents[i].setId(i);

		// at the beginning, the thread is not running
		m_threadAgents[i].setRunning(false);
	}

	// set the entry point and parameters
	for (i = 0; i < m_pInstance->m_size; i++) {
		m_pThreads[i].setParameters(
			&ThreadPool::m_run,
			static_cast<void*>(&m_threadAgents[i])
		);
	}

	// Start create threads
	for (i = 0; i < m_pInstance->m_size; i++) {
		// TODO: Change to LOG
		std::cout << __FUNC_NAME__ << ": Creating thread[" << i << "] - ";

		// actually start the thread
		m_pThreads[i].start();
	}
}

// destroy the threadpool
void ThreadPool::deinitialize() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) return;

	// stop all the threads
	for (uint32_t i = 0; i < m_pInstance->m_size; i++) {
		std::cout << __FUNC_NAME__ << ": Canceling thread[" << i << "]\n";
		m_pThreads[i].cancel();
	}

	// destroy the instance of Threadpool is there is one
	delete m_pInstance;
	m_pInstance = NULL;
}

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
	if (NULL == m_pInstance) return;

	// TODO: change to log
	std::cout << __FUNC_NAME__ << ": Join All threads" << '\n';
	for (uint32_t i = 0; i < m_size; i++) {
		// join the thread
		m_pThreads[i].join();
	}
}

void ThreadPool::add(Task* pTask, uint32_t id) {
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
	ReturnValue ret;
	std::cout << __FUNC_NAME__ << ": Setting thread[" << id << "] affinity: ";

	// set affinity
	ret = m_pThreads[id].setAffinity(cores);
	return ret;
}

uint32_t ThreadPool::size() const {
	return m_size;
}

// static run function
void* ThreadPool::m_run(void* data) {
	Task**		ppTask;
	ThreadAgent*	threadAgent 	= static_cast<ThreadAgent*>(data);
	ReturnValue	ret;
	uint32_t	received;
	
	while (true) {
		received = m_pQueues[threadAgent->getId()].get(ppTask);
		if ( 1 == received) {
			// ready to start the thread runing
			threadAgent->setRunning(true);
	
			try {
				// then run the task and get return value
				ret = (*ppTask)[0].run();

				// dealing with the ret
				if (ret != RET_GOOD)
					throw ret;
			}
			catch(ReturnValue i) {
				// TODO: change to LOG
				std::cout << "Warning: exit status " << ret << "\n"; 
			}
			catch(...) {			// catch all other exceptions
				// TODO: change to LOG
				std::cerr << "Error: catched unhandled exception\n";	
			}

			// thread is done, finished running
			threadAgent->setRunning(false);
		}
		else if ( 0 == received ) {
			// if didn't received any task, then sleep a little bit
			sleep(0.01);
		}
		else {
			// TODO: change to log
			// if received something wrong, exit
			std::cerr << "Error: the thread cannot get the task!\n"; 
			break;
		}
	}
	pthread_exit(NULL);
}

// deadlock detection
// TODO: try to optimize it, loop detection
void ThreadPool::detection() {
	std::set<uint32_t> threadIdSet;
	Mutex* locking;

	for (uint32_t head = 0; head < m_pInstance->m_size; ++head) {
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
			for (i = 0; i < m_pInstance->m_size; ++i) {
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



