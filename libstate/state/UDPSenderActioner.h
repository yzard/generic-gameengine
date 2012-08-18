// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef UDPSENDERACTIONER_H
#define UDPSENDERACTIONER_H

#include <state/IActioner.h>

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class IEvent;

class UDPSenderActioner : public IActioner {
public:
	UDPSenderActioner(const std::string&, uint16_t);
	virtual ~UDPSenderActioner();

	bool connect();
	bool send(const char* buf, size_t size) const;
	bool assignAddress(const std::string&, uint16_t);

	// interface IActioner
	virtual bool act(IEvent* event);

private:
	int socket_;
	struct sockaddr_in address_;
};

#endif // UDPSENDERACTIONER_H
