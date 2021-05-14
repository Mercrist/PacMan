#pragma once
#include "EntityManager.h"
#include "Animation.h"
#include "Ghost.h"

class RandomGhost: public Ghost{
    public:
        RandomGhost(int, int, int, int, ofImage, EntityManager*, string, bool);
        ~RandomGhost();
        bool getRg(){
            return true;
        };
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        int speed=3;
        EntityManager* em;
        Animation* killableAnim;  
        bool rg =false;  
};