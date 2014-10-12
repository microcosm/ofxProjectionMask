#pragma once
#include "ofMain.h"
#include "Canvas.h"
#include "BufferPattern.h"

class HueCyclePattern : public BufferPattern {
public:
    
    void setup();
    void update();
    
protected:
    int currentHue;
};