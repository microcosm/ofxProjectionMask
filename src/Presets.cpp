#include "Presets.h"

/*
  Edit your presets here
  ======================
  This file is full of presets to help you easily switch between when
  you are developing your patterns and when you want to display live
  on a projector.

  For fuller instructions on dualscreen/fullscreen setup, check out
  ofApp.cpp in the example project.

  Development mode presets                                      |
  ========================                                      |
  You probably won't need to change this. Scroll down to find  \|/
  'production' mode presets.                                    V
 
  In my case, it's a late 2011 MacBook Pro at (1680 x 1050px), so as
  long as everything fits inside those dimensions:
 */
const int developmentSoloWindowWidth = 1100;
const int developmentSoloWindowHeight = 800;

const int developmentNumGridLinesX = 14;
const int developmentNumGridLinesY = 10;

const int developmentDesignCanvasX = 402;
const int developmentDesignCanvasY = 8;
const int developmentDesignCanvasWidth = 240;
const int developmentDesignCanvasHeight = 180;
const int developmentDesignCanvasLabelX = 402;
const int developmentDesignCanvasLabelY = 204;

const int developmentLiveCanvasX = 402;
const int developmentLiveCanvasY = 340;
const int developmentLiveCanvasWidth = 610;
const int developmentLiveCanvasHeight = 410;

const int developmentBufferPreviewX = 402;
const int developmentBufferPreviewY = 224;
const int developmentBufferPreviewWidth = 80;
const int developmentBufferPreviewHeight = 80;
const int developmentBufferMargin = 16;

const int developmentNumberBoxWidth = 100;
const int developmentNumberBoxHeight = 20;

const int developmentInstructionsX = 8;
const int developmentInstructionsY = 18;
const int developmentPlaybackVolumeX = 9;
const int developmentPlaybackVolumeY = 726;
const int developmentNonPlaybackVolumeX = 320;
const int developmentNonPlaybackVolumeY = 746;

const int developmentNumberTagMargin = 20;
const int developmentNumberBoxMargin = 6;
const int developmentNumberTagOffsetX = -20;
const int developmentNumberTagOffsetY = 14;

const int developmentNewMaskFrameWidth = 70;
const int developmentNewMaskFrameHeight = 100;

const bool developmentStartFullscreen = false;
const char* developmentStorageDirectory = "development";

/*
  Production mode presets
  =======================
  Usually a laptop and a projector. These presets are for top-aligned
  monitors:
                                                   0    1680    4240
  ---------------------------------              0 +-----+-------+
  Left:     2011 MacBook Pro (1680 x 1050px)       |  L  |   R   |
  Right:    Monoprice        (2560 x 1600px)  1050 +-----|       |
                                                         +-------+
*/

const char* productionSecondWindowName = "openFrameworks Window 2";
const int productionSecondWindowX = 2880; //The second window begins at the far right (full width) of the left screen
const int productionSecondWindowY = 0;
const int productionSecondWindowWidth = 1920;
const int productionSecondWindowHeight = 1080;

const int productionNumGridLinesX = 60;
const int productionNumGridLinesY = 46;

const int productionDesignCanvasX = 10;
const int productionDesignCanvasY = 10;
const int productionDesignCanvasWidth = 1004;
const int productionDesignCanvasHeight = 710;
const int productionDesignCanvasLabelX = -1000;
const int productionDesignCanvasLabelY = -1000;

const int productionLiveCanvasX = 0;
const int productionLiveCanvasY = 0;
const int productionLiveCanvasWidth = productionSecondWindowWidth;
const int productionLiveCanvasHeight = productionSecondWindowHeight;

const int productionBufferPreviewX = 10;
const int productionBufferPreviewY = 730;
const int productionBufferPreviewWidth = 150;
const int productionBufferPreviewHeight = 150;
const int productionBufferMargin = 16;

const int productionNumberBoxWidth = 290;
const int productionNumberBoxHeight = 48;

const int productionInstructionsX = 1028;
const int productionInstructionsY = 26;
const int productionPlaybackVolumeX = 1028;
const int productionPlaybackVolumeY = 688;
const int productionNonPlaybackVolumeX = 1651;
const int productionNonPlaybackVolumeY = 736;

const int productionNumberTagMargin = 20;
const int productionNumberBoxMargin = 12;
const int productionNumberTagOffsetX = -18;
const int productionNumberTagOffsetY = 28;

const int productionNewMaskFrameWidth = 200;
const int productionNewMaskFrameHeight = 300;

const bool productionStartFullscreen = true;
const char* productionStorageDirectory = "production";

void Presets::setMode(PresetMode _mode){
    mode = _mode;
    load();
}

PresetMode Presets::getMode(){
    return mode;
}

void Presets::cycleMode(){
    if(mode == PRESETS_DEVELOPMENT){
        setMode(PRESETS_PRODUCTION);
    }else if(mode == PRESETS_PRODUCTION){
        setMode(PRESETS_DEVELOPMENT);
    }
}

