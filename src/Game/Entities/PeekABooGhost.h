#pragma once
#include "EntityManager.h"
#include "Animation.h"
#include "Ghost.h"

class PeekABooGhost: public Ghost{
    public:
        PeekABooGhost(int, int, int, int, ofImage, EntityManager*, string, bool,bool);
        ~PeekABooGhost();
        bool getPabg(){
            return true;
        };
        void setColor(){
            this->color =colors[ofRandom(4)]; 
        };
        bool getColorChange(){
            return this->colorchange;
        };
        void setColorChange(bool x){
            this->colorchange=x;
        };
        void setPabg(bool x){
            pabg=x;
        }
        void SetNewPabg(bool x){
            this->newPabg=x;
        }
        bool getNewPabg(){
            return this->newPabg;
        };
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned;
        int speed=3;
        EntityManager* em;
        Animation* killableAnim;  
        Animation* colorAnim; 
        bool pabg; 
        bool colorchange=false; 
        bool rg=false;
        bool newPabg;
        string color;
        std::vector<string> colors{"red", "cyan", "pink","orange"};
        
};