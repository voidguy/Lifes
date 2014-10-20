
#pragma once


class Packet {
public:
	Packet();
	virtual ~Packet();

public:
	static void putBytes(uint8_t *bytebuf, const std::vector<uint8_t> bytes) {
		*(reinpreter_cast<uin16_t *>bytebuf) = bytes.size();
		bytebuf += 2;
		for (const uint8_t byte: bytes) {
			*bytebuf++ = byte;
		}
	}

	virtual void handle(PacketListener packet_listener) 		= 0;
	virtual void decrypt(PacketSerializer packet_serializer) 	= 0; 
	virtual void encrypt(PacketSerializer packet_serializer) 	= 0;
};
