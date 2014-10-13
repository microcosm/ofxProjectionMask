#include "ofxProjectionMapper.h"

const string designModeText = "Design";
const string designLiveModeText = "Design / Live";
const string liveModeText = "Live";
const string previewTagText = "Buffer preview";

const int bufferStartFrameNum = 120;

const int mouseXAdjustment = -1;
const int mouseYAdjustment = -2;

//Public
void ofxProjectionMapper::setup(BufferPattern* _pattern){
    
    pattern = _pattern;
    displayMode = Design;
    
    ofSetHexColor(0xFFFFFF);
	ofBackground(0, 0, 0);
    ofSetWindowPosition(0, 0);
    ofSetWindowShape(presets.windowWidth, presets.windowHeight);
    ofEnableAlphaBlending();
    
    designCanvas.setPosition(presets.designCanvasX, presets.designCanvasY);
    designCanvas.setSize(presets.designCanvasWidth, presets.designCanvasHeight);
    designCanvas.setNumGridLines(presets.numGridLinesX, presets.numGridLinesY);
    
    liveCanvas.setPosition(presets.liveCanvasX, presets.liveCanvasY);
    liveCanvas.setSize(presets.liveCanvasWidth, presets.liveCanvasHeight);
    liveCanvas.setNumGridLines(presets.numGridLinesX, presets.numGridLinesY);
    
    textArea.setInstructionsPosition(presets.instructionsX, presets.instructionsY);
    textArea.setPlaybackVolumePosition(presets.playbackVolumeX, presets.playbackVolumeY);
    textArea.setNonPlaybackVolumesPosition(presets.nonPlaybackVolumeX, presets.nonPlaybackVolumeY);
    textArea.setNumberBoxSize(presets.numberBoxWidth, presets.numberBoxHeight);
    textArea.setOffsets(presets.numberTagOffsetX, presets.numberTagOffsetY);
    textArea.setMargins(presets.numberTagMargin, presets.numberBoxMargin);
    
    ofSetFullscreen(presets.startFullscreen);
    selectedMaskFrame = 0;
    xml.setup(&designCanvas, &liveCanvas, &canvasContents, pattern->getBuffers());
    xml.load();
}

void ofxProjectionMapper::update(int mouseX, int mouseY){
    
    mouse.x = mouseX + mouseXAdjustment;
    mouse.y = mouseY + mouseYAdjustment;
    
    if(!isTransforming()){
        canvasContents.updateHighlights(mouseX, mouseY);
    }
    
    if(displayMode == Design){
        textArea.setRenderMode(designModeText);
    }else if(displayMode == HalfLive){
        textArea.setRenderMode(designLiveModeText);
    }else if(displayMode == Live){
        textArea.setRenderMode(liveModeText);
    }
}

void ofxProjectionMapper::draw(){
    
    drawBufferPreviews();
    
    ofPushMatrix();
    ofTranslate(designCanvas.getX(), designCanvas.getY());
    designCanvas.draw();
    canvasContents.drawDesign();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(liveCanvas.getX(), liveCanvas.getY());
    if(displayMode == Design){
        liveCanvas.draw();
    }
    canvasContents.drawLive(displayMode);
    ofPopMatrix();
    
    textArea.draw();
    
    drawLiveCursor();
}

void ofxProjectionMapper::keyReleased(int key){
    if(key == 'f' || key == 'F'){
        createNewMaskFrame();
        xml.autoSave();
    }else if(key == 'p' || key == 'P'){
        createNewMaskPoint();
        xml.autoSave();
    }else if (key == ' '){
        ofToggleFullscreen();
    }else if(key == 'u' || key == 'U'){
        undo();
    }else if(key == 'r' || key == 'R'){
        redo();
    }else if(key == 127 || key == 8){
        deleteHighlightedItem();
        xml.autoSave();
    }else if(key == 356){
        nudge(Left);
        xml.autoSave();
    }else if(key == 357){
        nudge(Up);
        xml.autoSave();
    }else if(key == 358){
        nudge(Right);
        xml.autoSave();
    }else if(key == 359){
        nudge(Down);
        xml.autoSave();
    }else if(key == 's' || key == 'S'){
        xml.save();
    }else if(key == 'l' || key == 'L'){
        xml.load();
    }else if(key == 'm' || key == 'M'){
        cycleMode();
    }else if(key == 'e' || key == 'E'){
        toggleFrameNudge();
    }
}

