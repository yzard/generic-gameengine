#ifndef __INFRA_TASK_H__
#define __INFRA_TASK_H__

#include <infra/Global.h>

class Task {
public:
	Task() {}
	virtual ~Task() {};
	virtual ReturnValue run()	= 0;
};

#endif /*  __INFRA_TASK_H__ */
