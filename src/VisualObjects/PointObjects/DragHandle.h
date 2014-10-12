#pragma once
#include "ofMain.h"
#include "PointObject.h"
#include "ofExtensions.h"

enum Corner { TopLeft, TopRight, BottomLeft, BottomRight };

class DragHandle : public PointObject{
public:
    Corner getCorner();
    void setCorner(Corner corner);
    
    void drawDesign();
    void drawLive();
    
protected:
    Corner corner;
};