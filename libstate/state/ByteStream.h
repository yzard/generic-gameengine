// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <Global.h>
#include <iostream>
#include <string>

class ByteStream {
public:
	ByteStream();
	virtual ~ByteStream();

	uint32_t size();
	bool empty();
	void copyTo(char* buffer);

	friend ByteStream& operator<<(ByteStream& bs, int value);
	friend ByteStream& operator<<(ByteStream& bs, unsigned int value);
	friend ByteStream& operator<<(ByteStream& bs, long value);
	friend ByteStream& operator<<(ByteStream& bs, unsigned long value);
	friend ByteStream& operator<<(ByteStream& bs, const char* value);
	friend ByteStream& operator<<(ByteStream& bs, const std::string& value);

	friend ByteStream& operator>>(ByteStream& bs, int& value);
	friend ByteStream& operator>>(ByteStream& bs, unsigned int& value);
	friend ByteStream& operator>>(ByteStream& bs, long& value);
	friend ByteStream& operator>>(ByteStream& bs, unsigned long& value);
	friend ByteStream& operator>>(ByteStream& bs, char* value);
	friend ByteStream& operator>>(ByteStream& bs, std::string& value);

	friend std::ostream& operator<<(std::ostream& os, const ByteStream& bs);

private:
	void realloc(size_t newSize);
	void input(const char* value, size_t len);
	void output(char* value, size_t len);

	uint32_t in_;
	uint32_t out_;
	char* buffer_;
	size_t capacity_;
};

#endif // BYTESTREAM_H

