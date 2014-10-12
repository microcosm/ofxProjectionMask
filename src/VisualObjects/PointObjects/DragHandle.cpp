#include "DragHandle.h"

const ofColor notHighlightedColor = ofColor(255, 255, 255, 128);
const ofColor highlightedColor = ofColor(0, 255, 255, 128);

Corner DragHandle::getCorner(){
    return corner;
}

void DragHandle::setCorner(Corner corner){
    this->corner = corner;
}

void DragHandle::drawDesign(){
    if(this->highlighted){
        ofCircleNoStroke(this->position.x, this->position.y, this->getRadius(), highlightedColor);
    }else{
        ofCircleNoStroke(this->position.x, this->position.y, this->getRadius(), notHighlightedColor);
    }
}

void DragHandle::drawLive(){
    if(this->highlighted){
        ofCircleNoStroke(this->livePosition.x, this->livePosition.y, this->getRadius(), highlightedColor);
    }else{
        ofCircleNoStroke(this->livePosition.x, this->livePosition.y, this->getRadius(), notHighlightedColor);
    }
}