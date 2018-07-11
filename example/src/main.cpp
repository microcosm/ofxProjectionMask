#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

int getNumScreens(){
    CGDisplayCount displayCount;
    CGDirectDisplayID displays[32];
    CGGetActiveDisplayList(32, displays, &displayCount);
    return displayCount;
}

int main(){
    int numScreens = getNumScreens();

    ofGLFWWindowSettings settings;
    //settings.windowMode = OF_FULLSCREEN;
    settings.monitor = 0;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    settings.shareContextWith = mainWindow;
    settings.monitor = numScreens > 1 ? 1 : settings.monitor;
    shared_ptr<ofAppBaseWindow> secondWindow = ofCreateWindow(settings);
    secondWindow->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
    ofAddListener(secondWindow->events().draw, mainApp.get(), &ofApp::drawSecondWindow);

    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
