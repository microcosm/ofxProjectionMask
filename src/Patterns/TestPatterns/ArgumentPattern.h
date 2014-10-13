#pragma once
#include "ofMain.h"
#include "Canvas.h"
#include "BufferPattern.h"

class SetupPattern : public BufferPattern{
public:
    void setup();
    void update();
};