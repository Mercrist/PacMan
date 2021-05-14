#pragma once
#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        virtual void render();
        bool getKillable();
        void setKillable(bool);
        
        /*virtual boolean getter for random ghost property, 
        it is virtual because it needs to recognize if a subclass of 
        ghost has the random ghost property as true, whereas the ghost has 
        the default random ghost property set to false */
        virtual bool getRg(){     
            return false;
        }
        virtual bool getPabg(){
            return pabg;
        }
        virtual bool getColorChange(){
            return false;
        }
        virtual void setColor(){
            this->color=colors[ofRandom(4)] ;
        }
        virtual void setColorChange(bool x){
            return;
        }
        virtual void setPabg(bool x){
            this->pabg=x;
        }
        virtual void setNewPabg(bool x){
            this->newPabg=x;
        }
         virtual bool getNewPabg(){
            return this->newPabg;
        }
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=3;
        EntityManager* em;
        Animation* killableAnim;
        bool rg; //new property of random ghost added to ghost class
                //this property is in charge of recognizing if it is a random ghost or not
        bool pabg;
        string color;
        bool newPabg;
        std::vector<string> colors{"red", "cyan", "pink","orange"};

};