#include "Presets.h"

/* Edit your presets here
   ======================
   This file is full of presets, to help you easily switch between when
   you are developing your patterns and when you want to display live
   on a projector.

   Go to Presets.h to switch between Development and Production modes.

   Development mode presets
   ========================
   Usually a single screen, in my case:
   -----------------------------------
   Late 2011 MacBook Pro (1680 x 1050px)
*/
const int developmentWindowWidth = 800;
const int developmentWindowHeight = 400;

const int developmentNumGridLinesX = 14;
const int developmentNumGridLinesY = 10;

const int developmentDesignCanvasX = 8;
const int developmentDesignCanvasY = 10;
const int developmentDesignCanvasWidth = 320;
const int developmentDesignCanvasHeight = 240;

const int developmentLiveCanvasX = 342;
const int developmentLiveCanvasY = 10;
const int developmentLiveCanvasWidth = 668;
const int developmentLiveCanvasHeight = 480;

const int developmentBufferPreviewX = 342;
const int developmentBufferPreviewY = 505;
const int developmentBufferPreviewWidth = 100;
const int developmentBufferPreviewHeight = 100;
const int developmentBufferMargin = 16;
const int developmentStackAfter = 5;

const int developmentNumberBoxWidth = 100;
const int developmentNumberBoxHeight = 20;

const int developmentInstructionsX = 8;
const int developmentInstructionsY = 274;
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

/* Production mode presets
   =======================
   Usually a laptop and a projector. These presets are for top-aligned
   monitors:
   ---------------------------------             +-----+-------+
   Left:     Retina MacBook Pro (1440 x 900px)   |  L  |   R   |
   Right:    Monoprice          (2560 x 1600px)  +-----|       |
   Combined: (4000 x 1600px)                           +-------+
*/

const int productionWindowWidth = 4000;
const int productionWindowHeight = 1600;

const int productionNumGridLinesX = 60;
const int productionNumGridLinesY = 46;

const int productionDesignCanvasX = 10;
const int productionDesignCanvasY = 10;
const int productionDesignCanvasWidth = 1004;
const int productionDesignCanvasHeight = 710;

const int productionLiveCanvasX = 1440;
const int productionLiveCanvasY = 0;
const int productionLiveCanvasWidth = 2560;
const int productionLiveCanvasHeight = 1600;

const int productionBufferPreviewX = 10;
const int productionBufferPreviewY = 730;
const int productionBufferPreviewWidth = 150;
const int productionBufferPreviewHeight = 150;
const int productionBufferMargin = 16;
const int productionStackAfter = 1;

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

void Presets::setPresetMode(PresetMode _mode){
    mode = _mode;
    load();
}

void Presets::load() {
    
    if(mode == PRESETS_DEVELOPMENT) {
        
        windowWidth = developmentWindowWidth;
        windowHeight = developmentWindowHeight;
        
        numGridLinesX = developmentNumGridLinesX;
        numGridLinesY = developmentNumGridLinesY;
        
        designCanvasX = developmentDesignCanvasX;
        designCanvasY = developmentDesignCanvasY;
        designCanvasWidth = developmentDesignCanvasWidth;
        designCanvasHeight = developmentDesignCanvasHeight;
        
        liveCanvasX = developmentLiveCanvasX;
        liveCanvasY = developmentLiveCanvasY;
        liveCanvasWidth = developmentLiveCanvasWidth;
        liveCanvasHeight = developmentLiveCanvasHeight;
        
        bufferPreviewX = developmentBufferPreviewX;
        bufferPreviewY = developmentBufferPreviewY;
        bufferPreviewWidth = developmentBufferPreviewWidth;
        bufferPreviewHeight = developmentBufferPreviewHeight;
        bufferMargin = developmentBufferMargin;
        stackAfter = developmentStackAfter;
        
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
        
    } else if(mode == PRESETS_PRODUCTION) {
        
        windowWidth = productionWindowWidth;
        windowHeight = productionWindowHeight;
        
        numGridLinesX = productionNumGridLinesX;
        numGridLinesY = productionNumGridLinesY;
        
        designCanvasX = productionDesignCanvasX;
        designCanvasY = productionDesignCanvasY;
        designCanvasWidth = productionDesignCanvasWidth;
        designCanvasHeight = productionDesignCanvasHeight;
        
        liveCanvasX = productionLiveCanvasX;
        liveCanvasY = productionLiveCanvasY;
        liveCanvasWidth = productionLiveCanvasWidth;
        liveCanvasHeight = productionLiveCanvasHeight;
        
        bufferPreviewX = productionBufferPreviewX;
        bufferPreviewY = productionBufferPreviewY;
        bufferPreviewWidth = productionBufferPreviewWidth;
        bufferPreviewHeight = productionBufferPreviewHeight;
        bufferMargin = productionBufferMargin;
        stackAfter = productionStackAfter;
        
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
    }
}
