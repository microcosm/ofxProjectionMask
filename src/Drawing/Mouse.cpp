#include "Mouse.h"

void Mouse::setup(Canvas* _canvas) {
    canvas = _canvas;
}

void Mouse::set(int _x, int _y) {
    x = _x + adjustment.x;
    y = _y + adjustment.y;
}

void Mouse::setSelection(MaskFrame* maskFrame) {
    selectedMaskFrame = maskFrame;
    setMouseOffsetFromSelectedMaskFrame();
}

int Mouse::newSelectionWidth(){
    int mouseXConstrained = clampInt(x, canvas->getX() + offsetX, canvas->getX() + canvas->getWidth() + offsetX);
    int newWidth;
    
    if(selectedCorner == TopLeft){
        
        newWidth = (selectedMaskFrame->getX() + selectedMaskFrame->getWidth() + offsetX) - mouseXConstrained;
        
    }else if(selectedCorner == TopRight){
        
        newWidth = mouseXConstrained - (selectedMaskFrame->getX() + offsetX);
        
    }else if(selectedCorner == BottomRight){
        
        newWidth = mouseXConstrained - (selectedMaskFrame->getX() + offsetX);
        
    }else if(selectedCorner == BottomLeft){
        
        newWidth = (selectedMaskFrame->getX() + selectedMaskFrame->getWidth() + offsetX) - mouseXConstrained;
    }
    
    int smallestLegalWidth = selectedMaskFrame->getSmallestLegalWidth(selectedCorner);
    int newWidthClamped = clampInt(newWidth, smallestLegalWidth);
    return newWidthClamped;
}

int Mouse::newSelectionHeight(){
    int mouseYConstrained = clampInt(y, canvas->getY() + offsetY, canvas->getY() + canvas->getHeight() + offsetY);
    int newHeight;
    
    if(selectedCorner == TopLeft){
        
        newHeight = (selectedMaskFrame->getY() + selectedMaskFrame->getHeight() + offsetY) - mouseYConstrained;
        
    }else if(selectedCorner == TopRight){
        
        newHeight = (selectedMaskFrame->getY() + selectedMaskFrame->getHeight() + offsetY) - mouseYConstrained;
        
    }else if(selectedCorner == BottomRight){
        
        newHeight = mouseYConstrained - (selectedMaskFrame->getY() + offsetY);
        
    }else if(selectedCorner == BottomLeft){
        
        newHeight = mouseYConstrained - (selectedMaskFrame->getY() + offsetY);
    }
    
    int smallestLegalHeight = selectedMaskFrame->getSmallestLegalHeight(selectedCorner);
    int newHeightClamped = clampInt(newHeight, smallestLegalHeight);
    return newHeightClamped;
}

float Mouse::newSelectionX() {
    return x - offsetX;
}

float Mouse::newSelectionY() {
    return y - offsetY;
}

void Mouse::setMouseOffsetFromSelectedMaskFrame(){
    TransformState transformState = selectedMaskFrame->getTransformState();
    if(transformState == Translating){
        setMouseOffsetFromTopLeftCorner();
    }else if(transformState == Scaling){
        setMouseOffsetFromSelectedCorner();
    }else if(transformState == Masking){
        setMouseOffsetFromSelectedMaskPoint();
    }
}

void Mouse::setMouseOffsetFromSelectedMaskPoint(){
    offsetX = x - selectedMaskFrame->getSelectedMaskPointX();
    offsetY = y - selectedMaskFrame->getSelectedMaskPointY();
}

void Mouse::setMouseOffsetFromSelectedCorner(){
    selectedCorner = selectedMaskFrame->highlightedCorner();
    if(selectedCorner == TopLeft){
        setMouseOffsetFromTopLeftCorner();
    }else if(selectedCorner == TopRight){
        setMouseOffsetFromTopRightCorner();
    }else if(selectedCorner == BottomRight){
        setMouseOffsetFromBottomRightCorner();
    }else if(selectedCorner == BottomLeft){
        setMouseOffsetFromBottomLeftCorner();
    }
}

void Mouse::setMouseOffsetFromTopLeftCorner(){
    offsetX = x - selectedMaskFrame->getX();
    offsetY = y - selectedMaskFrame->getY();
}

void Mouse::setMouseOffsetFromTopRightCorner(){
    offsetX = x - selectedMaskFrame->getX() - selectedMaskFrame->getWidth();
    offsetY = y - selectedMaskFrame->getY();
}

void Mouse::setMouseOffsetFromBottomRightCorner(){
    offsetX = x - selectedMaskFrame->getX() - selectedMaskFrame->getWidth();
    offsetY = y - selectedMaskFrame->getY() - selectedMaskFrame->getHeight();
}

void Mouse::setMouseOffsetFromBottomLeftCorner(){
    offsetX = x - selectedMaskFrame->getX();
    offsetY = y - selectedMaskFrame->getY() - selectedMaskFrame->getHeight();
}