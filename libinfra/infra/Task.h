#ifndef __TASK_H__
#define __TASK_H__
#include <global.h>

typedef struct TaskNode_t {
	uint32_t id;
	Task task;
	struct TaskNode_t* next;
} TaskNode;

class Task {
public:
	virtual int run() = 0;
}

#endif /*  __TASK_H__ */
