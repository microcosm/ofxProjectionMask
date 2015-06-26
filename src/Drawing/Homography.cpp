#include "Homography.h"

void Homography::begin(ofPoint src[4], ofPoint dst[4]) {

    findHomography(src, dst, transformMatrix);
    glPushMatrix();
    glMultMatrixf(transformMatrix);
    glPushMatrix();
}

void Homography::end() {
    glPopMatrix();
    glPopMatrix();
}