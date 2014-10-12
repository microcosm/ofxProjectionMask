#pragma once
#include "ofMain.h"
#include "ofExtensions.h"

class PointObject{
public:
    PointObject(){
        highlighted = false;
    }
    int getX();
    int getY();
    int getLiveX();
    int getLiveY();
    
    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);
    
    void setLivePosition(int x, int y);
    void setLiveX(int x);
    void setLiveY(int y);
    
    void drawDesign();
    void drawLive();
    
    int getRadius();
    bool isHighlighted();
    void setHighlighted(bool isHighlighted);
    
protected:
    bool highlighted;
    ofVec2f position;
    ofVec2f livePosition;
};