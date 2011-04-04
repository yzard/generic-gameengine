#ifndef __EXAMPLETASK_H__
#define __EXAMPLETASK_H__

#include <infra/Task.h>

class ExampleTask: public Task {
public:
	ExampleTask();
	~ExampleTask();

	ReturnValue run();
	// TODO: implement all
}

#endif /* __EXAMPLETASK_H__ */
