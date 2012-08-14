// vim: tabstop=8 shiftwidth=8 noexpandtab
#ifndef BYTESTREAM_H
#define BYTESTREAM_H

class ByteStream {
public:
	ByteStream();
	virtual ~ByteStream();

	friend ByteStream& operator<<(ByteStream& bs, const char* value);


private:
	void realloc(size_t newSize);
	void in(void* value, size_t size);
	void out(void* value, size_t& size);

	uint32_t in_;
	uint32_t out_;
	char* buffer_;
	size_t capacity_;
};

#endif // BYTESTREAM_H

