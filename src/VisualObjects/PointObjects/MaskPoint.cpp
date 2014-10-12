#include "MaskPoint.h"

const ofColor maskPointColor = ofColor(255, 255, 255, 128);
const ofColor highlightColor = ofColor(0, 255, 255, 255);
const ofColor nonHighlightColor = ofColor(0, 128, 128, 255);
const ofColor ghostColor = ofColor(0, 255, 255, 128);

void MaskPoint::setType(MaskPointType type){
    this->type = type;
}

MaskPointType MaskPoint::getType(){
    return this->type;
}

void MaskPoint::drawDesign(){
    if(this->type == Real){
        ofSetColor(maskPointColor);
        ofRect(this->getX(), this->getY(), 1, 1);
        if(this->isHighlighted()){
            ofNoFill();
            ofSetColor(highlightColor);
            ofCircle(this->getX(), this->getY(), this->getRadius());
        }
    }
    if(this->type == Ghost){
        ofSetColor(maskPointColor);
        ofRect(this->getX(), this->getY(), 1, 1);
        ofNoFill();
        ofSetColor(ghostColor);
        ofCircle(this->getX(), this->getY(), this->getRadius());
    }
}

void MaskPoint::drawLive(){
    if(this->type == Real){
        ofSetColor(maskPointColor);
        ofRect(this->getLiveX(), this->getLiveY(), 1, 1);
        if(this->isHighlighted()){
            ofSetColor(highlightColor);
        }else{
            ofSetColor(nonHighlightColor);
        }
        ofNoFill();
        ofCircle(this->getLiveX(), this->getLiveY(), this->getRadius());
    }
    if(this->type == Ghost){
        ofSetColor(maskPointColor);
        ofRect(this->getLiveX(), this->getLiveY(), 1, 1);
        ofNoFill();
        ofSetColor(ghostColor);
        ofCircle(this->getLiveX(), this->getLiveY(), this->getRadius());
    }
}