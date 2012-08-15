// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef UDPSENDERACTIONER_H
#define UDPSENDERACTIONER_H

class IEvent;

class UDPSenderActioner : public IActioner {
public:
	UDPSenderActioner(const std::string&, uint16_t);
	virtual ~UDPSenderActioner();

	bool connect();
	bool send(const char* buf, size_t size, char delimiter);
	bool assignAddress(const std::string&, uint16_t);

	// interface IActioner
	virtual void act(IEvent* event);

private:
	int socket_;
	struct netaddr_in address_;

};

#endif // UDPSENDERACTIONER_H

