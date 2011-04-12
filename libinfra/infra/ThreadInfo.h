#ifndef __INFRA_THREADINFO_H__
#define __INFRA_THREADINFO_H__

#include <infra/Global.h>
#include <set>

struct ThreadInfo_t {
	uint32_t		id;		// the id inside of threadpool
	pthread_mutex_t		locking;	// the locks going to lock
	set<pthread_mutex_t>	locked;		// locked lock
	bool			running;	// is the thread running(true) or sleeping(false)?
};

typedef ThreadInfo		struct ThreadInfo_t;

#endif /* __INFRA_THREADINFO_H__ */

