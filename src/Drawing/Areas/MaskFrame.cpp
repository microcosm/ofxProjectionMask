#include "MaskFrame.h"

const ofColor notHighlightedColor = ofColor(255, 255, 255, 128);
const ofColor highlightedColor = ofColor(0, 255, 255, 255);
const ofColor maskLineColor = ofColor(255, 255, 255, 128);
const int minimumFrameSize = 6;
const int frameMargin = 2;
const int cursorMargin = 6;

//Public
int MaskFrame::getId(){
    return frameId;
}

void MaskFrame::setId(int newId){
    frameId = newId;
}

void MaskFrame::assignCanvases(Canvas& designCanvas, Canvas& liveCanvas){
    this->designCanvas = &designCanvas;
    this->liveCanvas = &liveCanvas;
}

void MaskFrame::setPattern(ofxLayerMask *pattern){
    this->pattern = pattern;
}

void MaskFrame::highlightIfCloseTo(int absoluteX, int absoluteY){
    this->highlightDragHandlesIfCloseTo(absoluteX, absoluteY);
    if(this->hasHighlightedDragHandle()){
        this->highlighted = false;
        this->unhighlightAllMaskPoints();
    }else{
        this->highlighted = true;
        this->highlightRectIfCloseTo(absoluteX, absoluteY);
        this->highlightMaskPointsIfCloseTo(absoluteX, absoluteY);
        
        if(this->hasHighlightedMaskPoint()){
            this->hasAGhostPoint = false;
        }else{
            this->findGhostPointIfCloseTo(absoluteX, absoluteY);
        }
    }
}

void MaskFrame::setHighlighted(bool isHighlighted){
    this->highlighted = isHighlighted;
}

bool MaskFrame::isHighlighted(){
    return this->highlighted;
}

bool MaskFrame::hasHighlightedDragHandle(){
    for(int i = 0; i < dragHandles.size(); i++){
        if(dragHandles[i]->isHighlighted()){
            return true;
            break;
        }
    }
    return false;
}

bool MaskFrame::hasHighlightedMaskPoint(){
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->isHighlighted()){
            return true;
            break;
        }
    }
    return false;
}

MaskPoint* MaskFrame::getHighlightedMaskPoint(){
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->isHighlighted()){
            return maskPoints[i];
            break;
        }
    }
    return 0;
}

DragHandle* MaskFrame::getHighlightedDragHandle(){
    for(int i = 0; i < dragHandles.size(); i++){
        if(dragHandles[i]->isHighlighted()){
            return dragHandles[i];
            break;
        }
    }
    return 0;
}

bool MaskFrame::hasGhostPoint(){
    return this->hasAGhostPoint;
}

bool MaskFrame::canDrawLive(){
    if(maskPoints.size() > 3){
        return true;
    }else if(maskPoints.size() == 3){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(!maskPoints[i]->equals(maskPoints[j])){
                    return true;
                }
            }
        }
    }
    return false;
}

int MaskFrame::getSelectedMaskPointX(){
    return selectedMaskPoint->getX();
}

int MaskFrame::getSelectedMaskPointY(){
    return selectedMaskPoint->getY();
}

SafeDeque<MaskPoint> *MaskFrame::getMaskPoints(){
    return &maskPoints;
}

TransformState MaskFrame::getTransformState(){
    return this->transformState;
}

void MaskFrame::setTransformState(TransformState transformState){
    this->transformState = transformState;
    this->respondToStateChange();
}

void MaskFrame::drawDesign(){
    ofPushMatrix();
    ofTranslate(this->designPosition.x, this->designPosition.y);
    
    bool hasHighlightedDragHandle = this->hasHighlightedDragHandle();
    bool hasHighlightedMaskPoint = this->hasHighlightedMaskPoint();
    
    if((highlighted || hasHighlightedDragHandle || getTransformState() == Scaling) && !hasHighlightedMaskPoint){
        ofSetColor(highlightedColor);
    }else{
        ofSetColor(notHighlightedColor);   
    }
    ofRect(0, 0, this->designWidth, this->designHeight);
    
    if((highlighted || hasHighlightedDragHandle) && !hasHighlightedMaskPoint){
        for(int i = 0; i < dragHandles.size(); i++){
            dragHandles[i]->drawDesign();
        }
    }
    
    if(maskPoints.size() > 1){
        ofSetColor(maskLineColor);
        for(int i = 0; i < maskPoints.size(); i++){
            int nextIndex = getNextIndex(i, maskPoints.size());
            ofLine(maskPoints[i]->getX(), maskPoints[i]->getY(), maskPoints[nextIndex]->getX(), maskPoints[nextIndex]->getY());
        }
    }
    
    if(this->hasAGhostPoint){
        ghostPoint.drawDesign();
    }
    
    for(int i = 0; i < maskPoints.size(); i++){
        maskPoints[i]->drawDesign();
    }
    
    ofPopMatrix();
}

