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

	Clock::StructRdtsc s, e;
	uint64_t d;

	for (int i = 0; i < 100; i++) {
		Clock::rdtsc(s);
		Clock::rdtsc(e);
	
		// see how many cycles rdtsc needs
		d = e.cycles - s.cycles;
	
		std::cout << d << std::endl;
	}
}
