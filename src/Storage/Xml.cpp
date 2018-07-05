#include "Xml.h"

const string sessionTag = "session";
const string typeTag = "type";
const string timestampTag = "timestamp";
const string designCanvasTag = "designCanvas";
const string liveCanvasTag = "liveCanvas";
const string maskFramesTag = "maskFrames";
const string maskFrameTag = "maskFrame";
const string maskPointsTag = "maskPoints";
const string maskPointTag = "maskPoint";

const string idTag = "id";
const string widthTag = "width";
const string heightTag = "height";
const string xTag = "x";
const string yTag = "y";

const string designWidthTag = "designWidth";
const string designHeightTag = "designHeight";
const string designXTag = "designX";
const string designYTag = "designY";

const string liveWidthTag = "liveWidth";
const string liveHeightTag = "liveHeight";
const string liveXTag = "liveX";
const string liveYTag = "liveY";

const string levelDivider = ":";

const string designCanvasName = "design";
const string liveCanvasName = "live";

const string typeAuto = "auto";
const string typeManual = "manual";

const string defaultTimestamp = "no-timestamp-found";

const string defaultFileName = "saved";
const string fileExtension = ".xml";
const string directoryDivider = "/";
const string projectionMaskPath = "ProjectionMasks";

void Xml::setup(Canvas *designCanvas, Canvas *liveCanvas, CanvasContents *canvasContents, vector<ofxLayerMask*> *patterns, string directory){
    fileName = defaultFileName;
    this->designCanvas = designCanvas;
    this->liveCanvas = liveCanvas;
    this->canvasContents = canvasContents;
    this->patterns = patterns;
    this->xmlSubPath = projectionMaskPath + directoryDivider + directory;
}

void Xml::save(){
    save(false);
}

void Xml::autoSave(){
    save(true);
}

void Xml::load(){
    
	ofxXmlSettings xml;
    
    if(xml.loadFile(xmlSubPath + directoryDivider + fileName + fileExtension)){
        xml.pushTag(sessionTag);
        
        loadSourceCanvasDimensions(&xml);
        loadMaskFrames(&xml);
        
        xml.popTag();   
    }
}

void Xml::save(bool autoSave){
    
    ensureDirectory();
    backupExistingFile();
    
	ofxXmlSettings xml;
    
	xml.addTag(sessionTag);
	xml.pushTag(sessionTag);
    
    addType(&xml, autoSave);
    addTimestamp(&xml);
    addCanvas(&xml, designCanvas, designCanvasTag);
    addCanvas(&xml, liveCanvas, liveCanvasTag);
    addMaskFrames(&xml, canvasContents);
    
    xml.popTag();
    
	xml.saveFile(xmlSubPath + directoryDivider + fileName + fileExtension);
}

void Xml::backupExistingFile(){
    
	ofxXmlSettings xml;
    
    if(xml.loadFile(xmlSubPath + directoryDivider + fileName + fileExtension)){
        xml.pushTag(sessionTag);
        string timestamp = xml.getValue(timestampTag, defaultTimestamp);
        xml.saveFile(xmlSubPath + directoryDivider + fileName + "-" + timestamp + fileExtension);
    }
}

void Xml::ensureDirectory(){
    
    ofDirectory directory;
    
    string dataDirectory = ofToDataPath("");
    if(!directory.doesDirectoryExist(dataDirectory)){
        directory.createDirectory(dataDirectory);
    }
    
    string projectionMaskDirectory = ofToDataPath(projectionMaskPath);
    if(!directory.doesDirectoryExist(projectionMaskDirectory)){
        directory.createDirectory(projectionMaskDirectory);
    }

    string xmlSubDirectory = ofToDataPath(xmlSubPath);
	if(!directory.doesDirectoryExist(xmlSubDirectory)){
        directory.createDirectory(xmlSubDirectory);
    }
}

void Xml::addTimestamp(ofxXmlSettings *xml){
    xml->addTag(timestampTag);
    xml->setValue(timestampTag, ofGetTimestampString());
}

void Xml::addType(ofxXmlSettings *xml, bool autoSave){
    xml->addTag(typeTag);
    if(autoSave){
        xml->setValue(typeTag, typeAuto);
    }else{
        xml->setValue(typeTag, typeManual);
    }
}