void MaskFrame::drawLive(DisplayMode mode, StretchMode stretchMode){
    ofPushMatrix();
    ofTranslate(this->livePosition.x, this->livePosition.y);
    
    if(this->canDrawLive()){
        homographyMode = stretchMode == HOMOGRAPHY && maskPoints.size() == 4;
        
        if(homographyMode) {
            ofSetColor(ofColor::white);
            prepareHomography();
            homography.begin(input, output);
            pattern->drawLayer(0, false);
            homography.end();
        } else {
            pattern->beginMask();
            ofPushStyle();
            {
                ofFill();
                ofBackground(ofColor::black);
                ofSetColor(ofColor::white);
                ofBeginShape();
                for(int i = 0; i < maskPoints.size(); i++){
                    if(stretchMode == STRETCH_TO_MASKFRAME) {
                        x = ofMap(maskPoints[i]->getLiveX(), 0, getLiveWidth(), 0, pattern->getWidth());
                        y = ofMap(maskPoints[i]->getLiveY(), 0, getLiveHeight(), 0, pattern->getHeight());
                    } else {
                        x = maskPoints[i]->getLiveX();
                        y = maskPoints[i]->getLiveY();
                    }
                    ofVertex(x, y);
                }
                ofEndShape();
            }
            ofPopStyle();
            pattern->endMask();
            
            if(stretchMode == STRETCH_TO_MASKFRAME) {
                pattern->draw(0, 0, getLiveWidth(), getLiveHeight());
            } else {
                pattern->draw();
            }
        }
    }
    
    if(mode != Live){
        
        bool hasHighlightedDragHandle = this->hasHighlightedDragHandle();
        bool hasHighlightedMaskPoint = this->hasHighlightedMaskPoint();

        ofPushStyle();
        {
            if((highlighted || hasHighlightedDragHandle || getTransformState() == Scaling) && !hasHighlightedMaskPoint){
                ofSetColor(highlightedColor);
            }else{
                ofSetColor(notHighlightedColor);
            }
            ofRect(0, 0, this->liveWidth, this->liveHeight);

            if((highlighted || hasHighlightedDragHandle) && !hasHighlightedMaskPoint){
                for(int i = 0; i < dragHandles.size(); i++){
                    dragHandles[i]->drawLive();
                }
            }
        }
        ofPopStyle();
    }
        
    if(mode == Design){
        if(maskPoints.size() > 2){
            ofSetColor(maskLineColor);
            for(int i = 0; i < maskPoints.size(); i++){
                int nextIndex = getNextIndex(i, maskPoints.size());
                ofLine(maskPoints[i]->getLiveX(), maskPoints[i]->getLiveY(), maskPoints[nextIndex]->getLiveX(), maskPoints[nextIndex]->getLiveY());
            }
        }
    }
    
    if(mode != Live){
        
        if(this->hasAGhostPoint){
            ghostPoint.drawLive();
        }
        
        for(int i = 0; i < maskPoints.size(); i++){
            maskPoints[i]->drawLive();
        }
    }
    
    ofPopMatrix();
}

void MaskFrame::setSize(int width, int height){
    this->designWidth = width;
    this->designHeight = height;
    setDragHandlePositions();
    transposeToLiveCanvas();
}

void MaskFrame::setSize(int width, int height, Corner movingCorner){
    this->setPositionsToMatchScaleChange(width, height, movingCorner);
    this->setSize(width, height);
}

void MaskFrame::setLiveSize(int width, int height){
    this->liveWidth = width;
    this->liveHeight = height;
    transposeToDesignCanvas();
    setDragHandlePositions();
}

void MaskFrame::setLiveSize(int width, int height, Corner movingCorner){
    this->setLivePositionsToMatchScaleChange(width, height, movingCorner);
    this->setLiveSize(width, height);
}

void MaskFrame::setPosition(int absoluteX, int absoluteY){
    setRectPosition(absoluteX, absoluteY);
    setDragHandlePositions();
    transposeToLiveCanvas();
}

void MaskFrame::setLivePosition(int absoluteX, int absoluteY){
    setLiveRectPosition(absoluteX, absoluteY);
    transposeToDesignCanvas();
    setDragHandlePositions();
}

void MaskFrame::setLiveRelativePosition(int absoluteX, int absoluteY){
    setLiveRectPosition(this->liveCanvas->getX() + absoluteX, this->liveCanvas->getY() + absoluteY);
    transposeToDesignCanvas();
    setDragHandlePositions();
}

