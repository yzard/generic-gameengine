#include <iostream>
#include <infra/Profile.h>

int main() {
	CLOCK_COMPACT_INIT(compact);
	CLOCK_COMPACT_MONO_BEGIN(compact);
	CLOCK_COMPACT_MONO_END(compact);
	CLOCK_COMPACT_PRINT(compact);

	// show the monotonic time
	// the latency for doing nothing
	// with take 200 ~ 300 ns
	CLOCK_INIT(mono);
	CLOCK_MONO_BEGIN(mono);
	CLOCK_MONO_END(mono);
	CLOCK_PRINT(mono);
}
