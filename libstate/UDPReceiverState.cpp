// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/UDPReceiverState.h>

#include <iostream>
#include <string>

#define BUFFER_LENGTH 512

UDPReceiverState::UDPReceiverState(const std::string& host, uint16_t port)
	: socket_(-1)
	, address_() {
	assignAddress(host, port);
}

UDPReceiverState::~UDPReceiverState() {
	if (socket_)
		close(socket_);
}

bool UDPReceiverState::listen() {
	socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket_ == -1) {
		perror("socket");
		return false;
	}

	if (bind(socket_, (const sockaddr*)&address_, sizeof(address_)) == -1) {
		perror("bind");
		return false;
	}

	char buffer[BUFFER_LENGTH];

	// sender address
	struct sockaddr_in senderAddress;
	socklen_t addrSize = sizeof(senderAddress);

	// start receive
	for (;;) {
		size_t size = recvfrom(socket_, &buffer, sizeof(buffer), 0,
			(sockaddr*)&senderAddress, &addrSize);
		memset(buffer+size, 0, BUFFER_LENGTH - size);
		receive(buffer,size);
	}
}

bool UDPReceiverState::receive(char* buffer, size_t size) {
	std::cout << size << std::endl;
	return true;
}

bool UDPReceiverState::assignAddress(const std::string& host, uint16_t port) {
	memset((char*)&address_, 0, sizeof(address_));
	address_.sin_family = AF_INET;
	address_.sin_port = htons(port);
	if (inet_aton(host.c_str(), &address_.sin_addr) == 0) {
		std::cout << "convert host:port to struct socketaddr_in failed"
			<< std::endl;
		return false;
	}
	return true;
}
