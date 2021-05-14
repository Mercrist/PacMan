#pragma once
#include "State.h"
#include "Button.h"
#include "Animation.h" 
class WinState : public State {
private:
	ofImage img2;
	Button *NewButton; //new Button Button object that presents onto the secreen to start a new game
	Animation* anim;
	ofSoundPlayer music;

public:
	WinState();
	~WinState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
};