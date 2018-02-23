#include "BoundingSquare.h"
#include "BoundingCircle.h"

BoundingSquare::BoundingSquare() {
	posX = 0;
	posY = 0;
	width = 1;
	height = 1;
}

BoundingSquare::BoundingSquare(float pX, float pY, float wdth, float hght) {
	posX = pX;
	posY = pY;
	width = wdth;
	height = hght;
}
BoundingSquare::~BoundingSquare(){

}

bool BoundingSquare::testCollision(BoundingBox bb){
	return false;
}
bool BoundingSquare::testCollision(BoundingSquare bb) {
	return false;
}
bool BoundingSquare::testCollision(BoundingCircle bb) {
	return false;
}

void BoundingSquare::handleCollision()
{
}
