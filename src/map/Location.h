

class Location {

public:
	Location(const World world, const float x, const float y);

public:
	Location &operator+(const float x, const float y);
	Location &operator+(const Location &loc);
	Location &operator-(const Location &loc);
	Location &operator*(const Location &loc);

	float distance(const Location &loc);
	float distanceSquared(const Location &loc);

	Block getBlock();
	Chunk getChunk();
	World getWorld();
	Vector getDirection();
	float getX();
	float getY();

	float length();
	float lengthSquared();
	static int locToBlock(float loc); 

	void setWorld(World world);
	void setX(double x);
	void setY(double y);

	Location zero();

};
