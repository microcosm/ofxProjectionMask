#include "ofxProjectionMask.h"

//Public
void ofxProjectionMask::setup(StretchMode _stretchMode, PresetMode presetMode){
    presets.setMode(presetMode);
    displayMode = Design;
    
    ofSetHexColor(0xFFFFFF);
    ofBackground(0, 0, 0);
    ofSetWindowPosition(0, 0);
    ofSetWindowShape(presets.firstWindowWidth, presets.firstWindowHeight);
    ofEnableAlphaBlending();
    
    layout();
    
    selectedMaskFrame = 0;
    stretchMode = _stretchMode;
    
    xml.setup(&designCanvas, &liveCanvas, &canvasContents, &patterns, presets.storageDirectory);
    if(patterns.size() > 0) {
        xml.load();
    }
    mouse.setup(&designCanvas);

    background.setup(presets.liveCanvasWidth, presets.liveCanvasHeight, 1);

    ofAddListener(ofEvents().keyReleased, this, &ofxProjectionMask::keyReleased);
    ofAddListener(ofEvents().draw, this, &ofxProjectionMask::draw);
    ofAddListener(ofEvents().mouseDragged, this, &ofxProjectionMask::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &ofxProjectionMask::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxProjectionMask::mouseReleased);
}

void ofxProjectionMask::setStorageFileName(string fileName){
    xml.setFileName(fileName);
}

ofxLayerMask* ofxProjectionMask::newPattern(int width, int height){

    patterns.push_back(new ofxLayerMask);
    patterns.back()->setup(width, height, 1);
    xml.load();
    return patterns.back();
}

void ofxProjectionMask::layout() {
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
}

void ofxProjectionMask::update(int mouseX, int mouseY){
    
    mouse.set(mouseX, mouseY);
    
    if(!isTransforming()){
        canvasContents.updateHighlights(mouseX, mouseY);
    }
    
    textArea.setDisplayMode(displayMode);
    textArea.setPresetMode(presets.getMode());
}

void ofxProjectionMask::draw(ofEventArgs& args){
    ofPushStyle();
    {
        ofSetLineWidth(1);
        ofBackground(ofColor::black);
        drawBufferPreviews();
        
        ofPushMatrix();
        ofTranslate(designCanvas.getX(), designCanvas.getY());
        drawBackground(designCanvas.getWidth(), designCanvas.getHeight(), 150);
        designCanvas.draw();
        canvasContents.drawDesign();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(presets.designCanvasLabelX, presets.designCanvasLabelY);
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Design Canvas", ofPoint(0, 0));
        ofPopMatrix();
        
        textArea.draw();
    }
    ofPopStyle();
}

void ofxProjectionMask::drawProductionWindow(){
    ofPushMatrix();
    ofTranslate(liveCanvas.getX(), liveCanvas.getY());
    if(displayMode == Design){
        liveCanvas.draw();
    }
    canvasContents.drawLive(displayMode, stretchMode);
    ofPopMatrix();
    drawLiveCursor();
}

void ofxProjectionMask::drawBackground(int width, int height, int alpha){
    if(background.numLayers() > 0){
        background.draw(0, 0, width, height);
        ofSetColor(ofColor::black, 255 - alpha);
        ofFill();
        ofDrawRectangle(0, 0, width, height);
        ofSetColor(ofColor::white);
        ofNoFill();
    }
}

void ofxProjectionMask::keyReleased(ofKeyEventArgs& args){
    if(args.key == 'f' || args.key == 'F'){
        createNewMaskFrame();
        xml.autoSave();
    }else if(args.key == 'p' || args.key == 'P'){
        createNewMaskPoint();
        xml.autoSave();
    }else if (args.key == ' '){
        ofToggleFullscreen();
    }else if(args.key == 'u' || args.key == 'U'){
        undo();
    }else if(args.key == 'r' || args.key == 'R'){
        redo();
    }else if(args.key == 127 || args.key == 8){
        deleteHighlightedItem();
        xml.autoSave();
        xml.load();
    }else if(args.key == OF_KEY_LEFT){
        nudge(Left);
        xml.autoSave();
    }else if(args.key == OF_KEY_UP){
        nudge(Up);
        xml.autoSave();
    }else if(args.key == OF_KEY_RIGHT){
        nudge(Right);
        xml.autoSave();
    }else if(args.key == OF_KEY_DOWN){
        nudge(Down);
        xml.autoSave();
    }else if(args.key == 's' || args.key == 'S'){
        xml.save();
    }else if(args.key == 'l' || args.key == 'L'){
        xml.load();
    }else if(args.key == 'm' || args.key == 'M'){
        cycleMode();
    }else if(args.key == 'n' || args.key == 'N'){
        toggleFrameNudge();
    }
}

