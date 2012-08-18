#ifndef __INFRA_PROFILE_H__
#define __INFRA_PROFILE_H__

#include <Global.h>
#include <iostream>
#include <sys/time.h>

#if defined(__MACH__)
#	include <mach/mach_time.h>
#endif

// the timestamp will always be the nano precision
#define Timestamp	uint64_t
#define Cycles		uint64_t


/***************************************************************
 * the timstamp type definitions and methods                   *
 ***************************************************************/

// there is no need to put all those functions into
// class
namespace Clock {

// since C99 standard suggest not use static to enforce the localize
// of function in the compilation unit, so use anonymous namespace
// instead.
namespace {

// this is the structure for recording rdtsc instructions reads
// the id field is for core i7, rdtscp can retrieve the processor
// id when doing rdtsc too.
struct StructRdtsc {
	uint64_t cycles;	// 64 bits cycles
	uint32_t id;		// the processor id
};

// rdtsc count functions
#ifdef __GNUC__
inline void rdtsc(StructRdtsc& record) {
	// serailization
	// this assembly code will take
	// 100 cycles
	__asm__ __volatile__(
		"xorl %%eax,%%eax;"
		"cpuid;"
	::: "%rax", "%rbx", "%rcx", "rdx");

	// use rdtscp if your cpu is core i7 above
	// then you don't need serialize, that's because of out of
	// order execute
	// __asm__ __volatile__(
	//	"rdtscp"
	//	: "=A" (record.cycles), "=c" (record.id));

	__asm__ __volatile__("rdtsc" : "=A" (record.cycles));
}
#else
#	error Need add rdtsc() support for this compiler.
#endif

// Return the CPU Hz
// TODO: finish it
inline Cycles CPUHz() {
	Cycles s, e;
	return 0;
}

// the system clock functions
inline Timestamp realTime() {
#ifdef HAVE_CLOCK_GETTIME
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (ts.tv_sec * 1000000000LL + ts.tv_nsec );
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000000LL + tv.tv_usec * 1000LL );
#endif
}

// Monotonic time is the time when real time clock has been
// adjusted, the related offset will be calculated too, so
// ideally the monotonic time should never skewed. But if
// the offset is not correctly calculated, the monotonic time
// might be wrong, so we can use CLOCK_MONOTONIC_RAW time.
// Similar to monotonic time, Raw time is the hardware-based time
// that will not be adjusted by NTP, the support if this needs
// >= Linux 2.6.28; Linux-specific
inline Timestamp monoTime() {
#if defined(HAVE_CLOCK_GETTIME)
	struct timespec ts;

#	if defined(CLOCK_MONOTONIC_RAW)
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
#	else
	clock_gettime(CLOCK_MONOTONIC, &ts);
#	endif

	return (ts.tv_sec * 1000000000LL + ts.tv_nsec );
#elif defined(__MACH__)
	static mach_timebase_info_data_t info = {0,0};

	if (info.denom == 0)
		mach_timebase_info(&info);

	return mach_absolute_time() * (info.numer / info.denom);
#else
#	warn No Monotonic time support!
	return 0;
#endif
}

}

}

// Convert timespec to Timestamp
#define TS_TIMESTAMP(ts)	((ts).tv_sec * 1000000000LL + (ts).tv_nsec )

// Convert timeval to Timestamp
#define TV_TIMESTAMP(tv)	((tv).tv_sec * 1000000000LL + (tv).tv_usec * 1000LL )

// The following are useful macros

// initialize the variable, this macro should be used
// combined with CLOCK_REAL_BEGIN, CLOCK_REAL_END,
// or CLOCK_MONO_BEGIN, CLOCK_MONO_END with the same
// variable name.
#define CLOCK_INIT(name)				\
	uint64_t name##_begin = 0, name##_end = 0;

// the macro that will easily to measure the latencies
#define CLOCK_REAL_BEGIN(name)				\
	do {						\
		name##_begin = Clock::realTime();	\
	} while(0)

#define CLOCK_REAL_END(name)				\
	do {						\
		name##_end = Clock::realTime();		\
	} while(0)

#define CLOCK_MONO_BEGIN(name)				\
	do {						\
		name##_begin = Clock::monoTime();	\
	} while(0)

#define CLOCK_MONO_END(name)				\
	do {						\
		name##_end = Clock::monoTime();		\
	} while(0)

#define CLOCK_PRINT(name)				\
	do {						\
		uint64_t latency;			\
		latency = name##_end - name##_begin;	\
		std::cout << __FILE__ << ":"		\
			  << __LINE__ << ": "		\
			  << "Latency: "		\
			  << #name    << "="		\
			  << latency  << " ns\n";	\
	} while (0)

#endif /* __INFRA_PROFILE_H__ */
