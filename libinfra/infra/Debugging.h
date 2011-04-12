#ifndef __INFRA_DEBUGGING_H__
#define __INFRA_DEBUGGING_H__

#include <iostream>
#include <typeinfo>
#include <cxxabi.h> // __cxa_demangle

// dump the information of variable name
// for example, like:
//     test.cpp:15: trace: type name: value
//     ^        ^               ^     ^
//     |filename|               |     |variable value
//              |line           |variable name
#define TRACE(variable)	do {								\
	int status;									\
	char *realname = abi::__cxa_demangle(typeid(variable).name(), 0, 0, &status); 	\
	std::cout << __FILE__ << ":"							\
		  << __LINE__ << ": "							\
		  << "dump: "								\
		  << realname << " "							\
		  << #variable    << " = "						\
		  << '[' << variable << ']' << "\n";					\
	free(realname);									\
	} while (0);

#endif /* __INFRA_DEBUGGING_H__ */
