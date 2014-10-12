#pragma once

enum EnvironmentMode { Development, Production };

class Environment{
public:
    Environment(){
        /* Switch environmet here */
        //mode = Development;
        mode = Production;
        
        loadConstants();
    }
    
    int windowWidth;
    int windowHeight;
    
    int numGridLinesX;
    int numGridLinesY;
    
    int designCanvasX;
    int designCanvasY;
    int designCanvasWidth;
    int designCanvasHeight;
    
    int liveCanvasX;
    int liveCanvasY;
    int liveCanvasWidth;
    int liveCanvasHeight;
    
    int bufferPreviewX;
    int bufferPreviewY;
    int bufferPreviewWidth;
    int bufferPreviewHeight;
    int bufferMargin;
    int stackAfter;
    
    int numberBoxWidth;
    int numberBoxHeight;
    
    int instructionsX;
    int instructionsY;
    int playbackVolumeX;
    int playbackVolumeY;
    int nonPlaybackVolumeX;
    int nonPlaybackVolumeY;
    
    int numberTagMargin;
    int numberBoxMargin;
    int numberTagOffsetX;
    int numberTagOffsetY;
    
    int newMaskFrameWidth;
    int newMaskFrameHeight;
    
    bool startFullscreen;
    
protected:
    void loadConstants();
    EnvironmentMode mode;
};