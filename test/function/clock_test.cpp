#include <iostream>
#include <infra/Profile.h>

int main() {
	// show the monotonic time
	// the latency for doing nothing
	// with take 200 ~ 300 ns
	CLOCK_INIT(mono);
	CLOCK_MONO_BEGIN(mono);
	CLOCK_MONO_END(mono);
	CLOCK_PRINT(mono);
}
