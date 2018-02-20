#pragma once

#ifndef __DUMMY__
#define __DUMMY__

#include "Entity.h"


class Dummy : public Entity {
public:

	Dummy();
	~Dummy();
	void update(int dt);
	void onHit();
	int life{ 100 };

	//protected:

};
#endif // !__DUMMY__