#pragma once
#include "ofMain.h"
#include "ObjectStore.h"
#include "MaskFrame.h"
#include "TextArea.h"
#include "XmlPersistence.h"
#include "BufferPattern.h"
#include "Presets.h"

class ofxProjectionMapper{
public:
    
    ofxProjectionMapper(){
        initialise();
        mode = Design;
    }
    void setMousePosition(int x, int y);
    void setVolumes(float *volume, vector<float> *nonPlaybackVolumes);
    void setPattern(BufferPattern* pattern);
    void update();
    
    Canvas *getLiveCanvas();
    
    void draw();
    void undo();
    void redo();
    
    void loadObjects();
    void saveObjects();
    void autoSaveObjects();
    
    void respondToMouseDrag();
    void respondToMouseDown();
    void respondToMouseRelease();
    void respondToKey(int key);
    
protected:
    Presets presets;
    Mode mode;
    int mouseX, mouseY;
    TextArea textArea;
    Canvas designCanvas, liveCanvas;
    MaskFrame *selectedMaskFrame;
    ObjectStore objectStore;
    ofVec2f mouseOffset;
    Corner selectedCorner;
    XmlPersistence xml;
    BufferPattern *pattern;
    
    void initialise();
    
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