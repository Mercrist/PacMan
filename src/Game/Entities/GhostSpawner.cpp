#include "GhostSpawner.h"
#include "Ghost.h"
#include "Dot.h"
#include "BigDot.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(){
    currentlyKillable=getCurrentlyKillable();
    if(em->getRg()){
        spawnGhost(colors[ofRandom(4)]);
    }
    if(em->getPabg()){
        spawnGhost(colors[ofRandom(4)]);
    }
    if(em->ghosts.size()<4){
        if(spawnCounter == 0){
            spawnGhost(colors[ofRandom(4)]); //spawns a ghost of random colors between red, pink, cyan, and orange
            spawnCounter = 30*5;
        }else{
            spawnCounter--;
        }
    }
}
void GhostSpawner::spawnGhost(string color){ //only spawns regular ghosts
    if(!randomghost  && !em->getRg() && !peekabooghost && !em->getPabg())
    {    
        Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
        em->ghosts.push_back(g);
    }
    
    while(randomghost || em->getRg())
    {
        
        int i = ofRandom(em->entities.size()); //gets the index of a random dot in the map
        ofRectangle coordinates = em->entities[i]->getBounds();//gets the coordinates for the random dot chosen
        
        if((abs(coordinates.getX() - getPX())  >=50) && (abs(coordinates.getY() - getPY()) >= 50)){
                RandomGhost* rg=new RandomGhost(coordinates.getX(),coordinates.getY(),coordinates.getWidth()-2,coordinates.getHeight()-2,sprite,em, color, true);
                em->ghosts.push_back(rg);//inserts the new random ghost to the ghosts vector
                em->entities[i]->remove =true;//removes the dot  
                randomghost=false;//sets the randomghost boolean back to 0
                em->setRg(false);//sets the random ghost boolean in the entitymanager to 0 as well
            }   
    }
    if(peekabooghost){
        if(!colorchange){
            PeekABooGhost* pabg=new PeekABooGhost(x,y,width-2,height-2,sprite,em, "blank", true,true);
            em->ghosts.push_back(pabg);//inserts the new random ghost to the ghosts vector
            peekabooghost=false;//sets the randomghost boolean back to 0
            //sets the random ghost boolean in the entitymanager to 0 as well
        }
        if(colorchange){
            for(unsigned int i=0;i<em->ghosts.size();i++){
                if(dynamic_cast<Ghost*>(em->ghosts[i])->getNewPabg() && dynamic_cast<Ghost*>(em->ghosts[i])->getPabg() && !currentlyKillable){
                    ofRectangle coords= em->ghosts[i]->getBounds();
                    PeekABooGhost* pabg= new PeekABooGhost(coords.getX(),coords.getY(),width-2,height-2,sprite,em, "red",true,false);
                    em->ghosts.push_back(pabg);
                    pabg->setKillable(currentlyKillable);
                    peekabooghost=false;
                    colorchange=false;
                    return;	
                }
                else if(!dynamic_cast<Ghost*>(em->ghosts[i])->getNewPabg() && dynamic_cast<Ghost*>(em->ghosts[i])->getPabg() && !currentlyKillable){
                    ofRectangle coords= em->ghosts[i]->getBounds();
                    PeekABooGhost* pabg= new PeekABooGhost(coords.getX(),coords.getY(),width-2,height-2,sprite,em, "blank",true,true);
                    em->ghosts.push_back(pabg);
                    pabg->setKillable(currentlyKillable);
                    peekabooghost=false;
                    colorchange=false;
                    return;	
                }
             
            } 
        }
    
    } 
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){  //spawns random ghosts of different colors when the 'g' is pressed
        spawnGhost(colors[ofRandom(4)]);
    }
}