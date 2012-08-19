// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <iostream>
#include <cstdlib>

#include <state/ByteStream.h>

void usage(const char* program) {
	std::cout << "usage: " << program << " <options>"	<< std::endl;
	std::cout << "option:"					<< std::endl;
	std::cout << "-h                       this message"	<< std::endl;
}

int main(int argc, char* argv[]) {
	// options default value
	
	int c;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
		case '?':
		default:
			usage(argv[0]);
			return EXIT_SUCCESS;
		}
	}

	// process non-option parameters
	for (int i = optind; i < argc; ++i) {
		std::cout << "Non-option argument " << argv[i] << std::endl;
		return EXIT_FAILURE;
	}

	char* buffer = new char[512];
	ByteStream bs;

	bs << "1";
	memset(buffer, 0, 512);
	bs.copyTo(buffer, 1);
	std::cout << bs.size() << "/" << bs.capacity() << ": "
		<< bs << std::endl;

	bs << "2";
	memset(buffer, 0, 512);
	bs.copyTo(buffer, 2);
	std::cout << bs.size() << "/" << bs.capacity() << ": "
		<< bs << std::endl;

	bs << "34";
	memset(buffer, 0, 512);
	bs.copyTo(buffer, 4);
	std::cout << bs.size() << "/" << bs.capacity() << ": "
		<< bs << std::endl;

	bs << "567";
	memset(buffer, 0, 512);
	bs.copyTo(buffer, 4);
	std::cout << bs.size() << "/" << bs.capacity() << ": "
		<< bs << std::endl;

	return EXIT_SUCCESS;
}
