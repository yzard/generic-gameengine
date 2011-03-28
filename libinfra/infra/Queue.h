#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <infra/Global.h>
#include <cstring>
#include <stdint.h>

/* This is a lock-free FIFO queue template implementation.
 * the queue size has to be 2^n
 * the Type can be char, int, and any fixed size of type
 * if for class, the POINTER of class is highly recommanded.
 * For example:
 * 	Queue<int> 	int_queue;
 *	Queue<Task*>	task_queue; // Task is a class here.
 */

#define DEFAULT_QUEUE_SIZE 1024

template <class Type>
class Queue {
private:
	Type*		buffer;		// Ring buffer
	uint32_t	size;		// size of the buffer
	uint32_t	in;		// index for write
	uint32_t	out;		// index for read
	uint32_t	typeSize;	// sizeof(Type)

public:
	// Initialize the FIFO with size
	// the size should be 2^n
	Queue(uint32_t init_size = DEFAULT_QUEUE_SIZE) {
		// check if the size is 2^n
		if (init_size & (init_size - 1)) {
			// the size is not 2^n, set it
			// to default queue size
			init_size = DEFAULT_QUEUE_SIZE;
		};

		size 		= init_size;

		// initialize the buffer with type T
		buffer 		= new Type[size];

		// if in == out, means empty
		in		= 0;
		out		= 0;

		// sizeof(Type), will be used for memcpy
		typeSize = sizeof(Type);
	}
	~Queue() {
		delete[] buffer;
	}

	// the method for thread to put stuff in the queue
	// can be number of stuff
	uint32_t put(Type* elements, uint32_t len) {
		uint32_t endLen;

		// size - (in - out) means the free space of the queue
		// if the number is larger than the free space of
		// FIFO, then use the free space instead
		len = minimal(len, size - (in - out));

		// Ensure we sample the out index before we start putting
		// bytes into buffer
		mb();

		// first put the data starting from in to buffer end
		endLen = minimal(len, size - (in & (size-1)));
		memcpy(buffer + (in & (size-1)), elements, endLen*typeSize);

		// then put the rest at the beggining of the buffer
		memcpy(buffer, elements + endLen, (len-endLen)*typeSize);
		
		// Ensure we add the bytes to the buffer before we
		// update the in index
		wmb();

		in += len;

		// return the length of elements has been written.
		return len;			
	};

	// the method for another thread to get stuff off the queue
	uint32_t get(Type* elements, uint32_t len) {
		uint32_t endLen;

		len = minimal(len, in - out);

		// ensure sample the in index before we start removing
		// bytes from the buffer
		rmb();

		// first get the data from out to the end of the buffer
		endLen = minimal(len, size - (out & (size - 1)));
		memcpy(elements, buffer + (out & (size - 1)), endLen*typeSize);

		// then get the rest data from the begining of the buffer
		memcpy(elements + endLen, buffer, (len - endLen)*typeSize);

		// ensure we remove the bytes from the buffer before we
		// update the out index
		mb();

		out += len;

		// return the length of elements has been read.
		return len;
	}

	uint32_t length() {
		return size;
	}

	uint32_t count() {
		return in - out;
	}

};

#endif /*  __QUEUE_H__ */
