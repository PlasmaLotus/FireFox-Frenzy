#include "ProjectileBubble.h"
#include "../SquareEntity.h"
#include "../Map.h"
#include <math.h>

ProjectileBubble::ProjectileBubble():
	Projectile(-1, 0.f, 0.f){
}

ProjectileBubble::ProjectileBubble(int id) :
	Projectile(id, 0.f, 0.f){
}

ProjectileBubble::ProjectileBubble(int id, float x, float y) :
	Projectile(id, x, y)
{
	lifetime = 10000;
	durability = 10;
}

ProjectileBubble::~ProjectileBubble()
{
}

void ProjectileBubble::update(int32_t dt)
{
	Projectile::update(dt);
	
}

bool ProjectileBubble::isAlive(){
	//return true;
	if (durability > 0) {
		if (lifetime > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return (durability > 0 || lifetime > 0);
}

void ProjectileBubble::handleCollision()
{
}

void ProjectileBubble::handleCollision(Entity * e)
{
	try {
		if (e != nullptr) {
			CircleEntity* ce = dynamic_cast<CircleEntity*>(e);
			SquareEntity* se = dynamic_cast<SquareEntity*>(e);
			Map* mp = dynamic_cast<Map*>(e);
			if (ce != nullptr) {
				
				Vector2 tangentVector;
				// Vector perpendicular to (x, y) is (-y, x)
				tangentVector.y = -(e->posX - posX);
				tangentVector.x = e->posY - posY;
				tangentVector = tangentVector.getNormal();

				Vector2 relativeVelocity;
				//relativeVelocity.x = sin(orientation)* velocityX;
				//relativeVelocity.y = cos(orientation)* velocityY;
				relativeVelocity.x = (velocityX - e->velocityX);
				relativeVelocity.y = (velocityY - e->velocityY);
				relativeVelocity = relativeVelocity.getNormal();


				float vecLength = _distanceBetween(*e);
				//float vecLength = tangentVector.x * relativeVelocity.x + tangentVector.y * relativeVelocity.y;
				Vector2 velocityComponentOnTangent(tangentVector.x * vecLength, tangentVector.y * vecLength);
				Vector2 velocityComponentPerpendicularToTangent((tangentVector.x - velocityComponentOnTangent.x), (tangentVector.y - velocityComponentOnTangent.y));
				//relativeVelocity - velocityComponentOnTangent;
				Vector2 normalVCPerpendicular = velocityComponentPerpendicularToTangent.getNormal();
				velocityComponentOnTangent = velocityComponentOnTangent.getNormal();
				//orientation = std::atan2(normalVCPerpendicular.y, normalVCPerpendicular.x);
				//orientationX = sin(orientation) + 2.f * normalVCPerpendicular.x;
				//orientationY = cos(orientation) + 2.f * normalVCPerpendicular.y;
				
				//orientation = std::atan2(orientationY, orientationX);
				orientation = atan2(velocityComponentOnTangent.y + 1.f * normalVCPerpendicular.y, velocityComponentOnTangent.x + 1.f * normalVCPerpendicular.x);
				//velocityX -= 2 * velocityComponentPerpendicularToTangent.x;
				//velocityY -= 2 * velocityComponentPerpendicularToTangent.y;
				//posX -= relativeVelocity.x;
				//posY -= relativeVelocity.y;

				if (e->velocityX != 0) {
					e->velocityX += velocityComponentPerpendicularToTangent.x;
				}
				if (e->velocityY != 0) {
					e->velocityY += velocityComponentPerpendicularToTangent.y;
				}
			}
			else if (mp != nullptr) {
				if (posX - width * 4 < 0) {
					orientation = atan2(-1.f * sin(orientation), cos(orientation));
					//velocityX *= -1.f;
				}
				else if (posX + width * 4 > e->width) {
					orientation = atan2(-1.f * sin(orientation), cos(orientation));
				}

				if (posY - height * 4 < 0) {
					orientation = atan2(sin(orientation), -1.f * cos(orientation));
				}
				else  if (posY + height * 4 > e->height) {
					orientation = atan2(sin(orientation), -1.f * cos(orientation));
				}

			}
			else if (se != nullptr) {
				{
					/*Testing with square walls*/
					//Testing if the object entered from the right
					float widthSum = width / 2 + e->width / 2;
					float heightSum = height / 2 + e->height / 2;
					float arbitraryPixel = 0.001f; //Small unit of msure to make sure the object isnt still colliding with the wall the next frame
					if (posX >= e->posX) {
						//On the right of the wall
						if (prevPosX - e->posX > widthSum) {
							velocityX *= -1.f;
						}
					}
					else {
						//On the left of the wall
						/**/
						if (e->posX - prevPosX > widthSum) {
							velocityX *= -1.f;
						}
					}

					//Testing if the object entered from the bottom
					if (posY >= e->posY) {
						//On the bottom of the wall
						if (prevPosY - e->posY > heightSum) {
							velocityY *= -1.f;
						}
					}
					else {
						//On the top of the wall
						if (e->posY - prevPosY > heightSum) {
							velocityY *= -1.f;
						}
					}
				}
			}
			else {
			}
		}

	}
	catch (std::exception e) {
		//return false;
	}
	_angleBetween(*e);
	Vector2 tangentVector;
	// Vector perpendicular to (x, y) is (-y, x)
	//tangentVector.y = -(circle2.X - circle1.X);
	//tangentVector.x = circle2.Y - circle1.Y;

}