void ofxProjectionMapper::mouseDragged(){
    if(selectedMaskFrame != 0){
        TransformState transformState = selectedMaskFrame->getTransformState();
        if(transformState == Translating){
            selectedMaskFrame->setPosition(mouse.x - mouseOffset.x, mouse.y - mouseOffset.y);
        }else if(transformState == Scaling){
            scaleSelectedMaskFrame();
        }else if(transformState == Masking){
            selectedMaskFrame->setSelectedMaskPointPosition(mouse.x - mouseOffset.x, mouse.y - mouseOffset.y);
        }
    }
}

void ofxProjectionMapper::mousePressed(){
    selectedMaskFrame = canvasContents.beginTransform();
    if(selectedMaskFrame != 0){
        setMouseOffsetFromSelectedMaskFrame();
    }
}

void ofxProjectionMapper::mouseReleased(){
    selectedMaskFrame = 0;
    canvasContents.endTransform();
    xml.autoSave();
}

void ofxProjectionMapper::setVolumes(float *playbackVolume, vector<float> *nonPlaybackVolumes){
    textArea.setVolumes(playbackVolume, nonPlaybackVolumes);
}

//Protected
void ofxProjectionMapper::undo(){
    canvasContents.undo();
}

void ofxProjectionMapper::redo(){
    canvasContents.redo();
}

void ofxProjectionMapper::nudge(Direction direction){
    canvasContents.nudge(direction);
}

void ofxProjectionMapper::toggleFrameNudge(){
    canvasContents.toggleFrameNudge();
    textArea.setFrameNudgeEnabled(canvasContents.getFrameNudgeEnabled());
}

void ofxProjectionMapper::createNewMaskFrame(){
    MaskFrame maskFrame;
    maskFrame.assignCanvases(designCanvas, liveCanvas);
    maskFrame.setBuffers(pattern->getBuffers());
    maskFrame.setSize(presets.newMaskFrameWidth, presets.newMaskFrameHeight);
    maskFrame.setPosition(mouse.x, mouse.y);
    canvasContents.add(&maskFrame);
}

void ofxProjectionMapper::createNewMaskPoint(){
    canvasContents.createMaskPointAt(mouse.x, mouse.y);
}

void ofxProjectionMapper::deleteHighlightedItem(){
    canvasContents.erase();
}

void ofxProjectionMapper::cycleMode(){
    if(displayMode == Design){
        displayMode = HalfLive;
    }else if(displayMode == HalfLive){
        displayMode = Live;
    }else if(displayMode == Live){
        displayMode = Design;
    }
}

bool ofxProjectionMapper::mouseIsOverDesignCanvas(){
    return mouse.x > this->designCanvas.getX() && mouse.x < (this->designCanvas.getX() + this->designCanvas.getWidth())
    && mouse.y > this->designCanvas.getY() && mouse.y < (this->designCanvas.getY() + this->designCanvas.getHeight());
}

void ofxProjectionMapper::drawLiveCursor(){
    if(mouseIsOverDesignCanvas() && displayMode != Live){
        int liveMouseX = ofMap(mouse.x, designCanvas.getX(), designCanvas.getX() + designCanvas.getWidth(), liveCanvas.getX(), liveCanvas.getX() + liveCanvas.getWidth());
        int liveMouseY = ofMap(mouse.y, designCanvas.getY(), designCanvas.getY() + designCanvas.getHeight(), liveCanvas.getY(), liveCanvas.getY() + liveCanvas.getHeight());
        
        ofLine(liveMouseX - 5, liveMouseY - 5, liveMouseX + 5, liveMouseY + 5);
        ofLine(liveMouseX + 5, liveMouseY - 5, liveMouseX - 5, liveMouseY + 5);
    }
}

void ofxProjectionMapper::drawBufferPreviews(){
    ofPushMatrix();
    ofTranslate(presets.bufferPreviewX, presets.bufferPreviewY);
    
    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    
    int x = 0, y = 0, count = 0;
    vector<ofFbo>* buffers = pattern->getBuffers();
    
    for(int i = 0; i < buffers->size(); i++){
        ofTranslate(x, y);
        if(i > 0 && i % presets.stackAfter == 0){
            ofPopMatrix();
            ofPushMatrix();
            count++;
            ofTranslate(presets.bufferPreviewX + ((presets.bufferPreviewWidth + presets.bufferMargin) * count), presets.bufferPreviewY);
        }
        y = presets.bufferPreviewHeight + (presets.bufferMargin * 2);
        if(ofGetFrameNum() > bufferStartFrameNum){
            buffers->at(i).draw(0, 0, presets.bufferPreviewWidth, presets.bufferPreviewHeight);
        }
        ofRect(0, 0, presets.bufferPreviewWidth, presets.bufferPreviewHeight);
        ofDrawBitmapString("Buffer " + ofToString(i + 1), 0, presets.bufferPreviewHeight + presets.bufferMargin);
    }
    
    ofPopMatrix();
}

