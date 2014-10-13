#include "ofxProjectionMapper.h"

const int bufferStartFrameNum = 120;

//Public
void ofxProjectionMapper::setup(BufferPattern* _pattern, PresetMode _mode){
    presets.setMode(_mode);
    pattern = _pattern;
    setup();
}

void ofxProjectionMapper::setup(BufferPattern* _pattern){
    pattern = _pattern;
    setup();
}

void ofxProjectionMapper::setup(){
    
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
    mouse.setup(&designCanvas);
}

void ofxProjectionMapper::update(int mouseX, int mouseY){
    
    mouse.set(mouseX, mouseY);
    
    if(!isTransforming()){
        canvasContents.updateHighlights(mouseX, mouseY);
    }
    
    textArea.setDisplayMode(displayMode);
    textArea.setPresetMode(presets.getMode());
}

void ofxProjectionMapper::draw(){
    
    drawBufferPreviews();
    
    ofPushMatrix();
    ofTranslate(designCanvas.getX(), designCanvas.getY());
    designCanvas.draw();
    canvasContents.drawDesign();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(presets.designCanvasLabelX, presets.designCanvasLabelY);
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Design Canvas", ofPoint(0, 0));
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
    }else if(key == 'o' || key == 'O'){
        presets.cycleMode();
        setup();
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
    }else if(key == 'n' || key == 'N'){
        toggleFrameNudge();
    }
}

void ofxProjectionMapper::mouseDragged(){
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

void ofxProjectionMapper::mousePressed(){
    selectedMaskFrame = canvasContents.beginTransform();
    if(selectedMaskFrame != 0){
        mouse.setSelection(selectedMaskFrame);
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