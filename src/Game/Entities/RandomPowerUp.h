#pragma once
#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"

class RandomPowerUp : public PowerUp
{
    private:
        EntityManager* em;
        Player* p;
        ofSoundPlayer music;

    public:
        RandomPowerUp(EntityManager*, Player*);
        void activate();
};
