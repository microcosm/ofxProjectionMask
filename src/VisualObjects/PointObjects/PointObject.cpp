#include "PointObject.h"

const int radius = 4;

int PointObject::getX(){
    return position.x;
}

int PointObject::getY(){
    return position.y;
}

int PointObject::getLiveX(){
    return livePosition.x;
}

int PointObject::getLiveY(){
    return livePosition.y;
}

void PointObject::setPosition(int x, int y){
    this->position.x = x;
    this->position.y = y;
}

void PointObject::setX(int x){
    this->position.x = x;
}

void PointObject::setY(int y){
    this->position.y = y;
}

void PointObject::setLivePosition(int x, int y){
    this->livePosition.x = x;
    this->livePosition.y = y;
}

void PointObject::setLiveX(int x){
    this->livePosition.x = x;
}

void PointObject::setLiveY(int y){
    this->livePosition.y = y;
}

void PointObject::drawDesign(){
    
}

void PointObject::drawLive(){
    
}

int PointObject::getRadius(){
    return radius;
}

bool PointObject::isHighlighted(){
    return this->highlighted;
}

void PointObject::setHighlighted(bool isHighlighted){
    this->highlighted = isHighlighted;
}