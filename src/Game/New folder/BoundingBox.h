#pragma once

#ifndef __BB__
#define __BB__

struct  Vector2
{
	float x;
	float y;
};
class BoundingBox {
public:
	BoundingBox();
	virtual ~BoundingBox();
	Vector2 bbox;
	float &posX{ bbox.x };
	float &posY{ bbox.y };
	float width;
	float height;

	bool testCollision(BoundingBox bb);
	//std::vector
	Vector2 distanceBetweenCenter(BoundingBox bb);
	Vector2 angleBetweenCenter(BoundingBox bb);
	virtual void handleCollision();
protected:

};

#endif