#include "ofApp.h"

//To use this addon, we need to work with pattern objects and
//the ofxProjectionMapper. You can write as many patterns as
//you like. Just put them in a folder in your src directory
//and name them in the convention MyCrazyPattern, and have
//them inherit from the base class 'BufferPattern'.

//To try this out, look in the Patterns/TestPatterns directory
//of the addon. Those can serve as templates and give you a
//sense of the base pattern.

//Note also that this addon is designed to run full-screen,
//and with at least two screens (although there is a single
//screen mode for developing and testing). In a 'production'
//i.e. real environment, your second screen will be a projector
//and you will be using your first screen's design canvas to
//paint light onto the real world.

//In order to do this you will need to figure out precisely
//your screen dimensions and add them to the Presets class
//of this addon. You will also have to set up your displays
//to sit side-by-side using your OS preferences, and on OSX
//you may have to disable a setting in Mission Control
//preferences:
//http://forum.openframeworks.cc/t/dual-monitor-full-screen/13654/2

void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    //First, we set up our pattern, which sets up its buffer(s)
    pattern.setup();
    
    //Then we assign the pattern to the mapper, which displays
    //canvas and drawing tools, and renders the buffers.
    mapper.setup((BufferPattern*)&pattern);
    
    //Switch out to this line when you are ready to run this for
    //real with a secopnd screen / live projector setup
    //mapper.setup((BufferPattern*)&pattern, PRESETS_PRODUCTION);
}

void ofApp::update(){
    //This example pattern will run as-is, but when you are
    //ready head over to ofApp.h and try enabling some different
    //patterns...
    
    //When you enable ArgumentPattern in ofApp.h, uncomment this:
    //pattern.mapToColors(mouseX, mouseY);
    pattern.update();
    
    mapper.update(mouseX, mouseY);
}

void ofApp::draw(){
    mapper.draw();
}

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    mapper.keyReleased(key);
}

void ofApp::mouseMoved(int x, int y){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    mapper.mouseDragged();
}

void ofApp::mousePressed(int x, int y, int button){
    mapper.mousePressed();
}

void ofApp::mouseReleased(int x, int y, int button){
    mapper.mouseReleased();
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}