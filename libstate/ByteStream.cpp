#include <state/ByteStream.h>

#include <cmath>


ByteStream::ByteStream()
	: in_(0)
	, out_(0)
	, buffer_(NULL)
	, capacity_(0) {
}

ByteStream::~ByteStream() {
}

void ByteStream::realloc(size_t newSize) {
	size_t newCapacity = 1 << ((size_t)log2(newSize) + 1)
	if (newCapacity <= capacity_)
		return;

	char* newBuffer = new char[newCapacity];
	if (!buffer_) {
		buffer_		= newBuffer;
		in_		= 0;
		out_		= 0;
		capacity_	= newCapacity;
		return;
	}


	in_%capacity_



	
}

void ByteStream::in(const void* value, size_t size) {

}

void ByteStream::out(void* value) {

}

ByteStream& operator<<(ByteStream& bs, const char* value) {
	size_t valueSize = strlen(value);
	const void* valuePointer = value;
	bs.in(valuePointer, valueSize);
	return bs;
}
