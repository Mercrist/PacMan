#include "RandomGhost.h"
#include "BoundBlock.h"

RandomGhost::RandomGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color,bool rg): Ghost(x, y, width, height, spriteSheet, em, color){
    this->em = em;
    this->rg=rg;
}

RandomGhost::~RandomGhost(){
    delete killableAnim;
}