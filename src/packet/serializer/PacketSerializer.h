
#pragma once

#include <memory>
#include "packet/Packet.h"

typedef uint8_t Byte;

class PacketSerializer {
public:
	PacketSerializer(size_t n);
	PacketSerializer(const Byte *bytes, size_t len);
	~PacketSerializer();

public:
	//get
	template <class T> const T &get(size_t i);
	//set
	template <class T> void set(size_t i, const T &d);
	//read
	template <class T> const T &read();
	//write
	template <class T> void write(const T &d);

	void resetReader();
	void resetWriter();
	void seekReader(size_t offset);
	void seekWriter(size_t offset);

	Byte *getBuffer();
	void resize(size_t n);

private:
	Byte *reader_ptr;
	Byte *writer_ptr;
	Byte *base_ptr;
	size_t buff_len;
	std::allocator<Byte> allocator;
};