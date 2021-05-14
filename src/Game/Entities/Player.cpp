#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "RandomPowerUp.h"
#include "InvisiblePowerUp.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;
    img1.load("images/Background.png"); //loads sprites page 
    music.load("music/invisible.wav");
    
}
void Player::tick(){
    canMove = true;
    checkCollisions();
    if (immortal && !music.isPlaying())
        music.play(); //play invis power up music when you can use it

    if(canMove){
        if(facing == UP){
            y-= speed;
            walkUp->tick(); 
        }else if(facing == DOWN){
            y+=speed;
            walkDown->tick();
        }else if(facing == LEFT){
            x-=speed;
            walkLeft->tick();
        }else if(facing == RIGHT){
            x+=speed;
            walkRight->tick();
        }

        if (immortal) //count amount of steps taken since the player uses invisible power up
        {
            stepsTaken++;
            if(stepsTaken >= 40) //after 40 steps, deactivate powerup effects and reset variables
            {
                immortal = false;
                stepsTaken = 0;
                music.stop();
            }
        }
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    if (!immortal) //dont render the player when the powerup is active
    {    
        if(facing == UP){
            walkUp->getCurrentFrame().draw(x, y, width, height);
        
        }else if(facing == DOWN){
            walkDown->getCurrentFrame().draw(x, y, width, height);
        }else if(facing == LEFT){
            walkLeft->getCurrentFrame().draw(x, y, width, height);
        }else if(facing == RIGHT){
            walkRight->getCurrentFrame().draw(x, y, width, height);
        }
    }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);

    //draw current power up
    ofDrawBitmapString("Current PowerUp:", ofGetWidth()/2-100, 50);
    if (power != nullptr && dynamic_cast<RandomPowerUp*> (power))
    {
        ofSetColor(256,256,256); //dont color the current power up red
        img2.cropFrom(img1, 569, 48,16,16); //gets 16x16 image from (x,y), measures from top left corner of the sprite
        img2.draw(ofGetWidth()/2 + 33, 38);
    }

    else if (power != nullptr && dynamic_cast<InvisiblePowerUp*> (power))
    {
        ofSetColor(256,256,256); 
        img2.cropFrom(img1, 664, 5,16,16); 
        img2.draw(ofGetWidth()/2 + 33, 38);
    }
    
    else
        ofDrawBitmapString("None", ofGetWidth()/2 + 33, 50);

}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            setFacing(UP);
            break;
        case 's':
            setFacing(DOWN);
            break;
        case 'a':
            setFacing(LEFT);
            break;
        case 'd':
            setFacing(RIGHT);
            break;
        case 'n':
            if (!immortal)
                die();
            break;
        case 'm': //increases health
            if (health<3) //health boundary, it only permits addding more health if health is lower than 3
                health++;
            break;

        case ' ': //Activates Pac Man's Power up
            if (power != nullptr)
            {
                if(dynamic_cast<InvisiblePowerUp*> (power) && canUseInvisible() == false)
                    break; //don't use power up if player cant use invisible power up
                power->activate();
                delete power; 
                power = 0; //empties variable contents since the power up has been used
            }
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(FACING facing){
    this->facing = facing;
}

int Player::getHealth(){
    return health;
}

void Player::setHealth(int h){
    health = h;
}
int Player::getScore(){
    return score;
}
void Player::setScore(int h){
    score = h;
}

void Player::checkCollisions(){
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
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=10;
                em->setKillable(true);
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;

                if (ghost->getRg()) //get powerup if we eat a RandomGhost
                    power = new RandomPowerUp(em, this); //pass current player as pointer to power up class

                else if (ghost->getPabg())
                    power = new InvisiblePowerUp(this);
            }else{
                if (!immortal)
                    die();

            }
        }
    }

    
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

void Player::setCoords(int x1, int y1) 
{
    x = x1;
    y = y1;
}

void Player::setImmortality(bool status)
{
    this->immortal = status;
}

bool Player::canUseInvisible()
{
    for(Entity* entity:em->ghosts) 
    {
        Ghost* ghost = dynamic_cast<Ghost*>(entity);
        ofRectangle coords = ghost->getBounds();                         //using ofDistance(ghostX, ghostY, playerX, playerY) measures distance more accurately
        if(ofDist(coords.getX(), coords.getY(), this->x, this->y) <= 40) //cant use invis power up if distance between ghost and player is too small
            return false;
    }
    return true;
}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete power;
}