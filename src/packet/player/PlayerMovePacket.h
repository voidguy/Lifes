

class PlayerMovePacket: public Packet {
public:
	PlayerMovePacket();
	virtual ~PlayerMovePacket();
	
public:
	virtual void decrypt(PacketSerializer packet_serializer) override;
	virtual void encrypt(PacketSerializer packet_serializer) override; 
	virtual void handle(PacketListener packet_listener) override;

private:
	Player who;
	Location to;
	Location from;

	DECLARE_REFLECT(PlayerMovePacket, 0x1001);
};
