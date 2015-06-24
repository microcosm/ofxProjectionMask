#pragma once

#include "ofMain.h"
#include "ofxProjectionMask.h"
#include "ofxLayerMask.h"
#include "HueCyclePattern.h"

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
	
    ofxProjectionMask designer; //essentially, the UI
    ofxLayerMask pattern1, pattern2;

    //Uncomment these one at a time to try them:
    //HueCyclePattern pattern; //cycle rainbow colors - default
    //SetupPattern pattern;  //plain white
    //ArgumentPattern pattern; //control the pattern with args, plus multiple buffers
    //If you uncomment ArgumentPattern, go and uncomment the line in ofApp::update()
    //YourCustomPattern pattern; //Build your patterns based on this template
};
