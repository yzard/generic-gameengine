#ifndef __INFRA_TASK_H__
#define __INFRA_TASK_H__

#include <infra/Global.h>

class Task {
public:
	virtual ReturnValue run()	= 0;

	virtual ~Task();
private:

};

#endif /*  __INFRA_TASK_H__ */
