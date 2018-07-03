#include "ofExtensions.h"

void ofCircleStroke(int x, int y, int radius, int stroke, ofColor fillColor, ofColor strokeColor){
    
    /* 
     Making an ofCircle with a stroke
     ================================
     - Only the stroke (outer line) of a circle is smoothed
     - To create a stroke you have to call ofCircle twice, once with ofFill and once without
     - But ofCircle is limited by what openGL can do and so the line segments don't look good
     when you ofSetLineWidth > 1
     - Therefore to create the illusion you have to create 2 x ofCircle, each with it's own 
     1px stroke the same color as the fill
     - Then you still have to choose between tiny gaps vs. a properly smooth edge
     (adjust ofSetLineWidth(0..1) to see this)
     - It has been reported on github:
     http://forum.openframeworks.cc/index.php?topic=7278.0
     */
    
    int strokeRadius = radius + stroke;
    ofSetLineWidth(1);
    
    ofSetColor(strokeColor);
    ofFill();
    ofDrawCircle(x, y, strokeRadius);
    ofSetColor(strokeColor);
    ofNoFill();
    ofDrawCircle(x, y, strokeRadius);
    
    ofSetColor(fillColor);
    ofFill();
    ofDrawCircle(x, y, radius);
    ofSetColor(fillColor);
    ofNoFill();
    ofDrawCircle(x, y, radius);
}

void ofCircleNoStroke(int x, int y, int radius, ofColor color){
    
    ofSetLineWidth(1);
    
    ofSetColor(color);
    ofFill();
    ofDrawCircle(x, y, radius);
    ofSetColor(color);
    ofNoFill();
    ofDrawCircle(x, y, radius);
}

float clampFloat(float value, float lowerBoundary, float upperBoundary){
    if(value < lowerBoundary){
        return lowerBoundary;
    }else if(value > upperBoundary){
        return upperBoundary;
    }else{
        return value;
    }
}

int clampInt(int value, int lowerBoundary, int upperBoundary){
    if(value < lowerBoundary){
        return lowerBoundary;
    }else if(value > upperBoundary){
        return upperBoundary;
    }else{
        return value;
    }
}

int clampInt(int value, int lowerBoundary){
    if(value < lowerBoundary){
        return lowerBoundary;
    }
    return value;
}

int getNextIndex(int currentIndex, int size){
    if(currentIndex + 1 == size){
        return 0;
    }
    return currentIndex + 1;
}

//http://stackoverflow.com/questions/236129/splitting-a-string-in-c
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    return split(s, delim, elems);
}





