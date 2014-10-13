#pragma once
#include "ofMain.h"
#include "CanvasContents.h"
#include "MaskFrame.h"
#include "TextArea.h"
#include "XmlPersistence.h"
#include "BufferPattern.h"
#include "Presets.h"

class ofxProjectionMapper{
public:
    
    void setup(BufferPattern* pattern);
    void update(int mouseX, int mouseY);
    void draw();
    
    void keyReleased(int key);
    void mouseDragged();
    void mousePressed();
    void mouseReleased();
    
    void setVolumes(float *volume, vector<float> *nonPlaybackVolumes);
    
    Canvas *getLiveCanvas();
    
    void loadObjects();
    void saveObjects();
    void autoSaveObjects();
    
protected:
    Presets presets;
    Mode mode;
    TextArea textArea;
    Canvas designCanvas, liveCanvas;
    CanvasContents canvasContents;
    MaskFrame *selectedMaskFrame;
    ofVec2f mouse, mouseOffset;
    Corner selectedCorner;
    XmlPersistence xml;
    BufferPattern *pattern;
    
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
    void scaleSelectedMaskFrame();
    void scaleSelectedMaskFrame(int x, int y, int newWidth, int newHeight, int smallestLegalWidth, int smallestLegalHeight, bool floatX, bool floatY);
    
    void setMouseOffsetFromSelectedMaskFrame();
    void setMouseOffsetFromSelectedMaskPoint();
    void setMouseOffsetFromSelectedCorner();
    
    void setMouseOffsetFromTopLeftCorner();
    void setMouseOffsetFromTopRightCorner();
    void setMouseOffsetFromBottomRightCorner();
    void setMouseOffsetFromBottomLeftCorner();
};