// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef MASKMESSAGEEVENT_H
#define MASKMESSAGEEVENT_H

#include <Global.h>

#include <state/IEvent.h>
#include <state/ISerializable.h>

class ByteStream;

class MaskMessageEvent : public IEvent, ISerializable {
public:
	MaskMessageEvent();
	virtual ~MaskMessageEvent();

	std::string mask();
	void setMask(const std::string&);
	std::string message();
	void setMessage(const std::string&);
	uint32_t position();
	void setPosition(uint32_t);

	// public methods
	virtual void deserializeFrom(ByteStream& bs);
	virtual void deserializeTo(ByteStream& bs);

private:
	uint32_t	position_;	
	std::string	mask_;
	std::string	message_;
};

#endif // MASKMESSAGEEVENT_H

