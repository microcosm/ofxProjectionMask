#include "ofApp.h"
/*
  ofxProjectionMask
  =================
  ofxProjectionMask is an addon which allows you to mask out
  areas of the real world onto which to project any light
  pattern you like.

  Unlike projection mapping, this addon is not specifically
  about creating the 'illusion' that a light surface is
  'mapped onto' some target physical object; instead this
  addon simply masks - prevents the light patterns you specify
  from showing up anywhere outside of the mask boundaries.

  You can choose from three drawing modes:

  1. DO_NOT_STRETCH        Draw the pattern exactly as specified,
                           pixel-perfect to how it was drawn

  2. STRETCH_TO_MASKFRAME  Stretch the given pattern so that it
                           matches the boundaries of the mask
                           frame which contains it - you will
                           learn about mask frames when you
                           launch the UI

  3. HOMOGRAPHY            Stretch the pattern so that it matches
                           four arbitrary points within a mask
                           frame. This is the closest we get to
                           projection *mapping*, this essentially
                           allows you to 'pre-warp' your pattern
                           to match a rectangular target surface

                           Note: HOMOGRAPHY mode only works when
                           you have exactly 4 mask points inside
                           your mask frame. If you have more than
                           4 then it falls back to DO_NOT_STRETCH

  The idea of this addon is it separates out the masking from
  the mapping, and focuses more on the former than the latter.
  This is useful for situations in which you are more interested
  in exploring certain properties of light, computer graphics
  and physical space, than in creating an optical illusion.

  How to get started?
  -------------------
  Just launch the app! Instructions are there for how to
  use the UI. When you've had enough, scroll through this file
  to see how to program your own patterns.
*/

void ofApp::setup(){
    //First, set up the ofxProjectionMask designer
    designer.setup(); //Default is STRETCH_TO_MASKFRAME
    //designer.setup(DO_NOT_STRETCH); //Otherwise, explicitly state which mode you want
    //designer.setup(STRETCH_TO_MASKFRAME); //These are explained above
    //designer.setup(HOMOGRAPHY);

    //When you are ready to use this addon fullscreen with a
    //projector you will need to uncomment this line below, and
    //comment out the setup() call with no arguments above.
    //designer.setup(DO_NOT_STRETCH, PRESETS_PRODUCTION);
    //NOTE: If you enable PRESETS_PRODUCTION, you MUST also
    //go and uncomment this line in main.cpp
    //main.cpp : settings.windowMode = OF_FULLSCREEN;

    //Now lets set up two patterns of different sizes
    pattern1 = designer.newPattern(200, 200);
    pattern2 = designer.newPattern(800, 800);

    //And lets init the variables our patterns are going to use
    currentHue = 0;
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();
}

void ofApp::update(){
    //Tell the designer where your mouse is
    designer.update(mouseX, mouseY);

    //Let's draw a hue-cycle in our first pattern
    pattern1->begin();
    {
        currentHue += 0.2;
        if(currentHue >= 256){
            currentHue = 0;
        }
        
        ofBackground(ofColor::fromHsb(currentHue, 255, 255));
        for(int i = 5; i < pattern1->getWidth(); i += 40){
            for(int j = 15; j < pattern1->getHeight(); j += 40){
                ofSetColor(ofColor::black);
                ofDrawBitmapString(ofToString((int)currentHue), i, j);
            }
        }
    }
    pattern1->end();

    //Let's draw a grid in the second pattern
    pattern2->begin();
    {
        ofBackground(ofColor::black);
        for(int i = 40; i < pattern2->getWidth(); i += 80){
            for(int j = 40; j < pattern2->getHeight(); j += 80){
                ofSetColor(ofColor::white);
                ofDrawRectangle(0, i, pattern2->getWidth(), 20);
                ofDrawRectangle(j, 0, 20, pattern2->getHeight());
            }
        }
    }
    pattern2->end();
}

void ofApp::draw(){
    designer.drawFirstWindow();
}

void ofApp::drawSecondWindow(ofEventArgs &args){
    designer.drawSecondWindow();
}