void ofxProjectionMask::mouseDragged(ofMouseEventArgs &args){
    if(selectedMaskFrame != 0){
        TransformState state = selectedMaskFrame->getTransformState();
        
        if(state == Translating){
            float x = mouse.newSelectionX();
            float y = mouse.newSelectionY();
            selectedMaskFrame->setPosition(x, y);
            
        }else if(state == Scaling){
            int width = mouse.newSelectionWidth();
            int height = mouse.newSelectionHeight();
            Corner corner = selectedMaskFrame->highlightedCorner();
            selectedMaskFrame->setSize(width, height, corner);
            
        }else if(state == Masking){
            float x = mouse.newSelectionX();
            float y = mouse.newSelectionY();
            selectedMaskFrame->setSelectedMaskPointPosition(x, y);
        }
    }
}

void ofxProjectionMask::mousePressed(ofMouseEventArgs &args){
    selectedMaskFrame = canvasContents.beginTransform();
    if(selectedMaskFrame != 0){
        mouse.setSelection(selectedMaskFrame);
    }
}

void ofxProjectionMask::mouseReleased(ofMouseEventArgs &args){
    selectedMaskFrame = 0;
    canvasContents.endTransform();
    xml.autoSave();
}

void ofxProjectionMask::setVolumes(float *playbackVolume, vector<float> *nonPlaybackVolumes){
    textArea.setVolumes(playbackVolume, nonPlaybackVolumes);
}

ofxLayerMask* ofxProjectionMask::nextPattern() {
    int patternId = (canvasContents.getMaskFrames()->size()) % patterns.size();
    return patterns.at(patternId);
}

ofxLayerMask* ofxProjectionMask::getBackground() {
    return &background;
}

//Protected
void ofxProjectionMask::undo(){
    canvasContents.undo();
}

void ofxProjectionMask::redo(){
    canvasContents.redo();
}

void ofxProjectionMask::nudge(Direction direction){
    canvasContents.nudge(direction);
}

void ofxProjectionMask::toggleFrameNudge(){
    canvasContents.toggleFrameNudge();
    textArea.setFrameNudgeEnabled(canvasContents.getFrameNudgeEnabled());
}

void ofxProjectionMask::createNewMaskFrame(){
    MaskFrame maskFrame;
    maskFrame.assignCanvases(designCanvas, liveCanvas);
    maskFrame.setPattern(nextPattern());
    maskFrame.setSize(presets.newMaskFrameWidth, presets.newMaskFrameHeight);
    maskFrame.setPosition(mouse.x, mouse.y);
    canvasContents.add(&maskFrame);
}

void ofxProjectionMask::createNewMaskPoint(){
    canvasContents.createMaskPointAt(mouse.x, mouse.y);
}

void ofxProjectionMask::deleteHighlightedItem(){
    canvasContents.eraseHighlighted();
}

void ofxProjectionMask::cycleMode(){
    if(displayMode == Design){
        displayMode = HalfLive;
    }else if(displayMode == HalfLive){
        displayMode = Live;
    }else if(displayMode == Live){
        displayMode = Design;
    }
}

bool ofxProjectionMask::mouseIsOverDesignCanvas(){
    return mouse.x > this->designCanvas.getX() && mouse.x < (this->designCanvas.getX() + this->designCanvas.getWidth())
    && mouse.y > this->designCanvas.getY() && mouse.y < (this->designCanvas.getY() + this->designCanvas.getHeight());
}

void ofxProjectionMask::drawLiveCursor(){
    if(mouseIsOverDesignCanvas() && displayMode != Live){
        int liveMouseX = ofMap(mouse.x, designCanvas.getX(), designCanvas.getX() + designCanvas.getWidth(), liveCanvas.getX(), liveCanvas.getX() + liveCanvas.getWidth());
        int liveMouseY = ofMap(mouse.y, designCanvas.getY(), designCanvas.getY() + designCanvas.getHeight(), liveCanvas.getY(), liveCanvas.getY() + liveCanvas.getHeight());
        
        ofDrawLine(liveMouseX - 5, liveMouseY - 5, liveMouseX + 5, liveMouseY + 5);
        ofDrawLine(liveMouseX + 5, liveMouseY - 5, liveMouseX - 5, liveMouseY + 5);
    }
}

void ofxProjectionMask::drawBufferPreviews(){
    ofPushMatrix();
    ofTranslate(presets.bufferPreviewX, presets.bufferPreviewY);
    
    ofSetColor(255, 255, 255, 255);
    ofNoFill();
    
    int x = 0, y = 0, count = 0;
    
    for(int i = 0; i < patterns.size(); i++){
        ofTranslate(x, y);
        patterns.at(i)->drawLayer(0, 0, 0, presets.bufferPreviewWidth, presets.bufferPreviewHeight, false);
        ofDrawRectangle(0, 0, presets.bufferPreviewWidth, presets.bufferPreviewHeight);
        ofDrawBitmapString("Buffer " + ofToString(i + 1), 0, presets.bufferPreviewHeight + presets.bufferMargin);
        x = presets.bufferPreviewWidth + presets.bufferMargin;
    }
    
    ofPopMatrix();
}

bool ofxProjectionMask::isTransforming(){
    return selectedMaskFrame != 0 && selectedMaskFrame->getTransformState() != NoTransform;
}
