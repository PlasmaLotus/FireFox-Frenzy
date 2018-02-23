#pragma once

#ifndef __BBS__
#define __BBS__

#include "BoundingBox.h"
class BoundingCircle;
class BoundingSquare :public  BoundingBox {
public:
	BoundingSquare();
	BoundingSquare(float posX, float posY, float wdth, float hght);
	virtual ~BoundingSquare();

	bool testCollision(BoundingBox bb);
	bool testCollision(BoundingSquare bb);
	bool testCollision(BoundingCircle bb);
	virtual void handleCollision();
protected:

};

#endif