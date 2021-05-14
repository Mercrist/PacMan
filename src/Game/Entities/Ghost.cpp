#include "Ghost.h"
#include "BoundBlock.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Entity(x, y, width, height){ //added boolean property of random ghost which identifies the ghost as a random ghost or not
    this->em = em;
    this->rg=false; //since this is a regular ghost the rg property is set to false as default
    this->pabg=false;
    this->newPabg=false;
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

}

void Ghost::tick(){
    killableAnim->tick();
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
        }else if(facing == DOWN){
            y+=speed;
        }else if(facing == LEFT){
            x-=speed;
        }else if(facing == RIGHT){
            x+=speed;
        }
    }else{
        int randInt;
        if(justSpawned){
            randInt = ofRandom(2);

        }else{
            randInt = ofRandom(4);
        }
        if(randInt == 0){
            facing = LEFT;
        }else if(randInt == 1){
            facing = RIGHT;
        }else if(randInt == 2){
            facing = DOWN;
        }else if(randInt == 3){
            facing = UP;
        }
        justSpawned = false;

    }
}

void Ghost::render(){
    if(killable){
        killableAnim->getCurrentFrame().draw(x,y,width,height);
    }
    else{
        Entity::render();
    }
}

bool Ghost::getKillable(){
    return killable;
}
void Ghost::setKillable(bool k){
    killable = k;
}
void Ghost::checkCollisions(){
    for(BoundBlock* BoundBlock: em->BoundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
}

Ghost::~Ghost(){
    delete killableAnim;
}