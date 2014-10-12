#include "ofApp.h"

const int mouseXAdjustment = -1;
const int mouseYAdjustment = -2;

void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //ofSetDataPathRoot("");
    ofEnableSmoothing();
    
    pattern.setup();
    
    mapper.setPattern((BufferPattern*)&pattern);
    mapper.loadObjects();
    
}

void ofApp::update(){
    int mouseXAdjusted = mouseX + mouseXAdjustment;
    int mouseYAdjusted = mouseY + mouseYAdjustment;
    pattern.update();
    mapper.setMousePosition(mouseXAdjusted, mouseYAdjusted);
    mapper.update();
}

void ofApp::draw(){
    mapper.draw();
}

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    mapper.respondToKey(key);
}

void ofApp::mouseMoved(int x, int y){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    mapper.respondToMouseDrag();
}

void ofApp::mousePressed(int x, int y, int button){
    mapper.respondToMouseDown();
}

void ofApp::mouseReleased(int x, int y, int button){
    mapper.respondToMouseRelease();
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}