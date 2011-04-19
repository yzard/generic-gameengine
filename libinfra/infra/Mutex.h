#ifndef __INFRA_MUTEX_H__
#define __INFRA_MUTEX_H__

#include <infra/Global.h>
#include <pthread.h>

class Mutex {
public:
	Mutex ();
	Mutex (const char* str);
	Mutex (std::string str);

	~Mutex ();

	void lock();

	void unlock();

	void setDescription(std::string str);

	friend std::ostream& operator<<(std::ostream& os, Mutex& m);

private:
	pthread_mutex_t		mtx;
	std::string		description;
};



#endif /* __INFRA_MUTEX_H__ */
