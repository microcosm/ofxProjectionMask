#include "BufferPattern.h"

void BufferPattern::setup(){
    for(int i = 0; i < numBuffers; i++){
        ofFbo buffer;
        buffer.allocate(width, height, GL_RGBA, 0);
        buffers.push_back(buffer);
    }
}

void BufferPattern::draw(){
    ofPushMatrix();
    ofTranslate(10, 10);
    
    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    
    int x, y;
    
    for(int i; i < buffers.size(); i++){
        x = (width * i) + 10;
        y = 10;
        buffers[i].draw(x, y, width, height);
        ofRect(x, y, width, height);
    }
    
    ofPopMatrix();
}

int BufferPattern::test(){
    return 1;
}

vector<ofFbo>* BufferPattern::getBuffers(){
    return &this->buffers;
}