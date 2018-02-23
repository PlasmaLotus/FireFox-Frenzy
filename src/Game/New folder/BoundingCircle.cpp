#include "BoundingCircle.h"
#include "BoundingSquare.h"

BoundingCircle::BoundingCircle() {
	posX = 0;
	posY = 0;
	width = 1;
	height = 1;
}
BoundingCircle::BoundingCircle(float pX, float pY, float r) :
	BoundingBox()
{
	posX = pX;
	posY = pY;
	width = r;
	height = r;
}
BoundingCircle::~BoundingCircle() {

}

bool BoundingCircle::testCollision(BoundingBox bb) {
	return false;
}
bool BoundingCircle::testCollision(BoundingSquare bb) {
	return false;
}
bool BoundingCircle::testCollision(BoundingCircle bb) {
	return false;
}



void BoundingCircle::handleCollision()
{
}
