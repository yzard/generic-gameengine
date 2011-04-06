#include <infra/ExampleTask.h>

ExampleTask::ExampleTask() {
}

ExampleTask::~ExampleTask() {
}

ReturnValue ExampleTask::run() {
	std::cout << "What a fool zhuo is!\n";
	return RET_GOOD;
}
