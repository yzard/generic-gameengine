#ifndef IEVENT_H
#define IEVENT_H

#include <state/ISerializable.h>

#include <string>

class ByteStream;

class IEvent : public ISerializable {
public:
	IEvent(const std::string& name, const std::string& type);
	~IEvent();

	virtual void serializeTo(ByteStream& bs) = 0;
	virtual void deserializeFrom(ByteStream& bs) = 0;

	std::string name() const;
	std::string type() const;

protected:
	std::string name_;
	std::string type_;
};

#endif // IEVENT_H