void Xml::addCanvas(ofxXmlSettings *xml, Canvas *canvas, string tagName){
    
    xml->addTag(tagName);
    xml->pushTag(tagName);
    
    xml->addTag(widthTag);
    xml->addTag(heightTag);
    xml->addTag(xTag);
    xml->addTag(yTag);
    
    xml->setValue(widthTag, canvas->getWidth());
    xml->setValue(heightTag, canvas->getHeight());
    xml->setValue(xTag, canvas->getX());
    xml->setValue(yTag, canvas->getY());
    
    xml->popTag();
}

void Xml::addMaskFrames(ofxXmlSettings *xml, CanvasContents *canvasContents){
    
    xml->addTag(maskFramesTag);
    xml->pushTag(maskFramesTag);
    
    SafeDeque<MaskFrame> *maskFrames = canvasContents->getMaskFrames();
    
    for(int i = 0; i < maskFrames->size(); i++){
        addMaskFrame(xml, maskFrames->getPointer(i), i);
    }
    
    xml->popTag();
}

void Xml::addMaskFrame(ofxXmlSettings *xml, MaskFrame *maskFrame, int i){
    
    xml->addTag(maskFrameTag);
    xml->setValue(maskFrameTag + levelDivider + idTag, maskFrame->getId(), i);
    
    xml->setValue(maskFrameTag + levelDivider + designWidthTag, maskFrame->getWidth(), i);
    xml->setValue(maskFrameTag + levelDivider + designHeightTag, maskFrame->getHeight(), i);
    xml->setValue(maskFrameTag + levelDivider + designXTag, maskFrame->getRelativeX(), i);
    xml->setValue(maskFrameTag + levelDivider + designYTag, maskFrame->getRelativeY(), i);
    
    xml->setValue(maskFrameTag + levelDivider + liveWidthTag, maskFrame->getLiveWidth(), i);
    xml->setValue(maskFrameTag + levelDivider + liveHeightTag, maskFrame->getLiveHeight(), i);
    xml->setValue(maskFrameTag + levelDivider + liveXTag, maskFrame->getLiveRelativeX(), i);
    xml->setValue(maskFrameTag + levelDivider + liveYTag, maskFrame->getLiveRelativeY(), i);
    
    xml->pushTag(maskFrameTag, i);
    addMaskPoints(xml, maskFrame);
    xml->popTag();
}

void Xml::addMaskPoints(ofxXmlSettings *xml, MaskFrame *maskFrame){
    
    xml->addTag(maskPointsTag);
    xml->pushTag(maskPointsTag);
    
    SafeDeque<MaskPoint> *maskPoints = maskFrame->getMaskPoints();
    
    for(int i = 0; i < maskPoints->size(); i++){
        addMaskPoint(xml, maskPoints->getPointer(i), i);
    }
    
    xml->popTag();
}

void Xml::addMaskPoint(ofxXmlSettings *xml, MaskPoint *maskPoint, int i){
    
    xml->addTag(maskPointTag);
    
    xml->setValue(maskPointTag + levelDivider + designXTag, maskPoint->getX(), i);
    xml->setValue(maskPointTag + levelDivider + designYTag, maskPoint->getY(), i);
    xml->setValue(maskPointTag + levelDivider + liveXTag, maskPoint->getLiveX(), i);
    xml->setValue(maskPointTag + levelDivider + liveYTag, maskPoint->getLiveY(), i);
}

void Xml::loadSourceCanvasDimensions(ofxXmlSettings *xml){
    xml->pushTag(designCanvasTag);
    sourceDesignCanvasWidth = xml->getValue(widthTag, 0);
    sourceDesignCanvasHeight = xml->getValue(heightTag, 0);
    xml->popTag();
    
    xml->pushTag(liveCanvasTag);
    sourceLiveCanvasWidth = xml->getValue(widthTag, 0);
    sourceLiveCanvasHeight = xml->getValue(heightTag, 0);
    xml->popTag();
}

void Xml::loadMaskFrames(ofxXmlSettings *xml){
    
    xml->pushTag(maskFramesTag);
    
    SafeDeque<MaskFrame> *maskFrames = canvasContents->getMaskFrames();
    maskFrames->deleteAll();
    
    int numFrames = xml->getNumTags(maskFrameTag);
    
    for(int i = 0; i < numFrames; i++){
        loadMaskFrame(xml, maskFrames, i);
    }
    
    xml->popTag();
}

