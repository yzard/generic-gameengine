#ifndef __DEBUGGING_H__
#define __DEBUGGING_H__

#include <iostream>

// dump the information of variable name
// for example, like:
//     test.cpp:15: dump: name: value
//     ^        ^         ^     ^
//     |filename|         |     |variable value
//              |line     |variable name
#define DUMP(name)			\
	std::cout << __FILE__ << ":"	\
		  << __LINE__ << ": "	\
		  << "dump: "		\
		  << #name    << "="	\
		  << name     << "\n";

#endif /* DEBUGGING_H__ */
