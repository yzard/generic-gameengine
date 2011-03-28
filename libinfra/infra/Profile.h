#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <infra/Global.h>
#include <iostream>
#include <time.h>

// the timestamp will always be the nano precision
#define Timestamp	uint64_t

/*
 * rdtsc count functions
 */
#ifdef __GNUC__

static inline void rdtsc(uint64_t* val) {
	uint32_t low, high, aux;
	__asm__ __volatile__("rdtscp" : "=a" (low) , "=d" (high), "=c" (aux));
	*val = ((uint64_t) high << 32) | low;
}

#else
#	error Need add support for this compiler.
#endif


/***************************************************************
 * the timstamp type definitions and methods                   *
 ***************************************************************/

// there is no need to put all those functions into
// class
namespace Clock {

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
#ifdef HAVE_CLOCK_GETTIME
	struct timespec ts;

#	if defined(CLOCK_MONOTONIC_RAW)
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
#	else
	clock_gettime(CLOCK_MONOTONIC, &ts);
#	endif

	return (ts.tv_sec * 1000000000LL + ts.tv_nsec );
#else
	return 0;
#endif
}

}

// The following are every useful macros

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

#endif /* __PROFILE_H__ */