void MaskFrame::setSelectedMaskPointPosition(int x, int y){
    int clampedX = clampInt(x, frameMargin, this->getWidth() - frameMargin);
    int clampedY = clampInt(y, frameMargin, this->getHeight() - frameMargin);
    selectedMaskPoint->setPosition(clampedX, clampedY);
    transposeToLiveCanvas();
}

void MaskFrame::setX(int absoluteX){
    this->setRectX(absoluteX);
    setDragHandlePositions();
    transposeToLiveCanvas();
}

void MaskFrame::setY(int absoluteY){
    this->setRectY(absoluteY);
    setDragHandlePositions();
    transposeToLiveCanvas();
}

int MaskFrame::getX(){
    return designCanvas->getX() + designPosition.x;
}

int MaskFrame::getY(){
    return designCanvas->getY() + designPosition.y;
}

int MaskFrame::getRelativeX(){
    return designPosition.x;
}

int MaskFrame::getRelativeY(){
    return designPosition.y;
}

int MaskFrame::getWidth(){
    return designWidth;
}

int MaskFrame::getHeight(){
    return designHeight;
}

int MaskFrame::getLiveX(){
    return liveCanvas->getX() + livePosition.x;
}

int MaskFrame::getLiveY(){
    return liveCanvas->getY() + livePosition.y;
}

int MaskFrame::getLiveRelativeX(){
    return livePosition.x;
}

int MaskFrame::getLiveRelativeY(){
    return livePosition.y;
}

int MaskFrame::getLiveWidth(){
    return liveWidth;
}

int MaskFrame::getLiveHeight(){
    return liveHeight;
}

int MaskFrame::getSmallestLegalWidth(Corner cornerBeingAdjusted){
    int result;
    if(cornerBeingAdjusted == TopRight || cornerBeingAdjusted == BottomRight){
        result = getWidestPointLeftToRight();
    }else if(cornerBeingAdjusted == TopLeft || cornerBeingAdjusted == BottomLeft){
        result = getWidestPointRightToLeft();
    }
    
    result += frameMargin;
    if(result < minimumFrameSize){
        return minimumFrameSize;
    }
    return result;
}

int MaskFrame::getSmallestLegalHeight(Corner cornerBeingAdjusted){
    int result;
    if(cornerBeingAdjusted == BottomLeft || cornerBeingAdjusted == BottomRight){
        result = getTallestPointTopToBottom();
    }else if(cornerBeingAdjusted == TopLeft || cornerBeingAdjusted == TopRight){
        result = getTallestPointBottomToTop();
    }
    
    result += frameMargin;
    if(result < minimumFrameSize){
        return minimumFrameSize;
    }
    return result;
}

void MaskFrame::addMaskPoint(int absoluteX, int absoluteY){
    if(maskPoints.size() < 3){
        int x = absoluteX - this->designCanvas->getX() - this->designPosition.x;
        int y = absoluteY - this->designCanvas->getY() - this->designPosition.y;
        MaskPoint maskPoint;
        maskPoint.setType(Real);
        maskPoint.setPosition(x, y);
        this->insert(&maskPoint);
    }else if(this->hasAGhostPoint){
        this->makeGhostPointReal();
    }
    transposeToLiveCanvas();
}

void MaskFrame::makeGhostPointReal(){
    MaskPoint maskPoint;
    maskPoint.setType(Real);
    maskPoint.setPosition(this->ghostPoint.getX(), this->ghostPoint.getY());
    maskPoint.setHighlighted(true);
    this->insert(&maskPoint);
    this->hasAGhostPoint = false;
    transposeToLiveCanvas();
}

void MaskFrame::deleteSelectedMaskPoint(){
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->isHighlighted()){
            maskPoints.deleteItem(i);
            break;
        }
    }
    transposeToLiveCanvas();
}

void MaskFrame::nudge(Direction direction){
    
    int newX, newY;
    newX = this->livePosition.x;
    newY = this->livePosition.y;
    
    if(direction == Left){
        newX--;
    }else if(direction == Up){
        newY--;
    }else if(direction == Right){
        newX++;
    }else if(direction == Down){
        newY++;
    }
    
    int innerBoundaryX = 0;
    int outerBoundaryX = this->liveCanvas->getWidth() - this->liveWidth;
    this->livePosition.x = clampInt(newX, innerBoundaryX, outerBoundaryX);
    
    int innerBoundaryY = 0;
    int outerBoundaryY = this->liveCanvas->getHeight() - this->liveHeight;
    this->livePosition.y = clampInt(newY, innerBoundaryY, outerBoundaryY);
    
    transposeToDesignCanvas();
}

