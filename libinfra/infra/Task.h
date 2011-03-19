#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>
#include <global.h>
#include <Object.h>

typedef struct TaskElement_t {
	uint32_t id;
	Task task;
} TaskElement;

class Task: Object {
public:
	virtual int run() = 0;
}

#endif /*  __TASK_H__ */
