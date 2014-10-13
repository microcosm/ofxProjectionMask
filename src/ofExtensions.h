#pragma once
#include "ofMain.h"

enum TransformState { Translating, Scaling, Masking, NoTransform };

void ofCircleStroke(int x, int y, int radius, int stroke, ofColor fillColor, ofColor strokeColor);
void ofCircleNoStroke(int x, int y, int radius, ofColor color);

float clampFloat(float value, float lowerBoundary, float upperBoundary);
int clampInt(int value, int lowerBoundary, int upperBoundary);
int clampInt(int value, int lowerBoundary);
int getNextIndex(int currentIndex, int size);

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

