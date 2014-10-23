

class PacketPlayer: public Packet {
public:
	PlayerPacket();
	PlayerPacket(uuid_t)
	virtual ~PlayerPacket();

public:
	virtual void decrypt(PacketSerializer packet_serializer) override;
	virtual void encrypt(PacketSerializer packet_serializer) override; 
	virtual void handle(PacketListener packet_listener) override;

private:
	Player who;
};