// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <state/UDPSenderActioner.h>
#include <state/IEvent.h>
#include <state/ByteStream.h>

#include <iostream>

UDPSenderActioner::UDPSenderActioner(const std::string& host,
	uint16_t port)
	: socket_(-1)
	, address_(){
	assignAddress(host, port);
}

UDPSenderActioner::~UDPSenderActioner() {
	close(socket_);
}

bool UDPSenderActioner::connect() {
	if (socket_ != -1) {
		std::cout << "socket already opened" << std::endl;
		return true;
	}

	socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket_ == -1) {
		perror("socket");
		return false;
	}
	return true;
}

bool UDPSenderActioner::send(const char* buffer, size_t size) const {
	socklen_t addrSize = sizeof(address_);

	int result = sendto(socket_, &buffer, size, 0,
		(const sockaddr*)&address_, addrSize);

	if (result == -1) {
		perror("sendto");
		return false;
	}
	return true;
}

bool UDPSenderActioner::assignAddress(const std::string& host, uint16_t port) {
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

bool UDPSenderActioner::act(IEvent* event) {
	if (!connect())
		return false;

	char delimiter = 0xFF;
	ByteStream bs;

	// record type first
	bs << event->type();

	// serialize data
	event->serializeTo(bs);

	// append delimiter at the end
	bs << delimiter;

	// create buffer
	char buf[bs.size()];

	// copy stream content to buffer
	bs.copyTo(&buf[0]);

	// send
	send(&buf[0], bs.size());

	return true;
}