void MaskFrame::nudgeDragHandle(Direction direction){
    
    int newWidth, newHeight;
    newWidth = this->liveWidth;
    newHeight = this->liveHeight;
    
    DragHandle *highlightedDragHandle = this->getHighlightedDragHandle();
    Corner corner = highlightedDragHandle->getCorner();
    
    if(corner == TopLeft){
        if(direction == Left){
            newWidth++;
        }else if(direction == Up){
            newHeight++;
        }else if(direction == Right){
            newWidth--;
        }else if(direction == Down){
            newHeight--;
        }
    }else if(corner == TopRight){
        if(direction == Left){
            newWidth--;
        }else if(direction == Up){
            newHeight++;
        }else if(direction == Right){
            newWidth++;
        }else if(direction == Down){
            newHeight--;
        }
    }else if(corner == BottomRight){
        if(direction == Left){
            newWidth--;
        }else if(direction == Up){
            newHeight--;
        }else if(direction == Right){
            newWidth++;
        }else if(direction == Down){
            newHeight++;
        }
    }else if(corner == BottomLeft){
        if(direction == Left){
            newWidth++;
        }else if(direction == Up){
            newHeight--;
        }else if(direction == Right){
            newWidth--;
        }else if(direction == Down){
            newHeight++;
        }
    }
    
    int smallestLegalWidth = this->getSmallestLegalLiveWidth(corner);
    int smallestLegalHeight = this->getSmallestLegalLiveHeight(corner);
    int newWidthClamped = clampInt(newWidth, smallestLegalWidth);
    int newHeightClamped = clampInt(newHeight, smallestLegalHeight);
    this->setLiveSize(newWidthClamped, newHeightClamped, corner);
}

void MaskFrame::nudgeMaskPoint(Direction direction){
    MaskPoint* highlightedMaskPoint = getHighlightedMaskPoint();
    if(highlightedMaskPoint > 0){
        
        int newX, newY;
        newX = highlightedMaskPoint->getLiveX();
        newY = highlightedMaskPoint->getLiveY();
        
        if(direction == Left){
            newX--;
        }else if(direction == Up){
            newY--;
        }else if(direction == Right){
            newX++;
        }else if(direction == Down){
            newY++;
        }
        
        newX = clampInt(newX, frameMargin, this->liveWidth - frameMargin);
        newY = clampInt(newY, frameMargin, this->liveHeight - frameMargin);
        
        highlightedMaskPoint->setLiveX(newX);
        highlightedMaskPoint->setLiveY(newY);
        transposeToDesignCanvas();
    }
}

Corner MaskFrame::highlightedCorner(){
    for(int i = 0; i < dragHandles.size(); i++){
        if(dragHandles[i]->isHighlighted()){
            return dragHandles[i]->getCorner();
        }
    }
    throw "Highlighted corner not found";
}

void MaskFrame::transposeToLiveCanvas(){
    int designCanvasWidth = this->designCanvas->getWidth();
    int designCanvasHeight = this->designCanvas->getHeight();
    int liveCanvasWidth = this->liveCanvas->getWidth();
    int liveCanvasHeight = this->liveCanvas->getHeight();
    
    this->livePosition.x = ceil(ofMap(this->designPosition.x, 0, designCanvasWidth, 0, liveCanvasWidth));
    this->livePosition.y = ceil(ofMap(this->designPosition.y, 0, designCanvasHeight, 0, liveCanvasHeight));
    
    this->liveWidth = ceil(ofMap(this->designWidth, 0, designCanvasWidth, 0, liveCanvasWidth));
    this->liveHeight = ceil(ofMap(this->designHeight, 0, designCanvasHeight, 0, liveCanvasHeight));
    
    for(int i = 0; i < maskPoints.size(); i++){
        int liveX = ceil(ofMap(maskPoints[i]->getX(), 0, designCanvasWidth, 0, liveCanvasWidth));
        int liveY = ceil(ofMap(maskPoints[i]->getY(), 0, designCanvasHeight, 0, liveCanvasHeight));
        maskPoints[i]->setLiveX(liveX);
        maskPoints[i]->setLiveY(liveY);
    }    
    
    if(this->hasGhostPoint()){
        int liveX = ceil(ofMap(ghostPoint.getX(), 0, designCanvasWidth, 0, liveCanvasWidth));
        int liveY = ceil(ofMap(ghostPoint.getY(), 0, designCanvasHeight, 0, liveCanvasHeight));
        ghostPoint.setLiveX(liveX);
        ghostPoint.setLiveY(liveY);
    }
}

