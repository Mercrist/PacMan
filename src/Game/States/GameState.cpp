#include "GameState.h"
#include "Entity.h"
#include "Dot.h"
#include "BigDot.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	ofRectangle Playercoords = map->getPlayer()->getBounds();
	map->getGs()->setPX(Playercoords.getX());
	map->getGs()->setPY(Playercoords.getY());
	if(!music.isPlaying()){
			music.play();
			music.setVolume(0.3);
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	if(map->getEm()->entities.size() == 0){ //When the player has collected all of the dots in the game has won
		setFinished(true);
		setNextState("Win");
	}
	if((map->getPlayer()->getScore()==500)){
		map->getGs()->setRandomGhost(true); //when the score reaches 500 it gets the ghost Spawner from the map and sets the random ghost to true
		map->getGs()->spawnGhost(colors[ofRandom(4)]); //spawns a random ghost
		map->getPlayer()->setScore(map->getPlayer()->getScore()+10); //adds 10 to the score so that it can get out of the loop
	}
	if((map->getPlayer()->getScore()==1000)){
		map->getGs()->setPeekABooGhost(true);
		map->getGs()->setPeekABooGhostColorChange(false); //when the score reaches 1000 it gets the ghost spawner from the map and sets the colorchange to false
		map->getGs()->spawnGhost(colors[ofRandom(4)]); //spawns a peekABoo ghost
		map->getPlayer()->setScore(map->getPlayer()->getScore()+10); //adds 10 to the score so that it can get out of the loop
	}
	bool currentlyKillable;
	for(int i=0;i<map->getEm()->ghosts.size();i++){ //loops through the ghosts vector 
		if(dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->getPabg() && dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->getNewPabg()){ //identifies the peekabooghost from the map and wether it is not a colored ghost
			if(ofDist(map->getEm()->ghosts[i]->getBounds().getX(),map->getEm()->ghosts[i]->getBounds().getY(),map->getPlayer()->getBounds().getX(),map->getPlayer()->getBounds().getY())<=150){
				map->getGs()->setPeekABooGhost(true);
				map->getGs()->setPeekABooGhostColorChange(true);//sets the colorchange to true
				dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->setNewPabg(false);//sets the colored peekabooghost bool to false
				map->getGs()->setCurrentlyKillable(dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->getKillable());
				if(!map->getGs()->getCurrentlyKillable()){
					map->getEm()->ghosts[i]->remove=true; 
				}
				//removes the previous ghost and replaces it with a new blank ghost
				map->getGs()->spawnGhost(colors[ofRandom(4)]); // calls the spawn ghost function
				break;
				}
					
			}
			else if(dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->getPabg() && !dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->getNewPabg()){ //identifies if it is a peekabooghost and that it is colored ghost
				if(ofDist(map->getEm()->ghosts[i]->getBounds().getX(),map->getEm()->ghosts[i]->getBounds().getY(),map->getPlayer()->getBounds().getX(),map->getPlayer()->getBounds().getY())>150){//if the distance between the pacman and the ghost is higher than 250
					map->getGs()->setPeekABooGhost(true);
					map->getGs()->setPeekABooGhostColorChange(true);
					dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->setNewPabg(true);
					map->getGs()->setCurrentlyKillable(dynamic_cast<Ghost*>(map->getEm()->ghosts[i])->getKillable());
					if(!map->getGs()->getCurrentlyKillable()){
					map->getEm()->ghosts[i]->remove=true; 
					}
					
					map->getGs()->spawnGhost(colors[ofRandom(4)]);
					break;
				}
					
			}
	}

}
void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
	mapImage.load("images/map1.png"); //on reset it creates a new map instance so that it can be played again
	map = MapBuilder().createMap(mapImage);
}

int GameState::getFinalScore(){
	return finalScore;
}

GameState::~GameState(){
	delete map;
}