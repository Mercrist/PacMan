#pragma once

#include "BoundBlock.h"

class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> BoundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);
	void setRg(bool x){ //random ghost boolean setter
		this->rg=x;
	};
	void setPabg(bool y){ //random ghost boolean setter
		this->pabg=y;
	};
	bool getRg(){ //random ghost boolean getter
		return this->rg;
	};
	bool getPabg(){ //random ghost boolean getter
		return this->pabg;
	};
	bool getColorChange(){
		return this->colorChange;
	}
	void setColorChange(bool x){
		this->colorChange=true;
	}

private:
	bool killable = false;
	int killableCounter;
	bool rg=false; //random ghost boolean property
	bool pabg=false;//peekabooghost boolean property
	bool colorChange=false;
};