#include "ObjectStore.h"

//Public
void ObjectStore::add(MaskFrame *maskFrame){
    maskFrames.backup();
    maskFrames.push_back(*maskFrame);
    assignMaskFrameIds();
}

void ObjectStore::nudge(Direction direction){
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

void ObjectStore::erase(){
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

void ObjectStore::createMaskPointAt(int x, int y){
    MaskFrame* highlightedMaskFrame = this->getHighlightedMaskFrame();
    if(highlightedMaskFrame != 0){
        maskFrames.backup();
        highlightedMaskFrame->addMaskPoint(x, y);
    }   
}

void ObjectStore::updateHighlights(int x, int y){
    this->unhighlightAllMaskFrames();
    
    for (int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->highlightIfCloseTo(x, y);
        
        if(maskFrames[i]->isHighlighted() || maskFrames[i]->hasHighlightedDragHandle()){
            lastHighlightedMaskFrame = maskFrames[i];
            break;
        }
    }
}

void ObjectStore::toggleFrameNudge(){
    frameNudge = !frameNudge;
}

MaskFrame* ObjectStore::beginTransform(){
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

void ObjectStore::endTransform(){
    for(int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->setTransformState(NoTransform);
    }
}

void ObjectStore::undo(){
    maskFrames.undo();
}

void ObjectStore::redo(){
    maskFrames.redo();
}

bool ObjectStore::getFrameNudgeEnabled(){
    return frameNudge;
}

void ObjectStore::drawDesign(){
    for (int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->drawDesign();
    }
}
	
void ObjectStore::drawLive(Mode mode){
    for (int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->drawLive(mode);
    }
}

SafeDeque<MaskFrame> *ObjectStore::getMaskFrames(){
    return &this->maskFrames;
}

//Protected
void ObjectStore::unhighlightAllMaskFrames(){
    for(int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->setHighlighted(false);
    }
}

int ObjectStore::getHighlightedMaskFrameIndex(){
    for(int i = 0; i < maskFrames.size(); i++){
        if(maskFrames[i]->isHighlighted()){
            return i;
        }
    }
    return -1;
}

MaskFrame* ObjectStore::getHighlightedMaskFrame(){
    int i = getHighlightedMaskFrameIndex();
    if(i > -1){
        return maskFrames[i];
    }
    return 0;
}

bool ObjectStore::hasHighlightedMaskFrame(){
    int i = getHighlightedMaskFrameIndex();
    return i > -1;
}

int ObjectStore::assignMaskFrameIds(){
    for(int i = 0; i < maskFrames.size(); i++){
        maskFrames[i]->setId(i);
    }
}