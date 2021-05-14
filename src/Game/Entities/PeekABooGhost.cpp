#include "PeekABooGhost.h"
#include "BoundBlock.h"

PeekABooGhost::PeekABooGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color,bool Pabg, bool newPabg): Ghost(x, y, width, height, spriteSheet, em, color){
    this->em = em;
    this->rg=false;
    this->pabg=true;
    this->colorchange=false;
    this->newPabg=newPabg;

    setKillable(killable);
    vector<ofImage> killableFrames;
    ofImage temp;
    temp.cropFrom(spriteSheet, 584, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 64, 16, 16);
    killableFrames.push_back(temp);    
    temp.cropFrom(spriteSheet, 632, 64, 16, 16);
    killableFrames.push_back(temp);
    killableAnim = new Animation(10, killableFrames);
    if(color == "red"){
        sprite.cropFrom(spriteSheet,456,64,16,16);
    }else if(color=="pink"){
        sprite.cropFrom(spriteSheet,456,78,16,16);
    }else if(color=="cyan"){
        sprite.cropFrom(spriteSheet,456,96,16,16);
    }else if(color=="orange"){
        sprite.cropFrom(spriteSheet,456,113,16,16);
    }
    else if(color=="blank"){
        sprite.cropFrom(spriteSheet,456,180,16,16);
    }
}
PeekABooGhost::~PeekABooGhost(){
    delete killableAnim;
}