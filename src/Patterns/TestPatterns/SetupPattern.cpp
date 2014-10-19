#include "SetupPattern.h"

const int numberOfBuffers = 1;

void SetupPattern::setup(){
    
    numBuffers = numberOfBuffers;
    
    width = 200;
    height = 200;
    
    BufferPattern::setup();
}

void SetupPattern::update(){
    
    for(int i = 0; i < numBuffers; i++){
        
        buffers[i].begin();
        
        ofSetColor(ofColor::white);
        ofFill();
        ofRect(0, 0, width, height);
        
        buffers[i].end();   
    }
}