void MaskFrame::transposeToDesignCanvas(){
    int designCanvasWidth = this->designCanvas->getWidth();
    int designCanvasHeight = this->designCanvas->getHeight();
    int liveCanvasWidth = this->liveCanvas->getWidth();
    int liveCanvasHeight = this->liveCanvas->getHeight();
    
    this->designPosition.x = floor(ofMap(this->livePosition.x, 0, liveCanvasWidth, 0, designCanvasWidth));
    this->designPosition.y = floor(ofMap(this->livePosition.y, 0, liveCanvasHeight, 0, designCanvasHeight));
    
    this->designWidth = floor(ofMap(this->liveWidth, 0, liveCanvasWidth, 0, designCanvasWidth));
    this->designHeight = floor(ofMap(this->liveHeight, 0, liveCanvasHeight, 0, designCanvasHeight));
    
    for(int i = 0; i < maskPoints.size(); i++){
        int designX = floor(ofMap(maskPoints[i]->getLiveX(), 0, liveCanvasWidth, 0, designCanvasWidth));
        int designY = floor(ofMap(maskPoints[i]->getLiveY(), 0, liveCanvasHeight, 0, designCanvasHeight));
        maskPoints[i]->setPosition(designX, designY);
    }
}

//Protected
void MaskFrame::prepareHomography() {
    input[0] = ofPoint(0, 0);
    input[1] = ofPoint(pattern->getWidth(), 0);
    input[2] = ofPoint(pattern->getWidth(), pattern->getHeight());
    input[3] = ofPoint(0, pattern->getHeight());
    for(int i = 0; i < 4; i++) {
        x = maskPoints[i]->getLiveX();
        y = maskPoints[i]->getLiveY();
        output[i] = ofPoint(x, y);
    }
}

void MaskFrame::findGhostPointIfCloseTo(int absoluteX, int absoluteY){
    int maskFrameX = absoluteX - this->getX();
    int maskFrameY = absoluteY - this->getY();
    this->hasAGhostPoint = false;
    for(int i = 0; i < maskPoints.size(); i++){
        int nextIndex = getNextIndex(i, maskPoints.size());
        this->hasAGhostPoint = getIntersection(maskFrameX, maskFrameY, maskPoints[i], maskPoints[nextIndex], &ghostPoint);
        if(this->hasAGhostPoint){
            ghostPointIndex = nextIndex;
            transposeToLiveCanvas();
            break;
        }
    }
}

void MaskFrame::highlightRectIfCloseTo(int absoluteX, int absoluteY){
    int canvasX = absoluteX - this->designCanvas->getX();
    int canvasY = absoluteY - this->designCanvas->getY();
    bool containsPosition = containsPositionInRect(canvasX, canvasY) || containsPositionInDragHandles(canvasX, canvasY);
    this->setHighlighted(containsPosition);
}

void MaskFrame::highlightDragHandlesIfCloseTo(int absoluteX, int absoluteY){
    int canvasX = absoluteX - this->designCanvas->getX();
    int canvasY = absoluteY - this->designCanvas->getY();
    for(int i = 0; i < dragHandles.size(); i++){
        bool isHighlighted = containsPosition(canvasX, canvasY, dragHandles[i]);
        dragHandles[i]->setHighlighted(isHighlighted);
    }
}

void MaskFrame::highlightMaskPointsIfCloseTo(int absoluteX, int absoluteY){
    int canvasX = absoluteX - this->designCanvas->getX();
    int canvasY = absoluteY - this->designCanvas->getY();
    for(int i = 0; i < maskPoints.size(); i++){
        bool isHighlighted = containsPosition(canvasX, canvasY, maskPoints[i]);
        maskPoints[i]->setHighlighted(isHighlighted);
    }
}

void MaskFrame::unhighlightAllDragHandles(){
    for(int i = 0; i < dragHandles.size(); i++){
        dragHandles[i]->setHighlighted(false);
    }
}

void MaskFrame::unhighlightAllMaskPoints(){
    for(int i = 0; i < maskPoints.size(); i++){
        maskPoints[i]->setHighlighted(false);
    }
}

void MaskFrame::selectHighlightedMaskPoint(){
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->isHighlighted()){
            selectedMaskPoint = maskPoints[i];
            return;
        }
    }
    throw "No highlighted mask point found to select";
}

void MaskFrame::deselectMaskPoint(){
    selectedMaskPoint = 0;
}

void MaskFrame::insert(MaskPoint *maskPoint){
    if(maskPoints.size() < 3){
        maskPoints.push_back(*maskPoint);        
    }else if(this->hasAGhostPoint){
        maskPoints.insert(ghostPointIndex, *maskPoint);
    }
}

