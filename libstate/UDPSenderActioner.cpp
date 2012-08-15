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

bool UDPSenderActioner::send(const char* buffer, size_t size,
	char delimiter) const {
	size_t newSize = size + sizeof(delimiter);
	char newBuffer[newSize];

	memcpy(&newBuffer[0], &buffer, size);
	memcpy(&newBuffer[size], &delimiter, sizeof(delimiter));

	if result = sendto(socket_, &newBuffer, newSize, 0,
		(const sockaddr*)&address_, sizeof(address_));

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

void UDPSenderActioner::act(IEvent* event) {
	if (!connect())
		return;

	char delimiter = 0x01;
	ByteStream bs;
	event->serializeTo(bs);

	char buf[bs.size()];
	bs.copyTo(&buf[0]);

	send(&buf, bs.size(), delimiter);
}
