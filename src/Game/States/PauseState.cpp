#include "PauseState.h"
PauseState::PauseState() {
	ResumeButton = new Button(ofGetWidth()/2 - 5, ofGetHeight()/2, 64, 50, "Resume"); 
    QuitButton = new Button(ofGetWidth()/2 + 2, ofGetHeight()/2+40, 64, 50, "Quit");
	img1.load("images/intro.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	temp.cropFrom(img1, 29, 247, 170, 10); //grabs the company credits image
    rightAnimframes.push_back(temp); 
	anim = new Animation(10,rightAnimframes); 
	music.load("music/pause.wav");
}
void PauseState::tick() {
	ResumeButton->tick();
    QuitButton->tick();
	anim->tick();
	if(ResumeButton->wasPressed()){
		setNextState("Game"); //switches back to the game
		setFinished(false);
		music.stop(); //stop playing music when we change to another screen
		played = false; //reset variable
		return;
	}

    else if (QuitButton->wasPressed())
    {
        setNextState("Menu");
		setFinished(true); //finishes the game and takes you back to the menu
		music.stop(); 
		played = false;
		return;
    }

	if(!music.isPlaying() && played == false)
	{	
		music.play();
		played = true;
	}
}
void PauseState::render() {
	ofDrawBitmapString("Pacman Project", ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofDrawBitmapString("Game Paused", ofGetWidth()/2 + 10, ofGetHeight()/2-250, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(255, 255, 255);
	anim->getCurrentFrame().draw(ofGetWidth()/2-20, ofGetHeight()/2-100); //renders the pause state image
	ResumeButton->render();
    QuitButton->render();
}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
	ResumeButton->mousePressed(x, y);
    QuitButton->mousePressed(x, y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	ResumeButton->reset();
    QuitButton->reset();
}

PauseState::~PauseState(){
	delete ResumeButton;
    delete QuitButton;
	delete anim;
}