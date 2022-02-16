#include "GameEngine.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Components.h"

int main(int argc, char** argv) {
	GameEngine game;
	game.run();

	EntityManager m;
	CMovement cm;
	m.addEntity("enemy");
	m.update();
	m.getEntities("enemy").front().get()->addComponent<CMovement>(cm);
	CMovement m2 = m.getEntities("enemy").front().get()->getComponent<CMovement>();

	return 0;
}