#pragma once
#include "RandomGhost.h"
#include "EntityManager.h"
#include "PeekABooGhost.h"

class GhostSpawner: public Entity{
    public:
        GhostSpawner(int, int, int , int, EntityManager*, ofImage);
        void spawnGhost(string);
        void keyPressed(int);
        void tick();
        bool randomghost=false; //random ghost boolean which identifies if this ghost is a random ghost and is triggered when created
        void setRandomGhost(bool x){ //sets the boolean of random ghost
            this->randomghost=x;
        }
        void setPeekABooGhost(bool x){ //sets the boolean of random ghost
            peekabooghost=x;
        }
        bool peekabooghost=false;
        bool colorchange=false;
        void setPeekABooGhostColorChange(bool x){
            colorchange=x;
        }
        void setPX(int x){
            this->Playerx = x;
        }
        void setPY(int y){
            this->Playery = y;
        }
        int getPX(){
            return this->Playerx;
        }
        int getPY(){
            return this->Playery;
        }
        void setCurrentlyKillable(bool x){
            currentlyKillable=x;
        }
        bool getCurrentlyKillable(){
            return currentlyKillable;
        }

        std::vector<string> colors{"red", "cyan", "pink","orange"};//created vector colors which are the permitted colors of the ghosts
    private:
        EntityManager* em;
        bool currentlyKillable;
        int spawnCounter = 30*5;
        int spawnX, spawnY;
        int Playerx =0;
        int Playery= 0;


};