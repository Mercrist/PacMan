#include "WinState.h"
WinState::WinState() { //template based on MenuState header file 
	music.load("music/pacman_intermission.wav");
	NewButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 64, 50, "New Game");//button to go to start menu after finishing game
	img2.load("images/pacmanWin.png"); //image for win state
	img2.resize(ofGetHeight(), ofGetWidth());
	img2.draw(ofGetWidth()/2,ofGetHeight()/2, ofGetWidth(), ofGetHeight());
	vector<ofImage> rightAnimframes;
    ofImage temp;
	temp = img2;
    rightAnimframes.push_back(temp); //only requires one picture
	anim = new Animation(10,rightAnimframes); 
}
void WinState::tick() {
	NewButton->tick();
	anim->tick();
	if(NewButton->wasPressed()){
		setNextState("Menu"); //the next state after winning is the menu state
		setFinished(true);
		music.stop(); //stop playing music when we change to another screen
		return;
	}
	
	if(!music.isPlaying())
			music.play();
	
}
void WinState::render() {
	ofDrawBitmapString("Pacman Project", ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	NewButton->render();
}

void WinState::keyPressed(int key){
	
}

void WinState::mousePressed(int x, int y, int button){
	NewButton->mousePressed(x, y);
}

void WinState::reset(){
	setFinished(false);
	setNextState("");
	NewButton->reset();
}

WinState::~WinState(){
	delete NewButton;
	delete anim;
}