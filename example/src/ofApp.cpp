#include "ofApp.h"

const int mouseXAdjustment = -1;
const int mouseYAdjustment = -2;

void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //ofSetDataPathRoot("");
    ofEnableSmoothing();
    
    pattern.setup();
    
    maskEditor.setPattern((BufferPattern*)&pattern);
    maskEditor.loadObjects();
    
}

void ofApp::update(){
    int mouseXAdjusted = mouseX + mouseXAdjustment;
    int mouseYAdjusted = mouseY + mouseYAdjustment;
    pattern.update();
    maskEditor.setMousePosition(mouseXAdjusted, mouseYAdjusted);
    maskEditor.update();
}

void ofApp::draw(){
    maskEditor.draw();
}

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    maskEditor.respondToKey(key);
}

void ofApp::mouseMoved(int x, int y){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    maskEditor.respondToMouseDrag();
}

void ofApp::mousePressed(int x, int y, int button){
    maskEditor.respondToMouseDown();
}

void ofApp::mouseReleased(int x, int y, int button){
    maskEditor.respondToMouseRelease();
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}