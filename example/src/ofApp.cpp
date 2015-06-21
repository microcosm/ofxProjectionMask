#include "ofApp.h"
/*
  ofxProjectionMask
  =================
  ofxProjectionMask is an addon which allows you to mask out
  areas of the real world onto which to project any light
  pattern you like.

  Unlike projection mapping, this is not about creating the
  illusion that a light surface is 'mapped onto' a physical
  object; instead this addon simply prevents the light from
  showing up anywhere outside of the mask you draw.

  In other words, this addon separates out the masking from
  the mapping, and only does the former without doing the
  latter. You can of course, still pre-transform your patterns
  in code if you want to achieve traditional projection mapping.

  Just want to get a quick taste?
  -------------------------------
  To get going quickly and see if this addon is for you, just
  run it and follow the instructions to make your first shape.

  You will see a default pattern which cycles through hues.
  This is a good way to play with the UI and see what can
  be done.

  Ready to dig deeper?
  --------------------
  The addon consists of:
  1. The ofxProjectionMask class, which is a designer UI
     allowing you to slice out a shape with your mouse,
     representing some physical object within view of your
     projector.
  2. Several sample ___Pattern classes, from the base class
     BufferPattern. For example, the default pattern in this
     example is HueCyclePattern, which simply runs through
     the colors of the rainbow.

  To play with some of the other Pattern classes that come with
  this addon, head over to ofApp.h and start uncommenting some
  of the examples.

  If you get the idea and are ready to make your own Patterns,
  head to the bottom of this file, after the code. There are a
  set of instructions there to get you started.

  Fullscreen/dual-screen setup
  ----------------------------
  By default this addon runs in 'development' mode, with all
  the content squeezed into a single, floating window on a
  single computer display. To run this app for real you'll
  need to add a projector as your second display. There are
  full instructions on that at the bottom of this file.
*/

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    //First, we set up our pattern, which sets up its buffer(s)
    pattern.setup();
    pattern1.setupSingleLayer(500, 500);

    //Then we assign the pattern to the designer, which displays
    //canvas and drawing tools, and renders the buffers.
    designer.setup((BufferPattern*)&pattern);
    //designer.setup(pattern1);
    //designer.setup((BufferPattern*)&pattern, PRESETS_PRODUCTION); //explained below
}

void ofApp::update(){
    //Try switching the pattern in ofApp.h
    pattern1.beginLayer();
    {
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        ofRect(5, 5, 300, 300);
    }
    pattern1.endLayer();

    designer.update(mouseX, mouseY);

    //When you switch to ArgumentPattern, uncomment this:
    //pattern.mapToColors(mouseX, mouseY);
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
  How to draw your own patterns
  =============================
  Actually using the addon is easy enough, but you might
  need to invest an hour to get started. Easiest way is to
  follow these step-by-step instructions.

  The setup pattern
  -----------------
  First, where are the graphics drawn? Take a look at this
  file:

    /addons/ofxProjectionMapper/src/Patterns/TestPatterns/
    SetupPattern.cpp

  This is the simplest test pattern, outputting only white.
  It's helpful when you are actually drawing a mask for real
  with the designer, as it shows up very clearly every pixel
  right to the edges of your mask, so you can easily confirm
  the shape.

  Any number of buffers
  ---------------------
  Notice that SetupPattern above inherits from BufferPattern.
  This base class handles a collection of buffers for you
  (FBO's). You don't really need to know much about buffers,
  other than to think of them as little virtual displays you
  draw into, ready to render for real later.
  http://www.openframeworks.cc/documentation/gl/ofFbo.html

  SetupPattern has only one buffer, but you are about to make
  your own pattern with two buffers. The first buffer will
  provide the pattern for the first mask you draw. The second
  buffer will fill the second mask. If you create a third mask,
  there will be no third buffer to fill it, so it will be
  filled with the contents of the first buffer.

  Use a test pattern as a template
  --------------------------------
  1. Create a new cpp/h file duo in your own project's /src
     folder, with names like this:

         /src/MyCustomPattern.cpp
         /src/MyCustomPattern.h

  2. Copy the contents of the SetupPattern class files into
     the respective custom pattern class files, and rename
     the new classes to match their filenames:

        class SetupPattern ~> class MyCustomPattern

  3. Change the number of buffers to two:

        const int numberOfBuffers = 2;

  4. Now let's increase the size of the buffers in the
     setup() method. This is the 'resolution' of the buffers,
     or how many pixels they each hold:

         width = 200; ~> width = 400;
         height = 200; ~> height = 400;

  5. Now edit the contents of the buffer to make your own
     pattern. You can address each buffer individually with
     a method like this:

          void MyCustomPattern::update(){
              ofFill();

              //Fill buffer #1 with horizontal bars
              buffers[0].begin();
              for(int i = 0; i < 8; i++) {
                  if(i % 2 == 0) ofSetColor(ofColor::blue);
                  else ofSetColor(ofColor::red);
                  ofRect(0, i * 50, width, 50);
              }
              buffers[0].end();

              //Fill buffer #2 with vertical bars
              buffers[1].begin();
              for(int i = 0; i < 8; i++) {
                  if(i % 2 == 0) ofSetColor(ofColor::yellow);
                  else ofSetColor(ofColor::green);
                  ofRect(i * 50, 0, 50, height);
              }
              buffers[1].end();
          }

  6. Create an instance of your custom pattern class in
     ofApp.h:
          //... other includes
          #include "MyCustomPattern.h"

          class ofApp : public ofBaseApp {
          public:
              //... etc
              ofxProjectionMask designer;
              MyCustomPattern myPattern;
          };

     And pass it to the mapper in ofApp.cpp:

          void ofApp::setup(){
              //... etc
              myPattern.setup();
              designer.setup((BufferPattern*)&myPattern);
          }

  7. Run the app and use the designer to create two or more
     new masks. Your patterns are inside them!

  That should give you enough to get going with your own
  patterns. If you want to see how to pass input values, such
  as from the mouse (or a Kinect!) to your patterns, see the
  ArgumentPattern example.


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

  When you have done that, you can come back to ofApp.cpp above,
  and switch out this line:

      mapper.setup((BufferPattern*)&pattern);

  for this line:

      mapper.setup((BufferPattern*)&pattern, PRESETS_PRODUCTION);

  That's it! Report any issues via Github.
*/