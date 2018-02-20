#include "Dummy.h"

Dummy::Dummy() : Entity(){
	posX = 300;
	posY = 300;
}

Dummy::~Dummy() {

}

void Dummy::update(int dt) {
	//nothing
}

void Dummy::onHit() {
	//printf("Dummy has benn hit...\n");
}