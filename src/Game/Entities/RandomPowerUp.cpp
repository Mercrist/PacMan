#include "RandomPowerUp.h"

RandomPowerUp::RandomPowerUp(EntityManager* em, Player* p)
{
    this->em = em;
    this->p = p;
    music.load("music/teleport.wav");
}

void RandomPowerUp::activate()
{
    int i = ofRandom(em->entities.size()); //gets the index of a random dot in the map, entities ONLY contains the dots
    ofRectangle coordinates = em->entities[i]->getBounds();//gets coordinates 
    em->entities[i]->remove =true;//removes the dot
    p->setCoords(coordinates.getX(), coordinates.getY()); //changes players position
    music.play();
}