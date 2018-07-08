#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

int main(){
    ofGLFWWindowSettings settings;
    settings.setSize(1024, 768);
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.setSize(1024, 768);
    settings.resizable = false;
    settings.multiMonitorFullScreen = true;
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> secondWindow = ofCreateWindow(settings);
    secondWindow->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
    ofAddListener(secondWindow->events().draw, mainApp.get(), &ofApp::drawSecondWindow);

    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
