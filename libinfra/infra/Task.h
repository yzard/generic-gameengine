#ifndef __TASK_H__
#define __TASK_H__

#include <infra/Global.h>

class Task {
public:
	virtual ReturnValue run()	= 0;

	virtual ~Task();
private:

};

#endif /*  __TASK_H__ */
