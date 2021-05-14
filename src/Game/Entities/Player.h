#pragma once
#include "Animation.h"
#include "EntityManager.h"
#include "PowerUp.h"

class Player: public Entity{

    private:
        int spawnX, spawnY;
        int health=3;
        int score=0;
        int dotScore = 0; //variable created for sum of dots collected
        bool canMove;
        int speed = 8;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        //added powerup variables
        bool immortal = false;
        int stepsTaken = 0;
        ofImage img1, img2; 
        PowerUp* power = 0; //powerup attribute, assigning a pointer to 0 makes it automatically NULL and will prevent segmentation fault errors'
        ofSoundPlayer music;

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        void setHealth(int);
        int getScore();
        void setScore(int);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
        void die();
        //changes players position
        void setCoords(int x1, int y1);
        //makes player invincible
        void setImmortality(bool status);
        //check distance from player to ghost, determines whether invisible power up can be used
        bool canUseInvisible();
};