#include "CanvasContents.h"

//Public
void CanvasContents::add(MaskFrame *maskFrame){
    maskFrames.backup();
    maskFrames.push_back(*maskFrame);
    assignMaskFrameIds();
}

void CanvasContents::nudge(Direction direction){
    if(this->hasHighlightedMaskFrame()){
        maskFrames.backup();
        MaskFrame* maskFrame = this->getHighlightedMaskFrame();

        if(maskFrame->hasHighlightedMaskPoint()){
            maskFrame->nudgeMaskPoint(direction);
        }else if(frameNudge){
            maskFrame->nudge(direction);
        }
    }else{
        for(int i = 0; i < maskFrames.size(); i++){
            if(maskFrames[i]->hasHighlightedDragHandle()){
                maskFrames[i]->nudgeDragHandle(direction);
                break;
            }
        }
    }
}

void CanvasContents::erase(){
    int i = getHighlightedMaskFrameIndex();
    if(i > -1){
        if(maskFrames[i]->hasHighlightedMaskPoint()){
            maskFrames.backup();
            maskFrames[i]->deleteSelectedMaskPoint();
        }else{
            maskFrames.backup();
            maskFrames.deleteItem(i);
        }
    }
}

void CanvasContents::createMaskPointAt(int x, int y){
    MaskFrame* highlightedMaskFrame = this->getHighlightedMaskFrame();
    if(highlightedMaskFrame != 0){
        maskFrames.backup();
        highlightedMaskFrame->addMaskPoint(x, y);
    }   
}

void CanvasContents::updateHighlights(int x, int y){
    this->unhighlightAllMaskFrames();
    
    for (int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->highlightIfCloseTo(x, y);
        
        if(maskFrames[i]->isHighlighted() || maskFrames[i]->hasHighlightedDragHandle()){
            lastHighlightedMaskFrame = maskFrames[i];
            break;
        }
    }
}

void CanvasContents::toggleFrameNudge(){
    frameNudge = !frameNudge;
}

MaskFrame* CanvasContents::beginTransform(){
    for(int i = 0; i < maskFrames.size(); i++){
        if(maskFrames[i]->hasHighlightedDragHandle()){
            maskFrames[i]->setTransformState(Scaling);
            maskFrames.backup();
            return maskFrames.getPointer(i);
        }
        if(maskFrames[i]->isHighlighted()){
            if(maskFrames[i]->hasGhostPoint()){
                maskFrames[i]->makeGhostPointReal();
                maskFrames[i]->setTransformState(Masking);
            }else if(maskFrames[i]->hasHighlightedMaskPoint()){
                maskFrames[i]->setTransformState(Masking);
            }else{
                maskFrames[i]->setTransformState(Translating);
            }
            maskFrames.backup();
            return maskFrames.getPointer(i);
        }
    }
    return 0;
}

void CanvasContents::endTransform(){
    for(int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->setTransformState(NoTransform);
    }
}

void CanvasContents::undo(){
    maskFrames.undo();
}

void CanvasContents::redo(){
    maskFrames.redo();
}

bool CanvasContents::getFrameNudgeEnabled(){
    return frameNudge;
}

void CanvasContents::drawDesign(){
    for (int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->drawDesign();
    }
}
	
void CanvasContents::drawLive(Mode mode){
    for (int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->drawLive(mode);
    }
}

SafeDeque<MaskFrame> *CanvasContents::getMaskFrames(){
    return &this->maskFrames;
}

//Protected
void CanvasContents::unhighlightAllMaskFrames(){
    for(int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->setHighlighted(false);
    }
}

int CanvasContents::getHighlightedMaskFrameIndex(){
    for(int i = 0; i < maskFrames.size(); i++){
        if(maskFrames[i]->isHighlighted()){
            return i;
        }
    }
    return -1;
}

MaskFrame* CanvasContents::getHighlightedMaskFrame(){
    int i = getHighlightedMaskFrameIndex();
    if(i > -1){
        return maskFrames[i];
    }
    return 0;
}

bool CanvasContents::hasHighlightedMaskFrame(){
    int i = getHighlightedMaskFrameIndex();
    return i > -1;
}

int CanvasContents::assignMaskFrameIds(){
    for(int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->setId(i);
    }
}