void Xml::loadMaskFrame(ofxXmlSettings *xml, SafeDeque<MaskFrame> *maskFrames, int i){
    
    xml->pushTag(maskFrameTag, i);
    
    MaskFrame maskFrame;
    maskFrame.setId(getMaskFrameId(xml));
    
    maskFrame.assignCanvases(*designCanvas, *liveCanvas);
    maskFrame.setPattern(nextPattern());
    
    int liveWidth = getMaskFrameLiveWidth(xml);
    int liveHeight = getMaskFrameLiveHeight(xml);
    maskFrame.setLiveSize(liveWidth, liveHeight);
    
    int liveX = getMaskFrameLiveX(xml);
    int liveY = getMaskFrameLiveY(xml);
    maskFrame.setLiveRelativePosition(liveX, liveY);
    
    loadMaskPoints(xml, &maskFrame);
    maskFrame.transposeToDesignCanvas();
    maskFrames->push_back(maskFrame);
    
    xml->popTag();
}

void Xml::loadMaskPoints(ofxXmlSettings *xml, MaskFrame *maskFrame){
    
    xml->pushTag(maskPointsTag, 0);
    
    SafeDeque<MaskPoint> *maskPoints = maskFrame->getMaskPoints();
    
    int numPoints = xml->getNumTags(maskPointTag);
    
    for(int i = 0; i < numPoints; i++){
        loadMaskPoint(xml, maskPoints, maskFrame, i);
    }
    
    xml->popTag();
}

void Xml::loadMaskPoint(ofxXmlSettings *xml, SafeDeque<MaskPoint> *maskPoints, MaskFrame *maskFrame, int i){
    
    xml->pushTag(maskPointTag, i);
    
    MaskPoint maskPoint;
    maskPoint.setType(Real);
    maskPoint.setLiveX(xml->getValue(liveXTag, 0));
    maskPoint.setLiveY(xml->getValue(liveYTag, 0));
    
    maskPoints->push_back(maskPoint);
    xml->popTag();
}

int Xml::getMaskFrameId(ofxXmlSettings *xml){
    return xml->getValue(idTag, 0);
}

int Xml::getMaskFrameLiveWidth(ofxXmlSettings *xml){
    sourceMaskFrameWidth = xml->getValue(liveWidthTag, 0);
    return ofMap(sourceMaskFrameWidth, 0, sourceLiveCanvasWidth, 0, liveCanvas->getWidth());
}

int Xml::getMaskFrameLiveHeight(ofxXmlSettings *xml){
    sourceMaskFrameHeight = xml->getValue(liveHeightTag, 0);
    return ofMap(sourceMaskFrameHeight, 0, sourceLiveCanvasHeight, 0, liveCanvas->getHeight());
}

int Xml::getMaskFrameLiveX(ofxXmlSettings *xml){
    int maskFrameLiveX = xml->getValue(liveXTag, 0);
    return ofMap(maskFrameLiveX, 0, sourceLiveCanvasWidth, 0, liveCanvas->getWidth());
}

int Xml::getMaskFrameLiveY(ofxXmlSettings *xml){
    int maskFrameLiveY = xml->getValue(liveYTag, 0);
    return ofMap(maskFrameLiveY, 0, sourceLiveCanvasHeight, 0, liveCanvas->getHeight());
}

int Xml::getMaskPointLiveX(ofxXmlSettings *xml, MaskFrame *maskFrame){
    int maskPointLiveX = xml->getValue(liveXTag, 0);
    return ofMap(maskPointLiveX, 0, sourceMaskFrameWidth, 0, maskFrame->getWidth());
}

int Xml::getMaskPointLiveY(ofxXmlSettings *xml, MaskFrame *maskFrame){
    int maskPointLiveY = xml->getValue(liveYTag, 0);
    return ofMap(maskPointLiveY, 0, sourceMaskFrameHeight, 0, maskFrame->getHeight());
}

ofxLayerMask* Xml::nextPattern() {
    int patternId = (canvasContents->getMaskFrames()->size()) % patterns->size();
    return patterns->at(patternId);
}
