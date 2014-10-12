#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

int main( ){
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window,1024,768,OF_FULLSCREEN);
    ofRunApp(new ofApp());
}
