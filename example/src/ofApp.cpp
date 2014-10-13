#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    pattern.setup();
    mapper.setup((BufferPattern*)&pattern);
    mapper.loadObjects();
    
}

void ofApp::update(){
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