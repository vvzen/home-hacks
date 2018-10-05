// Based on the original example by Christopher Baker
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
// SPDX-License-Identifier:	MIT

#include "ofApp.h"


void ofApp::setup(){

    ofSetFrameRate(DESIRED_FRAME_RATE);

    // get a list of the available input video devices
    vector<ofVideoDevice> devices = grabber.listDevices();

    for (auto device : devices){
        if (device.bAvailable){
            ofLogNotice() << device.id << ": " << device.deviceName;
        }
        else {
            ofLogNotice() << device.id << ": " << device.deviceName << " - unavailable";
        }
    }

    // setup the webcam stream
    grabber.setDeviceID(0);
    grabber.setDesiredFrameRate(DESIRED_FRAME_RATE);
    grabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);

    grayscale_img.allocate(CAM_WIDTH, CAM_HEIGHT);
    color_img.allocate(CAM_WIDTH, CAM_HEIGHT);

    ofSetVerticalSync(true);

    ofxHTTP::SimpleIPVideoServerSettings settings;

    // Many other settings are available.
    settings.setPort(7890);

    // The default maximum number of client connections is 5.
    settings.ipVideoRouteSettings.setMaxClientConnections(3);

    // Apply the settings.
    server.setup(settings);

    // Start the server.
    server.start();

#if !defined(TARGET_LINUX_ARM)
    // Launch a browser with the address of the server.
    ofLaunchBrowser(server.url());
#endif

}


void ofApp::update(){
    
    // Update the webcam stream
    grabber.update();

    // If the frame is new, then send it to the server to be broadcast.
    if (grabber.isFrameNew()){

        color_img.setFromPixels(grabber.getPixels());
        grayscale_img = color_img;
        grayscale_img.mirror(false, true);
        server.send(grayscale_img.getPixels());
    }
}


void ofApp::draw(){

    // Draw the video on the server screen.
    grayscale_img.draw(0,0);

    // Display the number of connected clients for reference.
    std::stringstream ss;

    ss << "Num clients connected: ";
    ss << server.numConnections();

    ofDrawBitmapStringHighlight(ss.str(), 20, 20);
}
