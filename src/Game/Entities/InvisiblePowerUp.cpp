#include "InvisiblePowerUp.h"

InvisiblePowerUp::InvisiblePowerUp(Player* p)
{
    this->p = p;
}

void InvisiblePowerUp::activate()
{
    p->setImmortality(true);
}