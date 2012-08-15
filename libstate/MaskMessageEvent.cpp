#include <state/MaskMessageEvent.h>
#include <state/ByteStream.h>

MaskMessageEvent::MaskMessageEvent() {
}

MaskMessageEvent::~MaskMessageEvent() {
}

std::string mask() {
	return mask_;
}

void setMask(const std::string& mask) {
	mask_ = mask;
}

std::string message() {
	return message_;
}

void setMessage(const std::string& message) {
	message_ = message;
}

uint32_t position() {
	return position_;
}

void setPosition(uint32_t position) {
	position_ = position;
}

void MaskMessageEvent::serializeTo(ByteStream& bs) {
	//bs << position_ << mask_ << message_;
}

void MaskMessageEvent::deserializeFrom(ByteStream& bs) {
	// bs >> position_ >> mask_ >> message_;
}
