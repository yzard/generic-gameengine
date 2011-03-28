#ifndef __TASK_H__
#define __TASK_H__

#include <infra/Global.h>
#include <infra/Object.h>

class Task: Object {
public:
	virtual TaskId setId()		= 0;
	virtual TaskId getId()		= 0;
	virtual ReturnValue run()	= 0;

	virtual ~Task();
};

#endif /*  __TASK_H__ */
