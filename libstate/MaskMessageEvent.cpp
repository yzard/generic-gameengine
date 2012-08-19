#include <state/MaskMessageEvent.h>
#include <state/ByteStream.h>

MaskMessageEvent::MaskMessageEvent(const std::string& name)
	: IEvent(name, "MaskMessageEvent")
	, position_(0)
	, mask_()
	, message_() {
}

MaskMessageEvent::~MaskMessageEvent() {
}

std::string MaskMessageEvent::mask() {
	return mask_;
}

void MaskMessageEvent::setMask(const std::string& mask) {
	mask_ = mask;
}

std::string MaskMessageEvent::message() {
	return message_;
}

void MaskMessageEvent::setMessage(const std::string& message) {
	message_ = message;
}

uint32_t MaskMessageEvent::position() {
	return position_;
}

void MaskMessageEvent::setPosition(uint32_t position) {
	position_ = position;
}

void MaskMessageEvent::serializeTo(ByteStream& bs) {
	bs << position_ << mask_ << message_;
}

void MaskMessageEvent::deserializeFrom(ByteStream& bs) {
	bs >> position_ >> mask_ >> message_;
}
