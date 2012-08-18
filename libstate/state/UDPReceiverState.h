// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef UDPRECEIVERSTATE_H
#define UDPRECEIVERSTATE_H

#include <Global.h>

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class UDPReceiverState {
public:
	UDPReceiverState(const std::string& host, uint16_t port);
	virtual ~UDPReceiverState();

	// interface IMessageReceiver
	virtual bool listen();
	virtual bool receive(char* buffer, size_t size);

	bool assignAddress(const std::string& host, uint16_t port);

private:
	int socket_;
	struct sockaddr_in address_;
};

#endif // UDPRECEIVERSTATE_H

