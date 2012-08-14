#ifndef __INFRA_THREADAGENT_H__
#define __INFRA_THREADAGENT_H__

#include <Global.h>
#include <infra/Mutex.h>
#include <set>

// the ThreadAgent is the wrapper of mutex operations.
// its benifits are exposes the locks information that
// threads hold, for ThreadPool usage, which can achieve
// deadlock detection on the fly.

class ThreadAgent {
public:
	// use this method to lock, 
	ReturnValue lock(Mutex* pMutex) {
		// TODO: consider when the mutex already locked by you

		// because you are going to lock the pMutex
		// record the mutex you are going to lock
		locking = pMutex;

		// lock the mutex you want lock
		// if this operation blocked, the locking will
		// always pointed to pMutex;
		pMutex->lock();

		// lock the agent lock, ready to update information
		agentLock.lock();

		// the mutex has been successfully locked.
		locking = NULL;

		// move the mutex to the locked set, the set has recorded
		// all the locks the thread is holding
		locked.insert(pMutex);

		// unlock the agent lock
		agentLock.unlock();
	};

	// use this method to unlock 
	ReturnValue unlock(Mutex* pMutex) {
		// TODO: consider if the mutex you didn't locked yet and run this function

		// unlock the target mutex
		pMutex->unlock();

		// lock the agent lock
		agentLock.lock();

		// remove the target mutex from locked set
		locked.erase(pMutex);

		// unlock the agent lock
		agentLock.unlock();
	};

	ThreadAgent() {
		// when initialize, the running should be false
		running	= false;

		// the locking is empty, this thread is not locking anything
		// at the beginning
		locking = NULL;
	}

	~ThreadAgent() {
	}


	void setId(uint32_t newId) {
		id = newId;
	}

	uint32_t getId() {
		return id;
	}

	Mutex* getLocking() {
		return locking;
	}

	// set the running status of the thread
	void setRunning(bool value) {
		running = value;
	}

	std::set<Mutex*>& getLocked() {
		return locked;
	}
	
private:
	Mutex			agentLock;	// this is the mutex when access ThreadAgent structure need
						// be locked.
	uint32_t		id;		// the id inside of threadpool
	Mutex*			locking;	// the locks going to lock
	std::set<Mutex*>	locked;		// locked lock
	bool			running;	// is the thread running(true) or sleeping(false)?
};

#endif /* __INFRA_THREADAGENT_H__ */

