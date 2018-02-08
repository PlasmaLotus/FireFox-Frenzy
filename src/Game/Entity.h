#pragma once

#ifndef __ENTITY__
#define __ENTITY__

class Entity {
public:
	float posX;
	float posY;
	float posZ;
	float orientation;
	//float radianOrientation;
	int _id;
	//Game * _game;
	Entity();
	~Entity();
	virtual void update(int dt);
	//void update();


protected:

};
#endif // !__ENTITY__
