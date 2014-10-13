#pragma once
#include "ofMain.h"
#include "MaskFrame.h"
#include "DragHandle.h"
#include "Canvas.h"

class Mouse{
public:
    Mouse() {
        adjustment.x = -1;
        adjustment.y = -2;
    }
    float x, y;
    void setup(Canvas* _canvas);
    void set(int _x, int _y);
    
    void setSelection(MaskFrame* maskFrame);
    int newSelectionWidth();
    int newSelectionHeight();
    float newSelectionX();
    float newSelectionY();
    
protected:
    ofVec2f adjustment;
    Canvas* canvas;
    MaskFrame* selectedMaskFrame;
    float offsetX, offsetY;
    Corner selectedCorner;
    
    void setMouseOffsetFromSelectedMaskFrame();
    void setMouseOffsetFromSelectedMaskPoint();
    void setMouseOffsetFromSelectedCorner();
    
    void setMouseOffsetFromTopLeftCorner();
    void setMouseOffsetFromTopRightCorner();
    void setMouseOffsetFromBottomRightCorner();
    void setMouseOffsetFromBottomLeftCorner();
};