#include "Map.h"

Map::Map(EntityManager* em){
    entityManager = em;
}

void Map::tick(){
	entityManager->tick();
	player->tick();
	gs->tick();

}
void Map::render(){
    ofSetBackgroundColor(0, 0, 0);
	entityManager->render();
	player->render();

}

void Map::keyPressed(int key){
	player->keyPressed(key);
	gs->keyPressed(key);

}

void Map::mousePressed(int x, int y, int button){
	player->mousePressed(x, y, button);
}

void Map::keyReleased(int key){
	player->keyReleased(key);
}
void Map::addBoundBlock(BoundBlock* e){
    entityManager->BoundBlocks.push_back(e);
}
void Map::addEntity(Entity* e){
	entityManager->entities.push_back(e);
}
void Map::setPlayer(Player* p){
    player = p;
}

Player* Map::getPlayer(){
	return player;
}
void Map::setGhostSpawner(GhostSpawner* p){
    gs = p;
}

Map::~Map(){
	delete player;
	delete  entityManager;
	delete gs;
}