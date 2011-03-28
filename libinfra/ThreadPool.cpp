#include <infra/ThreadPool.h>

// the static variable for instance, make sure the instance to be
// only one
ThreadPool* ThreadPool::m_pInstance	= NULL;
pthread_t* ThreadPool::m_pThreads	= NULL;
pthread_mutex_t* ThreadPool::m_pMutexes	= NULL;
Queue<Task*>* ThreadPool::m_pQueues	= NULL;

// Singleton, ensure there is always only one instance
ThreadPool* ThreadPool::Instance(uint32_t number) {
	if (m_pInstance == NULL)
		m_pInstance = new ThreadPool(number);

	return m_pInstance;
}

// destroy the threadpool
void ThreadPool::Destroy() {
	// if the instance is not available, just return
	if (NULL == m_pInstance) return;

	// stop all the threads
	for (uint32_t i = 0; i < m_pInstance->m_size; i++) {
		std::cout << __FUNC_NAME__ << ": Canceling thread[" << i << "]\n";
		pthread_cancel(m_pInstance->m_pThreads[i]);
	}

	// destroy the instance of Threadpool is there is one
	delete m_pInstance;
	m_pInstance = NULL;
}

ThreadPool::ThreadPool(uint32_t number) {
	// check if the number threads is too many
	if (number > MAX_NUM_THREADS) number = MAX_NUM_THREADS;

	// allocate number of threads and mutexes
	m_pThreads	= new pthread_t[number];
	m_pMutexes	= new pthread_mutex_t[number];

	// initialize the queues for each thread 
	m_pQueues	= new Queue<Task*>[number];

	// assign number with size
	m_size		= number;	

	// initialize the pthread attribute
	pthread_attr_init(&m_attr);
	pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);

	uint32_t i;
	ReturnValue rc;

	// initialize all the mutex for writing
	for (i = 0; i < m_size; i++)
		pthread_mutex_init(&m_pMutexes[i], NULL);

	// Start create threads
	for (i = 0; i < m_size; i++) {
		// TODO: Change to LOG
		std::cout << __FUNC_NAME__ << ": Creating thread[" << i << "] - ";
		rc = pthread_create(&m_pThreads[i], &m_attr, &ThreadPool::m_run, static_cast<void*>(&i));
		if (rc) {
			// TODO: Change to LOG
			std::cout << "ERROR: return code from pthread_create() - "
				  << rc << std::endl;
			exit(-1);
		}
		else
			// TODO: Change to LOG
			std::cout << "Successfully created\n";
	}

	pthread_attr_destroy(&m_attr);
}

ThreadPool::~ThreadPool() {
	delete[] m_pThreads;
	delete[] m_pQueues;
	for (int i = 0; i < m_size; i++)
		pthread_mutex_destroy(&m_pMutexes[i]);
	delete[] m_pMutexes;
}

void ThreadPool::JoinAll() {
	if (NULL == m_pInstance) return;

	ReturnValue rc;
	// TODO: change to log
	std::cout << __FUNC_NAME__ << ": Join All threads" << std::endl;
	for (uint32_t i = 0; i < m_size; i++) {
		rc = pthread_join(m_pThreads[i], &m_status);
		if (rc != RET_GOOD) {
			// TODO: change to LOG
			errno = rc;
			perror("pthread_join");
		}
	}
}

void ThreadPool::add(Task** ppTask, uint32_t number) {
	// choose which queue you want add
	// need more sophisticate one

	// TODO: decide i
	uint32_t i = 0;

	// lock the mutex
	pthread_mutex_lock(&m_pMutexes[i]);

	// add the mutex to queue according to the task
	m_pQueues[i].put(ppTask, number);

	// unlock the mutex
	pthread_mutex_unlock(&m_pMutexes[i]);
}

ReturnValue ThreadPool::setAffinity(uint32_t num, int core) {
	// initialize cpuset variable with all zero
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	
	// TODO: support multiple core
	CPU_SET(core, &cpuset);

	std::cout << __FUNC_NAME__ << ": Setting thread[" << num << "] affinity: ";
	int ret;
	// set pthread affinity
	ret = pthread_setaffinity_np(m_pThreads[num], sizeof(cpu_set_t), &cpuset);
	if (ret != RET_GOOD) {
		// TODO: log error message 
		std::cout << "Fail to set affinity"; 
		errno = ret;
		perror("pthread_setaffinity_np");
		return RET_FAIL;
	}

	// TODO: Log the affinity
	std::cout << "set to core " << core << std::endl;

	return RET_GOOD;
}

uint32_t ThreadPool::size() {
	return m_size;
}

// static run function
void* ThreadPool::m_run(void* data) {
	Task**		ppTask;
	uint32_t	number = *(static_cast<uint32_t*>(data));
	uint32_t	received;
	
	while (true) {
		// TODO: only support one task at once
		received = m_pQueues[number].get(ppTask, 1);

		if (0 == received)
			// if didn't get any task, then sleep
			sleep(0.01);
		else if ( 1 == received)
			// if get 1 task, then run it
			(*ppTask)[0].run();
		else
			// TODO: change to LOG
			std::cout << "Get FIFO wrong" << std::endl;
	}
	pthread_exit(NULL);
}