bool Presets::isDevelopmentMode(){
    return mode == PRESETS_DEVELOPMENT;
}

bool Presets::isProductionMode(){
    return mode == PRESETS_PRODUCTION;
}

void Presets::load() {
    loadContextIndependantValues();
    
    if(mode == PRESETS_DEVELOPMENT) {
        loadDevelopmentValues();
    } else if(mode == PRESETS_PRODUCTION) {
        loadProductionValues();
    }
}

void Presets::loadContextIndependantValues() {
    soloWindowWidth = developmentSoloWindowWidth;
    soloWindowHeight = developmentSoloWindowHeight;
    
    secondWindowName = productionSecondWindowName;
    secondWindowX = productionSecondWindowX;
    secondWindowY = productionSecondWindowY;
    secondWindowWidth = productionSecondWindowWidth;
    secondWindowHeight = productionSecondWindowHeight;
}

void Presets::loadDevelopmentValues() {
    numGridLinesX = developmentNumGridLinesX;
    numGridLinesY = developmentNumGridLinesY;
    
    designCanvasX = developmentDesignCanvasX;
    designCanvasY = developmentDesignCanvasY;
    designCanvasWidth = developmentDesignCanvasWidth;
    designCanvasHeight = developmentDesignCanvasHeight;
    designCanvasLabelX = developmentDesignCanvasLabelX;
    designCanvasLabelY = developmentDesignCanvasLabelY;
    
    liveCanvasX = developmentLiveCanvasX;
    liveCanvasY = developmentLiveCanvasY;
    liveCanvasWidth = developmentLiveCanvasWidth;
    liveCanvasHeight = developmentLiveCanvasHeight;
    
    bufferPreviewX = developmentBufferPreviewX;
    bufferPreviewY = developmentBufferPreviewY;
    bufferPreviewWidth = developmentBufferPreviewWidth;
    bufferPreviewHeight = developmentBufferPreviewHeight;
    bufferMargin = developmentBufferMargin;
    
    numberBoxWidth = developmentNumberBoxWidth;
    numberBoxHeight = developmentNumberBoxHeight;
    
    instructionsX = developmentInstructionsX;
    instructionsY = developmentInstructionsY;
    playbackVolumeX = developmentPlaybackVolumeX;
    playbackVolumeY = developmentPlaybackVolumeY;
    nonPlaybackVolumeX = developmentNonPlaybackVolumeX;
    nonPlaybackVolumeY = developmentNonPlaybackVolumeY;
    
    numberTagMargin = developmentNumberTagMargin;
    numberBoxMargin = developmentNumberBoxMargin;
    numberTagOffsetX = developmentNumberTagOffsetX;
    numberTagOffsetY = developmentNumberTagOffsetY;
    
    newMaskFrameWidth = developmentNewMaskFrameWidth;
    newMaskFrameHeight = developmentNewMaskFrameHeight;
    
    startFullscreen = developmentStartFullscreen;
    storageDirectory = developmentStorageDirectory;
}

void Presets::loadProductionValues() {
    numGridLinesX = productionNumGridLinesX;
    numGridLinesY = productionNumGridLinesY;
    
    designCanvasX = productionDesignCanvasX;
    designCanvasY = productionDesignCanvasY;
    designCanvasWidth = productionDesignCanvasWidth;
    designCanvasHeight = productionDesignCanvasHeight;
    designCanvasLabelX = productionDesignCanvasLabelX;
    designCanvasLabelY = productionDesignCanvasLabelY;
    
    liveCanvasX = productionLiveCanvasX;
    liveCanvasY = productionLiveCanvasY;
    liveCanvasWidth = productionLiveCanvasWidth;
    liveCanvasHeight = productionLiveCanvasHeight;
    
    bufferPreviewX = productionBufferPreviewX;
    bufferPreviewY = productionBufferPreviewY;
    bufferPreviewWidth = productionBufferPreviewWidth;
    bufferPreviewHeight = productionBufferPreviewHeight;
    bufferMargin = productionBufferMargin;
    
    numberBoxWidth = productionNumberBoxWidth;
    numberBoxHeight = productionNumberBoxHeight;
    
    instructionsX = productionInstructionsX;
    instructionsY = productionInstructionsY;
    playbackVolumeX = productionPlaybackVolumeX;
    playbackVolumeY = productionPlaybackVolumeY;
    nonPlaybackVolumeX = productionNonPlaybackVolumeX;
    nonPlaybackVolumeY = productionNonPlaybackVolumeY;
    
    numberTagMargin = productionNumberTagMargin;
    numberBoxMargin = productionNumberBoxMargin;
    numberTagOffsetX = productionNumberTagOffsetX;
    numberTagOffsetY = productionNumberTagOffsetY;
    
    newMaskFrameWidth = productionNewMaskFrameWidth;
    newMaskFrameHeight = productionNewMaskFrameHeight;
    
    startFullscreen = productionStartFullscreen;
    storageDirectory = productionStorageDirectory;
}
