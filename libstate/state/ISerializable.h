// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

class ByteStream;

class ISerializable {
public:
	virtual void serializeTo(ByteStream& bs) = 0;
	virtual void deserializeFrom(ByteStream& bs) = 0;
};

#endif // ISERIALIZABLE_H

