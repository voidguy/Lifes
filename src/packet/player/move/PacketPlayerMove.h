

class PacketPlayerMove: public PacketPlayer final {
public:
	PacketPlayerMove();
	virtual ~PacketPlayerMove();
	
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
