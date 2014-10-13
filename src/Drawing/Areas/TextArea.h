#pragma once
#include "ofMain.h"
#include "ofTrueTypeFont.h"

class TextArea{
public:
    TextArea(){
        playbackVolume = 0;
        setFrameNudgeEnabled(false);
    }
    void setInstructionsPosition(int x, int y);
    void setPlaybackVolumePosition(int x, int y);
    void setNonPlaybackVolumesPosition(int x, int y);
    
    void setNumberBoxSize(int width, int height);
    void setMargins(int numberTagMargin, int numberBoxMargin);
    void setOffsets(int numberTagOffsetX, int numberTagOffsetY);
    
    void setRenderMode(string mode);
    void setFrameNudgeEnabled(bool enabled);
    void setVolumes(float *playbackVolume, vector<float> *nonPlaybackVolumes);
    
    void draw();
protected:
    int instructionsX, instructionsY;
    int playbackVolumeX, playbackVolumeY;
    int nonPlaybackVolumeX, nonPlaybackVolumeY;
    int numberBoxWidth, numberBoxHeight;
    
    int numberTagMargin, numberBoxMargin;
    int numberTagOffsetX, numberTagOffsetY;
    
    string renderModeText;
    string frameNudgeStatus;
    string textToDisplay;
    float *playbackVolume;
    vector<float> *nonPlaybackVolumes;
    
    void drawInstructionsText();
    void drawPlaybackVolume();
    void drawNonPlaybackVolumes();
    string getTextToDisplay();
};