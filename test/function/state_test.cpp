// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <iostream>
#include <getopt>

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
			return EXIT_FAILURE;
		}
	}

	// main program



	return EXIT_SUCCESS;
}
