#pragma once
#include "ofMain.h"
#include "Canvas.h"
#include "DragHandle.h"
#include "MaskPoint.h"
#include "PointObject.h"
#include "ofExtensions.h"
#include "SafeDeque.h"
#include "ofxTriangle.h"
#include "ofxLayerMask.h"

enum DisplayMode { Design, HalfLive, Live };
enum StretchMode {
    DO_NOT_STRETCH,
    STRETCH_TO_MASKFRAME
};

class MaskFrame{
public:
    MaskFrame(){
        highlighted = false;
        transformState = NoTransform;
        selectedMaskPoint = 0;
        ghostPoint.setType(Ghost);
        ghostPointIndex = 0;
        initialiseDragHandles();
    }
    
    int getId();
    void setId(int newId);
    void assignCanvases(Canvas& designCanvas, Canvas& liveCanvas);
    void setBuffers(vector<ofFbo> *buffers);
    void setPattern(ofxLayerMask *pattern);
    
    void highlightIfCloseTo(int absoluteX, int absoluteY);
    void setHighlighted(bool isHighlighted);
    bool isHighlighted();
    bool hasHighlightedDragHandle();
    bool hasHighlightedMaskPoint();
    bool hasGhostPoint();
    bool canDrawLive();
    MaskPoint* getHighlightedMaskPoint();
    DragHandle* getHighlightedDragHandle();
    int getSelectedMaskPointX();
    int getSelectedMaskPointY();
    SafeDeque<MaskPoint> *getMaskPoints();
    
    TransformState getTransformState();
    void setTransformState(TransformState transformState);
    
    void drawDesign();
    void drawLive(DisplayMode mode, StretchMode stretchMode);
    
    void setSize(int width, int height);
    void setSize(int width, int height, Corner movingCorner);
    void setLiveSize(int width, int height);
    void setLiveSize(int width, int height, Corner movingCorner);
    void setPosition(int absoluteX, int absoluteY);
    void setLivePosition(int absoluteX, int absoluteY);
    void setLiveRelativePosition(int absoluteX, int absoluteY);
    void setSelectedMaskPointPosition(int x, int y);
    void setX(int absoluteX);
    void setY(int absoluteY);
    int getX();
    int getY();
    int getRelativeX();
    int getRelativeY();
    int getWidth();
    int getHeight();
    int getLiveX();
    int getLiveY();
    int getLiveRelativeX();
    int getLiveRelativeY();
    int getLiveWidth();
    int getLiveHeight();
    int getSmallestLegalWidth();
    int getSmallestLegalHeight();
    int getSmallestLegalWidth(Corner cornerBeingAdjusted);
    int getSmallestLegalHeight(Corner cornerBeingAdjusted);
    
    void addMaskPoint(int absoluteX, int absoluteY);
    void makeGhostPointReal();
    void deleteSelectedMaskPoint();
    
    void nudge(Direction direction);
    void nudgeMaskPoint(Direction direction);
    void nudgeDragHandle(Direction direction);
    
    void transposeToLiveCanvas();
    void transposeToDesignCanvas();
    
    Corner highlightedCorner();
    
protected:
    int frameId;
    bool highlighted;
    bool hasAGhostPoint;
    int ghostPointIndex;
    TransformState transformState;
    MaskPoint* selectedMaskPoint;
    MaskPoint ghostPoint;
    vector<ofFbo> *buffers;
    ofxLayerMask *pattern;
    ofxTriangle triangleCreator;
    
    int designWidth;
    int designHeight;
    int liveWidth;
    int liveHeight;
    ofVec2f designPosition;
    ofVec2f livePosition;
    Canvas* designCanvas;
    Canvas* liveCanvas;
    float x, y;
    
    SafeDeque<DragHandle> dragHandles;
    SafeDeque<MaskPoint> maskPoints;
    
    void findGhostPointIfCloseTo(int absoluteX, int absoluteY);
    void highlightRectIfCloseTo(int absoluteX, int absoluteY);
    void highlightDragHandlesIfCloseTo(int absoluteX, int absoluteY);
    void highlightMaskPointsIfCloseTo(int absoluteX, int absoluteY);
    void unhighlightAllDragHandles();
    void unhighlightAllMaskPoints();
    void selectHighlightedMaskPoint();
    void deselectMaskPoint();
    //void clearBuffer();
    
    void insert(MaskPoint* maskPoint);
    int getInsertionIndex(MaskPoint* maskPoint);
    bool getIntersection(int x, int y, MaskPoint* maskPoint1, MaskPoint* maskPoint2, MaskPoint* intersection);
    
    void initialiseDragHandles();
    void respondToStateChange();
    
    bool containsPositionInRect(int canvasX, int canvasY);
    bool containsPositionInDragHandles(int canvasX, int canvasY);
    bool containsPosition(int canvasX, int canvasY, PointObject* pointObject);
    
    void setRectPosition(int absoluteX, int absoluteY);
    void setLiveRectPosition(int absoluteX, int absoluteY);
    void setRectX(int absoluteX);
    void setRectY(int absoluteY);
    void setLiveRectX(int absoluteX);
    void setLiveRectY(int absoluteY);
    void setDragHandlePositions();
    
    /* Design */
    void setPositionsToMatchScaleChange(int width, int height, Corner movingCorner);
    void setXPositionsToMatchScaleChange(int width);
    void setYPositionsToMatchScaleChange(int height);
    
    void translateMaskPointsX(int amount);
    void translateMaskPointsY(int amount);
    
    int getWidestPointLeftToRight();
    int getWidestPointRightToLeft();
    int getTallestPointTopToBottom();
    int getTallestPointBottomToTop();
    
    /* Live */
    void setLivePositionsToMatchScaleChange(int width, int height, Corner movingCorner);
    void setLiveXPositionsToMatchScaleChange(int width);
    void setLiveYPositionsToMatchScaleChange(int height);
    void translateMaskPointsLiveX(int amount);
    void translateMaskPointsLiveY(int amount);
    int getSmallestLegalLiveWidth(Corner cornerBeingAdjusted);
    int getSmallestLegalLiveHeight(Corner cornerBeingAdjusted);
    int getWidestLivePointLeftToRight();
    int getWidestLivePointRightToLeft();
    int getTallestLivePointTopToBottom();
    int getTallestLivePointBottomToTop();
};