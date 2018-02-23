#pragma once

#ifndef __BBC__
#define __BBC__

#include "BoundingBox.h"
class BoundingSquare;
class BoundingCircle : public BoundingBox {
public:
	BoundingCircle();
	BoundingCircle(float posX, float posY, float r);
	virtual ~BoundingCircle();

	bool testCollision(BoundingBox bb);
	bool testCollision(BoundingSquare bb);
	bool testCollision(BoundingCircle bb);
	virtual void handleCollision();
protected:

};

#endif