#include "TextArea.h"

const ofColor textColor = ofColor(255, 255, 255, 255);

const string designModeText = "Design";
const string designLiveModeText = "Design / Live";
const string liveModeText = "Live";

const string developmentModeText = "Development";
const string productionModeText = "Production";

const string stringOne = "      RENDER\n      ------\nRender mode: ";
const string stringTwo = "\nPreset mode: ";
const string stringThree = "\n  Framerate: ";
const string stringFour = "\nFrame nudge: ";
const string stringFive = "\n\n      KEYS\n      ----\n         F : new mask frame\n         P : new point inside frame\narrow keys : nudge\n       del : delete\n         M : cycle render mode\n         N : enable frame nudge\n         U : undo (keep pressing)\n         R : redo (keep pressing)\n         S : save\n         L : load\n     space : toggle fullscreen\n\n     INSTRUCTIONS\n     ------------\n  1. Position your mouse over the design\n     canvas. Notice there is a corresponding\n     crosshair on the live canvas.\n\n  2. Press 'f' to create a new mask frame. You\n     can click, drag, and re-size the frame\n     with the mouse.\n\n  3. Position the mouse inside the mask frame,\n     and press 'p' in 3 different locations\n     to create your first triangle.\n\n  4. Hover your mouse over the edges of the\n     triangle. You can now click and drag to\n     create more points.\n\n  5. Click 'u' for 'undo' a few times, and\n     then 'r' for 'redo'.\n\n  6. Hover over one of the points on your\n     shape, and use the arrow keys. Each press\n     nudges the point on the live canvas by 1\n     pixel.\n\n  7. Press 'm' to cycle through render modes.\n\n  8. Check out the bin/data folder. Every\n     time you make a change, a backup is saved\n     in there. If you ever want to get back to\n     a previous state, just overwrite\n     'saved.xml' and press 'l' for 'load'.";

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

void TextArea::setDisplayMode(DisplayMode displayMode){
    if(displayMode == Design){
        renderModeText = designModeText;
    }else if(displayMode == HalfLive){
        renderModeText = designLiveModeText;
    }else if(displayMode == Live){
        renderModeText = liveModeText;
    }
}

void TextArea::setPresetMode(PresetMode presetMode){
    if(presetMode == PRESETS_DEVELOPMENT){
        presetModeText = developmentModeText;
    }else if(presetMode == PRESETS_PRODUCTION){
        presetModeText = productionModeText;
    }
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
    ofDrawRectangle(playbackVolumeX, playbackVolumeY, numberBoxWidth, numberBoxHeight);
    ofFill();
    ofDrawRectangle(playbackVolumeX, playbackVolumeY, *playbackVolume * numberBoxWidth, numberBoxHeight);
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
        ofDrawRectangle(rectX, rectY, numberBoxWidth, numberBoxHeight);
        ofFill();
        ofDrawRectangle(rectX, rectY, (*nonPlaybackVolumes)[volumeIndex - 1] * numberBoxWidth, numberBoxHeight);
        ofDrawBitmapString(ofToString(volumeIndex), tagX, rectY + numberTagOffsetY);
    }
    
    ofDrawBitmapString(nonPlaybackVolumeTag, nonPlaybackVolumeX - numberBoxWidth, nonPlaybackVolumeY + numberTagMargin);
}

string TextArea::getTextToDisplay(){
    return stringOne + renderModeText + stringTwo + presetModeText + stringThree + ofToString(ofGetFrameRate()) + stringFour + frameNudgeStatus + stringFive;
}
