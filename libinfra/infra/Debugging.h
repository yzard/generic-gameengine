#ifndef __INFRA_DEBUGGING_H__
#define __INFRA_DEBUGGING_H__

#include <iostream>	// cerr
#include <string>	// string
#include <typeinfo>	// typeid
#include <cxxabi.h>	// __cxa_demangle

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// AT will give the const char string for file and line
#define AT __FILE__ ":" TOSTRING(__LINE__) ": "

// ATSTRING
#define ATSTRING(msg) std::string(std::string(AT) + std::string(msg))

// dump the information of variable name
// for example, like:
//     test.cpp:15: trace: type name: value
//     ^        ^               ^     ^
//     |filename|               |     |variable value
//              |line           |variable name
#define TRACE(variable)	do {								\
	int status;									\
	char *realname = abi::__cxa_demangle(typeid(variable).name(), 0, 0, &status); 	\
	std::cerr << AT << ": "								\
		  << "dump: "								\
		  << realname << " "							\
		  << #variable    << " = "						\
		  << '[' << variable << ']' << "\n";					\
	free(realname);									\
	} while (0)



#endif /* __INFRA_DEBUGGING_H__ */
