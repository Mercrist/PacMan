#pragma once
#include "PowerUp.h"
#include "Player.h"

class InvisiblePowerUp : public PowerUp
{
    private:
        Player* p;

    public:
        InvisiblePowerUp(Player*);
        void activate();
};
