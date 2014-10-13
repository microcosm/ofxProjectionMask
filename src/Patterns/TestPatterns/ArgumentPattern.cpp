#include "SetupPattern.h"

const int numberOfBuffers = 1;

const int playback1Channel = 1;
const int playback2Channel = 2;

void SetupPattern::setup(){
    
    numBuffers = numberOfBuffers;
    
    width = 200;
    height = 200;
    
    BufferPattern::setup();
}

void SetupPattern::update(){
    
    for(int i = 0; i < numBuffers; i++){
        
        buffers[i].begin();
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ofSetColor(ofColor::white);
        ofFill();
        ofRect(0, 0, width, height);
        
        buffers[i].end();   
    }
}