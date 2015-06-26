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
  Just launch the app! Instructions are on the left for how to 
  use the UI. When you've had enough, scroll through this file
  to see how to program your own patterns and run in fullscreen
  on your favorite projector.
*/

void ofApp::setup(){
    //Lets set up two patterns of different sizes
    pattern1.setup(100, 100, 1);
    pattern2.setup(800, 800, 1);

    //Now let's set up the ofxProjectionMask designer
    designer.setup(); //Default is STRETCH_TO_MASKFRAME
    //designer.setup(DO_NOT_STRETCH); //Otherwise, explicitly state which mode you want
    //designer.setup(STRETCH_TO_MASKFRAME);
    //designer.setup(HOMOGRAPHY);

    //When you are ready to use this addon fullscreen with a
    //projector you will need this line. (Scroll to the bottom
    //of this file for more on how to do that
    //designer.setup(DO_NOT_STRETCH, PRESETS_PRODUCTION);

    //Now let's assign our two patterns to the designer
    designer.add(&pattern1);
    designer.add(&pattern2);

    //And let's init the variables our patterns are going to use
    currentHue = 0;
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();
}

void ofApp::update(){
    //Tell the designer where your mouse is
    designer.update(mouseX, mouseY);

    //Let's draw a hue-cycle in our first pattern
    pattern1.beginLayer();
    {
        currentHue += 0.2;
        if(currentHue >= 256){
            currentHue = 0;
        }
        
        ofBackground(ofColor::fromHsb(currentHue, 255, 255));
        for(int i = 5; i < pattern1.getWidth(); i += 40){
            for(int j = 15; j < pattern1.getHeight(); j += 40){
                ofSetColor(ofColor::black);
                ofDrawBitmapString(ofToString((int)currentHue), i, j);
            }
        }
    }
    pattern1.endLayer();

    //Let's draw a grid in the second pattern
    pattern2.beginLayer();
    {
        ofBackground(ofColor::black);
        for(int i = 40; i < pattern2.getWidth(); i += 80){
            for(int j = 40; j < pattern2.getHeight(); j += 80){
                ofSetColor(ofColor::white);
                ofRect(0, i, pattern2.getWidth(), 20);
                ofRect(j, 0, 20, pattern2.getHeight());
            }
        }
    }
    pattern2.endLayer();
    
    //That's it!! The rest is boilerplate, copy the lines
    //below to make the designer work in your apps
    
    //Now head down to the bottom of this file to learn about presets!
    //You'll need to do this to start using the addon with a projector.
}

void ofApp::draw(){
    designer.draw();
}

void ofApp::keyReleased(int key){
    designer.keyReleased(key);
}

void ofApp::mouseDragged(int x, int y, int button){
    designer.mouseDragged();
}

void ofApp::mousePressed(int x, int y, int button){
    designer.mousePressed();
}

void ofApp::mouseReleased(int x, int y, int button){
    designer.mouseReleased();
}

void ofApp::keyPressed(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

/*
  How to switch over to fullscreen/dual-screen setup
  ==================================================
  Ok, so you are done playing with the development mode and you
  want to get started with a projector! Good, that's not
  unreasonable :)
 
  This addon uses ofxSecondWindow to handle running fullscreen
  with a projector. All you need to do is check your operating
  system's dual-screen display settings, and enter the correct
  values in the 'production' portion of the Presets.cpp file.
  
  How to do that?
  ---------------
  You will probably want to arrange your dualscreens like this:

        +--------+----------+ <-- top aligned
        | design | for-real |
        | canvas | mappings |
        +--------|          |
                 +----------+
         screen 1  screen 2
         (laptop) (projector)

  When you have done that, take note of your screen and
  projector screen resolutions, and plug in the numbers to
  this file:

      /addons/ofxProjectionMapper/src/Presets.cpp

  When you have done that, you can come back to this file and
  switch to using the setup() call with the PRESETS_PRODUCTION
  constant in it.
*/