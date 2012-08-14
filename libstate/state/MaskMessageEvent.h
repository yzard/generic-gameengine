// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef MASKMESSAGEEVENT_H
#define MASKMESSAGEEVENT_H

#include <state/IEvent.h>

class ByteStream;

class MaskMessageEvent : public IEvent, ISerializable {
public:
	MaskMessageEvent();
	virtual ~MaskMessageEvent();

	// public methods
	virtual void deserializeFrom(ByteStream& bs);
	virtual void deserializeTo(ByteStream& bs);

private:
	uint32_t	position_;	
	std::string	mask_;
	std::string	message_;
};

#endif // MASKMESSAGEEVENT_H

