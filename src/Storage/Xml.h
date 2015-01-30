#pragma once
#include "ofxXmlSettings.h"
#include "Canvas.h"
#include "CanvasContents.h"


class Xml{
public:
    void setup(Canvas *designCanvas, Canvas *liveCanvas, CanvasContents *canvasContents, vector<ofFbo> *buffers, string directory);
    void save();
    void autoSave();
    void load();
protected:
    Canvas *designCanvas, *liveCanvas;
    int sourceDesignCanvasWidth, sourceDesignCanvasHeight;
    int sourceLiveCanvasWidth, sourceLiveCanvasHeight;
    int sourceMaskFrameWidth, sourceMaskFrameHeight;
    CanvasContents *canvasContents;
    vector<ofFbo> *buffers;
    string xmlSubPath;
    
    void save(bool autoSave);
    void backupExistingFile();
    void ensureDirectory();
    
    void addTimestamp(ofxXmlSettings *xml);
    void addType(ofxXmlSettings *xml, bool autoSave);
    void addCanvas(ofxXmlSettings *xml, Canvas *canvas, string tagName);
    void addMaskFrames(ofxXmlSettings *xml, CanvasContents *canvasContents);
    void addMaskFrame(ofxXmlSettings *xml, MaskFrame *maskFrame, int i);
    void addMaskPoints(ofxXmlSettings *xml, MaskFrame *maskFrame);
    void addMaskPoint(ofxXmlSettings *xml, MaskPoint *maskPoint, int i);
    
    void loadSourceCanvasDimensions(ofxXmlSettings *xml);
    void loadMaskFrames(ofxXmlSettings *xml);
    void loadMaskFrame(ofxXmlSettings *xml, SafeDeque<MaskFrame> *maskFrames, int i);
    void loadMaskPoints(ofxXmlSettings *xml, MaskFrame *maskFrame);
    void loadMaskPoint(ofxXmlSettings *xml, SafeDeque<MaskPoint> *maskPoints, MaskFrame *maskFrame, int i);
    
    int getMaskFrameId(ofxXmlSettings *xml);
    int getMaskFrameLiveWidth(ofxXmlSettings *xml);
    int getMaskFrameLiveHeight(ofxXmlSettings *xml);
    int getMaskFrameLiveX(ofxXmlSettings *xml);
    int getMaskFrameLiveY(ofxXmlSettings *xml);
    int getMaskPointLiveX(ofxXmlSettings *xml, MaskFrame *maskFrame);
    int getMaskPointLiveY(ofxXmlSettings *xml, MaskFrame *maskFrame);
};