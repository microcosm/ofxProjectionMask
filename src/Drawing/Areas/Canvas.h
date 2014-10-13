#pragma once
#include "ofMain.h"

class Canvas{
public:
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    void setName(string name);
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setNumGridLines(int numGridLinesX, int numGridLinesY);
    void draw();
    
protected:
    string name;
    int width;
    int height;
    int x;
    int y;
    int numGridLinesX;
    int numGridLinesY;
    int gridLineDistanceX;
    int gridLineDistanceY;
    void calculateGridLineDistances();
};