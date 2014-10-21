

class PlayerPacket: public Packet {
public:
	PlayerPacket();
	virtual ~PlayerPacket();
public:

private:
	Player who;
};