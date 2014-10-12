#include "ofApp.h"

const int mouseXAdjustment = -1;
const int mouseYAdjustment = -2;

void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //ofSetDataPathRoot("");
    ofEnableSmoothing();
    
    mapper.setup();
    pattern.setup();
    
    mapper.setPattern((BufferPattern*)&pattern);
    mapper.loadObjects();
    
}

void ofApp::update(){
    int mouseXAdjusted = mouseX + mouseXAdjustment;
    int mouseYAdjusted = mouseY + mouseYAdjustment;
    pattern.update();
    mapper.update(mouseXAdjusted, mouseYAdjusted);
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