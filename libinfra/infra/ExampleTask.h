#ifndef __INFRA_EXAMPLETASK_H__
#define __INFRA_EXAMPLETASK_H__

#include <Global.h>
#include <infra/Task.h>

class ExampleTask: public Task {
public:
	ExampleTask();
	~ExampleTask();

	ReturnValue run();
};

#endif /* __INFRA_EXAMPLETASK_H__ */
