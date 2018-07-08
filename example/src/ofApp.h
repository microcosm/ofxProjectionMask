#pragma once

#include "ofMain.h"
#include "ofxProjectionMask.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void drawSecondWindow(ofEventArgs &args);

    ofxProjectionMask designer;
    ofxLayerMask *pattern1, *pattern2;

    float currentHue;
};
