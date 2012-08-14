#include <state/MaskMessageEvent.h>
#include <state/ByteStream.h>

MaskMessageEvent::MaskMessageEvent() {
}

MaskMessageEvent::~MaskMessageEvent() {
}

void MaskMessageEvent::serializeTo(ByteStream& bs) {
	//bs << position_ << mask_ << message_;
}

void MaskMessageEvent::deserializeFrom(ByteStream& bs) {
	// bs >> position_ >> mask_ >> message_;
}