bool MaskFrame::getIntersection(int maskFrameX, int maskFrameY, MaskPoint* maskPoint1, MaskPoint* maskPoint2, MaskPoint* intersection){
    
    ofPoint maskPointLineStart, maskPointLineEnd;
    maskPointLineStart.x = maskPoint1->getX();
    maskPointLineStart.y = maskPoint1->getY();
    maskPointLineEnd.x = maskPoint2->getX();
    maskPointLineEnd.y = maskPoint2->getY();
    
    ofPoint mouseCursorWithXMarginStart, mouseCursorWithXMarginEnd, xIntersection;
    mouseCursorWithXMarginStart.x = maskFrameX - round(cursorMargin / 2);
    mouseCursorWithXMarginStart.y = maskFrameY;
    mouseCursorWithXMarginEnd.x = mouseCursorWithXMarginStart.x + cursorMargin;
    mouseCursorWithXMarginEnd.y = maskFrameY;
    
    ofPoint mouseCursorWithYMarginStart, mouseCursorWithYMarginEnd, yIntersection;
    mouseCursorWithYMarginStart.x = maskFrameX;
    mouseCursorWithYMarginStart.y = maskFrameY - round(cursorMargin / 2);
    mouseCursorWithYMarginEnd.x = maskFrameX;
    mouseCursorWithYMarginEnd.y = mouseCursorWithYMarginStart.y + cursorMargin;
    
    bool xIntersects = ofLineSegmentIntersection(mouseCursorWithXMarginStart, mouseCursorWithXMarginEnd, maskPointLineStart, maskPointLineEnd, xIntersection);
    bool yIntersects = ofLineSegmentIntersection(mouseCursorWithYMarginStart, mouseCursorWithYMarginEnd, maskPointLineStart, maskPointLineEnd, yIntersection);
    
    if(xIntersects){
        intersection->setPosition(xIntersection.x, xIntersection.y);
    }else if(yIntersects){
        intersection->setPosition(yIntersection.x, yIntersection.y);
    }
    return xIntersects || yIntersects;
}

void MaskFrame::initialiseDragHandles(){
    DragHandle topLeft, topRight, bottomRight, bottomLeft;
    
    topLeft.setCorner(TopLeft);
    topRight.setCorner(TopRight);
    bottomRight.setCorner(BottomRight);
    bottomLeft.setCorner(BottomLeft);
    
    dragHandles.push_back(topLeft);
    dragHandles.push_back(topRight);
    dragHandles.push_back(bottomRight);
    dragHandles.push_back(bottomLeft);
}

void MaskFrame::respondToStateChange(){
    if(transformState == Masking){
        this->selectHighlightedMaskPoint();
    }else{
        this->deselectMaskPoint();
    }
    if(transformState == NoTransform){
        this->highlighted = false;
        this->unhighlightAllDragHandles();
    }
}

bool MaskFrame::containsPositionInRect(int canvasX, int canvasY){
    return(
           canvasX > this->designPosition.x && 
           canvasY > this->designPosition.y && 
           canvasX < (this->designPosition.x + this->designWidth) &&
           canvasY < (this->designPosition.y + this->designHeight));
}

bool MaskFrame::containsPositionInDragHandles(int canvasX, int canvasY){
    for(int i = 0; i < dragHandles.size(); i++){
        if(containsPosition(canvasX, canvasY, dragHandles[i])){
            return true;
        }
    }
    return false;
}

bool MaskFrame::containsPosition(int canvasX, int canvasY, PointObject* pointObject){
    int maskFrameX = canvasX - this->designPosition.x;
    int maskFrameY = canvasY - this->designPosition.y;
    int pointObjectX = pointObject->getX();
    int pointObjectY = pointObject->getY();
    int pointObjectRadius = pointObject->getRadius();
    
    if(abs(ofDist(maskFrameX, maskFrameY, pointObjectX, pointObjectY)) < pointObjectRadius){
        return true;
    }
    return false;
}

void MaskFrame::setRectPosition(int absoluteX, int absoluteY){
    setRectX(absoluteX);
    setRectY(absoluteY);
}

void MaskFrame::setLiveRectPosition(int absoluteX, int absoluteY){
    setLiveRectX(absoluteX);
    setLiveRectY(absoluteY);
}

void MaskFrame::setRectX(int absoluteX){
    int canvasX = absoluteX - this->designCanvas->getX();
    int innerBoundaryX = 0;
    int outerBoundaryX = this->designCanvas->getWidth() - this->designWidth;
    this->designPosition.x = clampInt(canvasX, innerBoundaryX, outerBoundaryX);
}

