#pragma once

#ifndef __ENTITY__
#define __ENTITY__

struct  Vector2
{
	float x;
	float y;
};

class Entity {
public:
	float orientation;
	int _id;
	float posX;
	float posY;
	float posZ;
	//Game * _game;
	Entity();
	~Entity();
	virtual void update(int dt);
	//void update();


protected:

};
#endif // !__ENTITY__
