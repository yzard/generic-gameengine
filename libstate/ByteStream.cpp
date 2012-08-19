// vim: tabstop=8 shiftwidth=8 noexpandtab
#include <Global.h>
#include <Debugging.h>
#include <state/ByteStream.h>

#include <cmath>

ByteStream::ByteStream()
	: in_(0)
	, out_(0)
	, buffer_(NULL)
	, capacity_(0) {
}

ByteStream::~ByteStream() {
	if (buffer_)
		delete buffer_;
}

uint32_t ByteStream::size() {
	return in_ - out_;
}

uint32_t ByteStream::capacity() {
	return capacity_;
}

bool ByteStream::empty() {
	return (in_ == out_);
}

void ByteStream::realloc(size_t newSize) {
	size_t capacity = 1UL << (uint32_t)log2((double)(newSize)) + 1;

	//assert(out_ <= in_)
	char* newBuffer = new char[capacity];
	if (!buffer_) {
		buffer_		= newBuffer;
		capacity_	= capacity;
		in_		= 0;
		out_		= 0;
		return;
	}

	// copy raw to new buffer
	copyRaw(newBuffer);

	// free old buffer_
	delete buffer_;

	// assign new buffer
	buffer_ 	= newBuffer;
	capacity_	= capacity;
	in_		= in_ - out_;
	out_		= 0;

	return;
}

void ByteStream::copyTo(char* buffer, size_t len) {
	if (len < size())
		return;

	// copy raw to new buffer
	copyRaw(buffer);
}

void ByteStream::copyRaw(char* buffer) {
	uint32_t in = in_ & (capacity_ -1);
	uint32_t out = out_ & (capacity_ -1);

	if (out < in) {
		memcpy(buffer, buffer_ + out, in - out);
	}
	else {
		memcpy(buffer, buffer_ + out, capacity_ - out);
		memcpy(buffer + (capacity_ - out), buffer_, in + 1);
	}
}

void ByteStream::input(const char* pointer, size_t len) {
	if (len > capacity_ - (in_ - out_))
		realloc(in_ - out_ + len);

	uint32_t l = min(len, capacity_ - (in_ & (capacity_ - 1)));
	memcpy(buffer_ + (in_ & (capacity_ -1)), pointer, l);
	memcpy(buffer_, pointer + l, len - l);
	in_ += len;
}

void ByteStream::output(char* pointer, size_t len) {
	if (len > (in_ - out_))
		return;

	uint32_t l = min(len, capacity_ - (out_ & (capacity_ - 1)));
	memcpy(pointer, buffer_ + (out_ & (capacity_ -1)), l);
	memcpy(pointer + l, buffer_, len - l);
	out_ += len;
}

ByteStream& operator<<(ByteStream& bs, char value) {
	bs.input((const char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator<<(ByteStream& bs, int value) {
	bs.input((const char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator<<(ByteStream& bs, unsigned int value) {
	bs.input((const char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator<<(ByteStream& bs, long value) {
	bs.input((const char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator<<(ByteStream& bs, unsigned long value) {
	bs.input((const char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator<<(ByteStream& bs, const char* value) {
	uint32_t size = strlen(value);
	bs.input((const char*)&size, sizeof(uint32_t));
	bs.input(value, size);
	return bs;
}

ByteStream& operator<<(ByteStream& bs, const std::string& value) {
	uint32_t size = value.size();
	bs.input((const char*)&size, sizeof(uint32_t));
	bs.input(value.c_str(), size);
	return bs;
}

ByteStream& operator>>(ByteStream& bs, char& value) {
	bs.output((char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator>>(ByteStream& bs, int& value) {
	bs.output((char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator>>(ByteStream& bs, unsigned int& value) {
	bs.output((char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator>>(ByteStream& bs, long& value) {
	bs.output((char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator>>(ByteStream& bs, unsigned long& value) {
	bs.output((char*)&value, sizeof(value));
	return bs;
}

ByteStream& operator>>(ByteStream& bs, char* value) {
	uint32_t size;
	bs.output((char*)&size, sizeof(uint32_t));
	value = new char[size+1];
	bs.output(value, size);
	value[size] = '\0';
	return bs;
}

ByteStream& operator>>(ByteStream& bs, std::string& value) {
	uint32_t size;
	bs.output((char*)&size, sizeof(uint32_t));
	char buf[size+1];
	bs.output((char*)&buf, size);
	buf[size] = '\0';
	value = buf;
	return bs;
}


std::ostream& operator<<(std::ostream& os, const ByteStream& rhs) {
	if (rhs.out_ == rhs.in_)
		return os;

	uint32_t in = rhs.in_ & (rhs.capacity_ - 1);
	uint32_t out = rhs.out_ & (rhs.capacity_ - 1);

	os << std::hex << std::uppercase;
	if (out < in) {
		for (uint32_t i = out; i < (in - out); ++i) {
			unsigned char chr = (rhs.buffer_)[i];
			os << (int)chr << " ";
		}
	}
	else {
		for (uint32_t i = out; i < (rhs.capacity_ - in); ++i) {
			unsigned char  chr = (rhs.buffer_)[i];
			os << (int)chr << " ";
		}

		for (uint32_t i = 0; i < in + 1; ++i) {
			unsigned char chr = (rhs.buffer_)[i];
			os << (int)chr << " ";
		}
	}
	os << std::dec;
	return os;
}