void MaskFrame::setRectY(int absoluteY){
    int canvasY = absoluteY - this->designCanvas->getY();
    int innerBoundaryY = 0;
    int outerBoundaryY = this->designCanvas->getHeight() - this->designHeight;
    this->designPosition.y = clampInt(canvasY, innerBoundaryY, outerBoundaryY);
}

void MaskFrame::setLiveRectX(int absoluteX){
    int canvasX = absoluteX - this->liveCanvas->getX();
    int innerBoundaryX = 0;
    int outerBoundaryX = this->liveCanvas->getWidth() - this->liveWidth;
    this->livePosition.x = clampInt(canvasX, innerBoundaryX, outerBoundaryX);
}

void MaskFrame::setLiveRectY(int absoluteY){
    int canvasY = absoluteY - this->liveCanvas->getY();
    int innerBoundaryY = 0;
    int outerBoundaryY = this->liveCanvas->getHeight() - this->liveHeight;
    this->livePosition.y = clampInt(canvasY, innerBoundaryY, outerBoundaryY);
}

void MaskFrame::setDragHandlePositions(){
    for(int i = 0; i < dragHandles.size(); i++){
        Corner corner = dragHandles[i]->getCorner();
        if(corner == TopLeft){
            dragHandles[i]->setPosition(0, 0);
            dragHandles[i]->setLivePosition(0, 0);
        }else if(corner == TopRight){
            dragHandles[i]->setPosition(this->designWidth, 0);
            dragHandles[i]->setLivePosition(this->liveWidth, 0);
        }else if(corner == BottomRight){
            dragHandles[i]->setPosition(this->designWidth, this->designHeight);
            dragHandles[i]->setLivePosition(this->liveWidth, this->liveHeight);
        }else if(corner == BottomLeft){
            dragHandles[i]->setPosition(0, this->designHeight);
            dragHandles[i]->setLivePosition(0, this->liveHeight);
        }
    }
}

/* Design */
void MaskFrame::setPositionsToMatchScaleChange(int width, int height, Corner movingCorner){
    if(movingCorner == BottomLeft){
        this->setXPositionsToMatchScaleChange(width);
        
    }else if(movingCorner == TopLeft){
        this->setXPositionsToMatchScaleChange(width);
        this->setYPositionsToMatchScaleChange(height);
        
    }else if(movingCorner == TopRight){
        this->setYPositionsToMatchScaleChange(height);
    }
}

void MaskFrame::setXPositionsToMatchScaleChange(int width){
    int oldX = this->getX();
    int oldWidth = this->getWidth();
    int difference = width - oldWidth;
    this->setX(oldX - difference);
    this->translateMaskPointsX(difference);
}

void MaskFrame::setYPositionsToMatchScaleChange(int height){
    int oldY = this->getY();
    int oldHeight = this->getHeight();
    int difference = height - oldHeight;
    this->setY(oldY - difference);
    this->translateMaskPointsY(difference);
}

void MaskFrame::translateMaskPointsX(int amount){
    for(int i = 0; i < maskPoints.size(); i++){
        int liveAmount = ofMap(amount, 0, this->designCanvas->getWidth(), 0, this->liveCanvas->getWidth());
        int newX = maskPoints[i]->getX() + amount;
        int newLiveX = maskPoints[i]->getLiveX() + liveAmount;
        maskPoints[i]->setX(newX);
        maskPoints[i]->setLiveX(newLiveX);
    }
}

void MaskFrame::translateMaskPointsY(int amount){
    for(int i = 0; i < maskPoints.size(); i++){
        int liveAmount = ofMap(amount, 0, this->designCanvas->getHeight(), 0, this->liveCanvas->getHeight());
        int newY = maskPoints[i]->getY() + amount;
        int newLiveY = maskPoints[i]->getLiveY() + liveAmount;
        maskPoints[i]->setY(newY);
        maskPoints[i]->setLiveY(newLiveY);
    }
}

int MaskFrame::getWidestPointLeftToRight(){
    int widestPointFound = 0;
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getX() > widestPointFound){
            widestPointFound = maskPoints[i]->getX();
        }
    }
    return widestPointFound;
}

int MaskFrame::getWidestPointRightToLeft(){
    int widestPointFound = this->getWidth();
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getX() < widestPointFound){
            widestPointFound = maskPoints[i]->getX();
        }
    }
    return this->getWidth() - widestPointFound;
}

int MaskFrame::getTallestPointTopToBottom(){
    int tallestPointFound = 0;
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getY() > tallestPointFound){
            tallestPointFound = maskPoints[i]->getY();
        }
    }
    return tallestPointFound;
}

