#include "ArgumentPattern.h"

const int numberOfBuffers = 6;

void ArgumentPattern::setup(){
    
    numBuffers = numberOfBuffers;
    
    width = 200;
    height = 200;
    
    for(int i = 0; i < numberOfBuffers; i++) {
        colors.push_back(color);
    }
    
    BufferPattern::setup();
}

void ArgumentPattern::update(){
    
    for(int i = 0; i < numBuffers; i++){
        
        buffers[i].begin();
        
        ofSetColor(colors[i]);
        ofFill();
        ofRect(0, 0, width, height);
        
        buffers[i].end();   
    }
}

void ArgumentPattern::mapToColors(int mouseX, int mouseY) {

    hues.x = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    hues.y = ofMap(mouseY, 0, ofGetHeight(), 0, 255);
        cout << hues.x << endl;
    for (int i = 0; i < numberOfBuffers; i++) {
        if(i % 2 == 0) {
            colors[i] = ofColor::fromHsb(hues.x, 255, 255);
        } else {
            colors[i] = ofColor::fromHsb(hues.y, 255, 255);
        }
    }
}