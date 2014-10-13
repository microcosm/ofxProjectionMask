#pragma once
#include "ofMain.h"
#include "PointObject.h"
#include "ofExtensions.h"

enum MaskPointType { Real, Ghost };
enum Direction { Left, Right, Up, Down };

class MaskPoint : public PointObject{
public:
    void setType(MaskPointType type);
    MaskPointType getType();
    
    void drawDesign();
    void drawLive();

protected:
    MaskPointType type;
};