//
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxHTTP.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"


class ofApp: public ofBaseApp {

public:
    void setup() override;
    void update() override;
    void draw() override;

    ofxHTTP::SimpleIPVideoServer server;

    ofVideoPlayer player;
    ofVideoGrabber grabber;

    ofxCvGrayscaleImage grayscale_img;
    ofxCvColorImage color_img;

    const int DESIRED_FRAME_RATE = 15;
    const int CAM_WIDTH = 640;
    const int CAM_HEIGHT = 480;
};
