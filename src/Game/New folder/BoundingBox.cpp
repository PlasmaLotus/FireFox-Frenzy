#include "BoundingBox.h"

BoundingBox::BoundingBox() {

}
BoundingBox::~BoundingBox(){

}
Vector2 BoundingBox::distanceBetweenCenter(BoundingBox bb)
{
	Vector2 v;
	v.x = (bbox.x - bb.bbox.x);
	v.y = (bbox.y - bb.bbox.y);

	return v;
}
void BoundingBox::handleCollision() {


}

bool BoundingBox::testCollision(BoundingBox bb){
	return false;
}