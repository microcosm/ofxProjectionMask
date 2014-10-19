#pragma once

#include "ofMain.h"
#include "ofxProjectionMask.h"
#include "HueCyclePattern.h"
#include "SetupPattern.h"
#include "ArgumentPattern.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
    ofxProjectionMask designer;
    
    /* You can only have one 'pattern' at a time, but the pattern
       can have multiple FBOs. Uncomment these one at a time to
       get an example, and use these classes as templates for your
       own patterns: */
    
    /* Cycle through colors, good test pattern */
    HueCyclePattern pattern;
    
    /* Just plain white, good for checking the edges of your shapes */
    //SetupPattern pattern;
    
    /* Shows how you can use arguments, and multiple FBOs */
    //Don't forget to send in the arguments as described in ofApp.cpp
    //ArgumentPattern pattern;
};
