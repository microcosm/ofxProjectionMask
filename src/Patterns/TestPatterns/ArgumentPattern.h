#pragma once
#include "ofMain.h"
#include "Canvas.h"
#include "BufferPattern.h"

class ArgumentPattern : public BufferPattern{
public:
    vector<ofColor> colors;
    void setup();
    void update();
    void mapToColors(int mouseX, int mouseY);
    ofColor color;
    ofVec2f hues;
};