#include "HueCyclePattern.h"

const int numberOfBuffers = 1;

void HueCyclePattern::setup(){
    
    numBuffers = numberOfBuffers;
    
    width = 200;
    height = 200;
    
    currentHue = 0;
    
    BufferPattern::setup();
}

void HueCyclePattern::update(){
    
    bool colorToggle = false;
    
    if(currentHue > 253){
        currentHue = 0;
    }else{
        if(ofGetFrameNum() % 6 == 0){
            currentHue++;
        }
    }
    
    for(int i = 0; i < numBuffers; i++){
        
        buffers[i].begin();
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ofSetColor(ofColor::fromHsb(currentHue, 255, 255));
        ofFill();
        ofRect(0, 0, width, height);
        
        for(int j = 5; j < width; j += 40){
            for(int k = 15; k < height; k += 40){
                if(colorToggle){
                    ofSetColor(ofColor::white);
                }else{
                    ofSetColor(ofColor::black);
                }
                colorToggle = !colorToggle;
                ofDrawBitmapString(ofToString(currentHue), j, k);
            }
        }
        buffers[i].end();   
    }
}