int MaskFrame::getTallestPointBottomToTop(){
    int tallestPointFound = this->getHeight();
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getY() < tallestPointFound){
            tallestPointFound = maskPoints[i]->getY();
        }
    }
    return this->getHeight() - tallestPointFound;
}

/* Live */
void MaskFrame::setLivePositionsToMatchScaleChange(int width, int height, Corner movingCorner){
    if(movingCorner == BottomLeft){
        this->setLiveXPositionsToMatchScaleChange(width);
        
    }else if(movingCorner == TopLeft){
        this->setLiveXPositionsToMatchScaleChange(width);
        this->setLiveYPositionsToMatchScaleChange(height);
        
    }else if(movingCorner == TopRight){
        this->setLiveYPositionsToMatchScaleChange(height);
    }
}

void MaskFrame::setLiveXPositionsToMatchScaleChange(int width){
    int oldX = this->livePosition.x;
    int oldWidth = this->liveWidth;
    int difference = width - oldWidth;
    this->livePosition.x = oldX - difference;
    this->translateMaskPointsLiveX(difference);
}

void MaskFrame::setLiveYPositionsToMatchScaleChange(int height){
    int oldY = this->livePosition.y;
    int oldHeight = this->liveHeight;
    int difference = height - oldHeight;
    this->livePosition.y = oldY - difference;
    this->translateMaskPointsLiveY(difference);
}

void MaskFrame::translateMaskPointsLiveX(int amount){
    for(int i = 0; i < maskPoints.size(); i++){
        int designAmount = ofMap(amount, 0, this->liveCanvas->getWidth(), 0, this->designCanvas->getWidth());
        int newX = maskPoints[i]->getLiveX() + amount;
        int newDesignX = maskPoints[i]->getX() + designAmount;
        maskPoints[i]->setLiveX(newX);
        maskPoints[i]->setX(newDesignX);
    }
}

void MaskFrame::translateMaskPointsLiveY(int amount){
    for(int i = 0; i < maskPoints.size(); i++){
        int designAmount = ofMap(amount, 0, this->liveCanvas->getHeight(), 0, this->designCanvas->getHeight());
        int newY = maskPoints[i]->getLiveY() + amount;
        int newDesignY = maskPoints[i]->getY() + designAmount;
        maskPoints[i]->setLiveY(newY);
        maskPoints[i]->setY(newDesignY);
    }
}

int MaskFrame::getSmallestLegalLiveWidth(Corner cornerBeingAdjusted){
    int result;
    if(cornerBeingAdjusted == TopRight || cornerBeingAdjusted == BottomRight){
        result = getWidestLivePointLeftToRight();
    }else if(cornerBeingAdjusted == TopLeft || cornerBeingAdjusted == BottomLeft){
        result = getWidestLivePointRightToLeft();
    }
    
    result += frameMargin;
    if(result < minimumFrameSize){
        return minimumFrameSize;
    }
    return result;
}

int MaskFrame::getSmallestLegalLiveHeight(Corner cornerBeingAdjusted){
    int result;
    if(cornerBeingAdjusted == BottomLeft || cornerBeingAdjusted == BottomRight){
        result = getTallestLivePointTopToBottom();
    }else if(cornerBeingAdjusted == TopLeft || cornerBeingAdjusted == TopRight){
        result = getTallestLivePointBottomToTop();
    }
    
    result += frameMargin;
    if(result < minimumFrameSize){
        return minimumFrameSize;
    }
    return result;
}

int MaskFrame::getWidestLivePointLeftToRight(){
    int widestPointFound = 0;
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getLiveX() > widestPointFound){
            widestPointFound = maskPoints[i]->getLiveX();
        }
    }
    return widestPointFound;
}

int MaskFrame::getWidestLivePointRightToLeft(){
    int widestPointFound = this->liveWidth;
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getLiveX() < widestPointFound){
            widestPointFound = maskPoints[i]->getLiveX();
        }
    }
    return this->liveWidth - widestPointFound;
}

int MaskFrame::getTallestLivePointTopToBottom(){
    int tallestPointFound = 0;
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getLiveY() > tallestPointFound){
            tallestPointFound = maskPoints[i]->getLiveY();
        }
    }
    return tallestPointFound;
}

int MaskFrame::getTallestLivePointBottomToTop(){
    int tallestPointFound = this->liveHeight;
    for(int i = 0; i < maskPoints.size(); i++){
        if(maskPoints[i]->getLiveY() < tallestPointFound){
            tallestPointFound = maskPoints[i]->getLiveY();
        }
    }
    return this->liveHeight - tallestPointFound;
}