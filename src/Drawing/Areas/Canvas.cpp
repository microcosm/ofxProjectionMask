#include "Canvas.h"

const ofColor outlineColor = ofColor(255, 255, 255, 255);
const ofColor interiorColor = ofColor(255, 255, 255, 100);
const int nameTextOffset = 8;

int Canvas::getWidth(){
    return this->width;
}

int Canvas::getHeight(){
    return this->height;
}

int Canvas::getX(){
    return this->x;
}

int Canvas::getY(){
    return this->y;
}

void Canvas::setName(string name){
    this->name = name;
}

void Canvas::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Canvas::setSize(int width, int height){
    this->width = width;
    this->height = height;
    this->calculateGridLineDistances();
}

void Canvas::setNumGridLines(int numGridLinesX, int numGridLinesY){
    this->numGridLinesX = numGridLinesX;
    this->numGridLinesY = numGridLinesY;
    this->calculateGridLineDistances();
}

void Canvas::calculateGridLineDistances(){
    if(this->width > 0 && this->numGridLinesX > 0){
        this->gridLineDistanceX = ceil((float)this->width / this->numGridLinesX);
    }
    if(this->height > 0 && this->numGridLinesY > 0){
        this->gridLineDistanceY = ceil((float)this->height / this->numGridLinesY);
    }
}

void Canvas::draw(){
    ofNoFill();
    ofSetColor(outlineColor);
    ofRect(0, 0, width, height);
    ofSetColor(interiorColor);
    for (int i = 0; i < width; i += this->gridLineDistanceX){
        ofLine(i, 0, i, height);
    }
    for (int i = 0; i < height; i += this->gridLineDistanceY){
        ofLine(0, i, width, i);
    }
}