bool ofxProjectionMapper::isTransforming(){
    return selectedMaskFrame != 0 && selectedMaskFrame->getTransformState() != NoTransform;
}

void ofxProjectionMapper::scaleSelectedMaskFrame(){
    int mouseXConstrained = clampInt(mouse.x, designCanvas.getX() + mouseOffset.x, designCanvas.getX() + designCanvas.getWidth() + mouseOffset.x);
    int mouseYConstrained = clampInt(mouse.y, designCanvas.getY() + mouseOffset.y, designCanvas.getY() + designCanvas.getHeight() + mouseOffset.y);
    int newWidth, newHeight;
    
    if(selectedCorner == TopLeft){
        
        newWidth = (selectedMaskFrame->getX() + selectedMaskFrame->getWidth() + mouseOffset.x) - mouseXConstrained;
        newHeight = (selectedMaskFrame->getY() + selectedMaskFrame->getHeight() + mouseOffset.y) - mouseYConstrained;
        
    }else if(selectedCorner == TopRight){
        
        newWidth = mouseXConstrained - (selectedMaskFrame->getX() + mouseOffset.x);
        newHeight = (selectedMaskFrame->getY() + selectedMaskFrame->getHeight() + mouseOffset.y) - mouseYConstrained;
        
    }else if(selectedCorner == BottomRight){
        
        newWidth = mouseXConstrained - (selectedMaskFrame->getX() + mouseOffset.x);
        newHeight = mouseYConstrained - (selectedMaskFrame->getY() + mouseOffset.y);
        
    }else if(selectedCorner == BottomLeft){
        
        newWidth = (selectedMaskFrame->getX() + selectedMaskFrame->getWidth() + mouseOffset.x) - mouseXConstrained;
        newHeight = mouseYConstrained - (selectedMaskFrame->getY() + mouseOffset.y);
    }
    
    int smallestLegalWidth = selectedMaskFrame->getSmallestLegalWidth(selectedCorner);
    int smallestLegalHeight = selectedMaskFrame->getSmallestLegalHeight(selectedCorner);
    int newWidthClamped = clampInt(newWidth, smallestLegalWidth);
    int newHeightClamped = clampInt(newHeight, smallestLegalHeight);
    selectedMaskFrame->setSize(newWidthClamped, newHeightClamped, selectedCorner);
}

void ofxProjectionMapper::setMouseOffsetFromSelectedMaskFrame(){
    TransformState transformState = selectedMaskFrame->getTransformState();
    if(transformState == Translating){
        setMouseOffsetFromTopLeftCorner();
    }else if(transformState == Scaling){
        setMouseOffsetFromSelectedCorner();
    }else if(transformState == Masking){
        setMouseOffsetFromSelectedMaskPoint();
    }
}

void ofxProjectionMapper::setMouseOffsetFromSelectedMaskPoint(){
    mouseOffset.x = mouse.x - selectedMaskFrame->getSelectedMaskPointX();
    mouseOffset.y = mouse.y - selectedMaskFrame->getSelectedMaskPointY();
}

void ofxProjectionMapper::setMouseOffsetFromSelectedCorner(){
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

void ofxProjectionMapper::setMouseOffsetFromTopLeftCorner(){
    mouseOffset.x = mouse.x - selectedMaskFrame->getX();
    mouseOffset.y = mouse.y - selectedMaskFrame->getY();
}

void ofxProjectionMapper::setMouseOffsetFromTopRightCorner(){
    mouseOffset.x = mouse.x - selectedMaskFrame->getX() - selectedMaskFrame->getWidth();
    mouseOffset.y = mouse.y - selectedMaskFrame->getY();
}

void ofxProjectionMapper::setMouseOffsetFromBottomRightCorner(){
    mouseOffset.x = mouse.x - selectedMaskFrame->getX() - selectedMaskFrame->getWidth();
    mouseOffset.y = mouse.y - selectedMaskFrame->getY() - selectedMaskFrame->getHeight();
}

void ofxProjectionMapper::setMouseOffsetFromBottomLeftCorner(){
    mouseOffset.x = mouse.x - selectedMaskFrame->getX();
    mouseOffset.y = mouse.y - selectedMaskFrame->getY() - selectedMaskFrame->getHeight();
}