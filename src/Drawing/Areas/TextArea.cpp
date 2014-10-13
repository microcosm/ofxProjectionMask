#include "TextArea.h"

const ofColor textColor = ofColor(255, 255, 255, 255);

const string stringOne = "      RENDER\n      ------\n       Mode: ";
const string stringTwo = "\n  Framerate: ";
const string stringThree = "\nFrame nudge: ";
const string stringFour = "\n\n\n      KEYS\n      ----\n         F : new mask frame\n         P : new point inside frame\n \narrow keys : nudge\n       del : delete\n\n         M : cycle render mode\n         N : enable frame nudge\n\n         U : undo (keep pressing)\n         R : redo (keep pressing)\n\n         S : save\n         L : load\n\n     space : toggle fullscreen\n\n\n     GUIDE\n     -----\n  1. Position your mouse over the design\n     canvas. Notice there is a corresponding\n     crosshair on the live canvas.\n\n  2. Press 'f' to create a new mask frame. You\n     can click, drag, and re-size the frame\n     with the mouse.\n\n  3. Position the mouse inside the mask frame,\n     and press 'p' in 3 different locations\n     to create your first triangle.\n\n  4. Hover your mouse over the edges of the\n     triangle. You can now click and drag to\n     create more points.\n\n  5. Click 'u' for 'undo' a few times, and\n     then 'r' for 'redo'.\n\n  6. Hover over one of the points on your\n     shape, and use the arrow keys. Each press\n     nudges the point on the live canvas by 1\n     pixel.\n\n  7. Press 'm' to cycle through render modes.\n\n  8. Check out the bin/data/xml folder. Every\n     time you make a change, a backup is saved\n     in there. If you ever want to get back to\n     a previous state, just overwrite\n     'saved.xml' and press 'l' for 'load'.";

const string playbackVolumeTag = "Vol: ";
const string nonPlaybackVolumeTag = "Non-Playback";

const string frameNudgeEnabledText = "Enabled";
const string frameNudgeDisabledText = "Disabled";

void TextArea::setInstructionsPosition(int x, int y){
    this->instructionsX = x;
    this->instructionsY = y;
}

void TextArea::setPlaybackVolumePosition(int x, int y){
    this->playbackVolumeX = x;
    this->playbackVolumeY = y;
}

void TextArea::setNonPlaybackVolumesPosition(int x, int y){
    this->nonPlaybackVolumeX = x;
    this->nonPlaybackVolumeY = y;
}

void TextArea::setNumberBoxSize(int width, int height){
    this->numberBoxWidth = width;
    this->numberBoxHeight = height;
}

void TextArea::setMargins(int numberTagMargin, int numberBoxMargin){
    this->numberTagMargin = numberTagMargin;
    this->numberBoxMargin = numberBoxMargin;
}

void TextArea::setOffsets(int numberTagOffsetX, int numberTagOffsetY){
    this->numberTagOffsetX = numberTagOffsetX;
    this->numberTagOffsetY = numberTagOffsetY;
}

void TextArea::setRenderMode(string mode){
    renderModeText = mode;
}

void TextArea::setFrameNudgeEnabled(bool enabled){
    if(enabled){
        frameNudgeStatus = frameNudgeEnabledText;
    }else{
        frameNudgeStatus = frameNudgeDisabledText;
    }
}

void TextArea::setVolumes(float *playbackVolume, vector<float> *nonPlaybackVolumes){
    this->playbackVolume = playbackVolume;
    this->nonPlaybackVolumes = nonPlaybackVolumes;
}

void TextArea::draw(){
    ofSetColor(textColor);
    drawInstructionsText();
    //drawPlaybackVolume();
    //drawNonPlaybackVolumes();
}

void TextArea::drawInstructionsText(){
    ofSetColor(textColor);
    string textToDisplay = getTextToDisplay();
    ofDrawBitmapString(textToDisplay, instructionsX, instructionsY);
}

void TextArea::drawPlaybackVolume(){
    ofNoFill();
    string volumeText = playbackVolumeTag + ofToString(*playbackVolume, 2);
    ofDrawBitmapString(volumeText, playbackVolumeX, playbackVolumeY + numberBoxHeight + numberTagMargin);
    ofRect(playbackVolumeX, playbackVolumeY, numberBoxWidth, numberBoxHeight);
    ofFill();
    ofRect(playbackVolumeX, playbackVolumeY, *playbackVolume * numberBoxWidth, numberBoxHeight);
}

void TextArea::drawNonPlaybackVolumes(){
    int rectX = nonPlaybackVolumeX - numberBoxWidth;
    int tagX = rectX + numberTagOffsetX;
    int rectY, tagY;
    float volume;
    int numVolumes = nonPlaybackVolumes->size();
    int volumeIndex;
    
    for(int i = 0; i < numVolumes; i++){
        volumeIndex = numVolumes - i;
        rectY = nonPlaybackVolumeY - numberBoxHeight - ((numberBoxHeight + numberBoxMargin) * i);
        tagY = nonPlaybackVolumeY - round(numberBoxHeight * 0.5);
        ofNoFill();
        ofRect(rectX, rectY, numberBoxWidth, numberBoxHeight);
        ofFill();
        ofRect(rectX, rectY, (*nonPlaybackVolumes)[volumeIndex - 1] * numberBoxWidth, numberBoxHeight);
        ofDrawBitmapString(ofToString(volumeIndex), tagX, rectY + numberTagOffsetY);
    }
    
    ofDrawBitmapString(nonPlaybackVolumeTag, nonPlaybackVolumeX - numberBoxWidth, nonPlaybackVolumeY + numberTagMargin);
}

string TextArea::getTextToDisplay(){
    return stringOne + renderModeText + stringTwo + ofToString(ofGetFrameRate()) + stringThree + frameNudgeStatus + stringFour;
}