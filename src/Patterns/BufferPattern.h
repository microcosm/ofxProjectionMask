#pragma once
#include "ofMain.h"
#include "Canvas.h"
#include "MaskFrame.h"

class BufferPattern{
public:
    void setup();
    void update();
    void draw();
    vector<ofFbo> *getBuffers();
    int test();
    
protected:
    vector<ofFbo> buffers;
    int width, height, numBuffers;
};