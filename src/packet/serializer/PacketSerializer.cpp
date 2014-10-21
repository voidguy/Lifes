
#include "packet/serializer/PacketSerializer.h"
#include <algorithm>

PacketSerializer::PacketSerializer(size_t n): 
	buff_len(n) {
	base_ptr = allocator.allocate(n);
	resetReader();
	resetWriter();
}
PacketSerializer::PacketSerializer(const Byte *bytes, size_t len): 
	PacketSerializer(len) {
	std::uninitialized_copy(bytes, bytes + len, base_ptr);
}
PacketSerializer::~PacketSerializer() {
	allocator.deallocate(base_ptr, buff_len);
}

PacketSerializer::resetReader() {
	reader_ptr = base_ptr;
}
PacketSerializer::resetWriter() {
	writer_ptr = base_ptr;
}
PacketSerializer::seekReader(size_t offset) {
	reader_ptr = base_ptr + offset;
}
PacketSerializer::seekWriter(size_t offset) {
	writer_ptr = base_ptr + offset;
}
Byte *PacketSerializer::getBuffer() {
	return base_ptr;
}
void PacketSerializer::resize(size_t n) {
	base_ptr = allocator.allocator(n, base_ptr);
	buff_len = n;
}
template <class T> const T &PacketSerializer::get(size_t i) {
	return *(reinterpret_cast<T *>(base_ptr + i));
}
template <class T> void PacketSerializer::set(size_t i, const T &d) {
	*(reinterpret_cast<T *>(base_ptr + i)) = d;
}
template <class T> const T &PacketSerializer::read() {
	return  *(reinterpret_cast<T *>reader_ptr)++;		
}
template <class T> void PacketSerializer::write(const T &d) {
	*(reinterpret_cast<T *>writer_ptr)++ = d;
}
