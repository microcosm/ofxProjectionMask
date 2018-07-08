#pragma once
#include "ofMain.h"
#include "ofxLayerMask.h"
#include "CanvasContents.h"
#include "MaskFrame.h"
#include "TextArea.h"
#include "Xml.h"
#include "Presets.h"
#include "Mouse.h"

class ofxProjectionMask{
public:
    void setup(StretchMode _stretchMode=STRETCH_TO_MASKFRAME, PresetMode presetMode=PRESETS_DEVELOPMENT);
    void setupSecondWindow();
    void setupCommon();

    void setStorageFileName(string fileName);
    ofxLayerMask* newPattern(int width, int height);
    void layout();
    void update(int mouseX, int mouseY);
    void draw(ofEventArgs& args);
    void drawSecondWindow();
    void drawBackground(int width, int height, int alpha);

    void keyReleased(ofKeyEventArgs& args);
    void mouseDragged(ofMouseEventArgs &args);
    void mousePressed(ofMouseEventArgs &args);
    void mouseReleased(ofMouseEventArgs &args);
    
    void setVolumes(float *volume, vector<float> *nonPlaybackVolumes);
    ofxLayerMask* nextPattern();
    ofxLayerMask* getBackground();

protected:
    Presets presets;
    DisplayMode displayMode;
    StretchMode stretchMode;
    
    Canvas designCanvas, liveCanvas;
    CanvasContents canvasContents;
    vector<ofxLayerMask*> patterns;
    ofxLayerMask background;

    Mouse mouse;
    MaskFrame *selectedMaskFrame;
    TextArea textArea;
    Xml xml;
    bool secondWindowSetup = false;
    
    void undo();
    void redo();
    
    void nudge(Direction direction);
    void toggleFrameNudge();
    
    void createNewMaskFrame();
    void createNewMaskPoint();
    void deleteHighlightedItem();
    
    void cycleMode();
    bool mouseIsOverDesignCanvas();
    
    void drawLiveCursor();
    void drawBufferPreviews();
    
    bool isTransforming();
};
