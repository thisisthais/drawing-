#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    faceTracker.setup();
    contourFinder.setSortBySize(true);
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    ofSetWindowShape(kinect.width*2, kinect.height*2);
    
    ofxCv::imitate(background, kinect);
    ofxCv::imitate(diff, kinect);
    ofxCv::imitate(thresholdImage, kinect);
    
    ofSetLineWidth(3);
    
    gui.setup();
    gui.add(thresh.setup("Threshhold", 10, 0, 255));
    gui.add(minRadius.setup("Min Radius", 10, 0, 400));
    gui.add(maxRadius.setup("Max Radius", 200, 0, 400));
    
    b_drawPointCloud = false;
    useDepthPixels = false;
    pointCloud.setMode(OF_PRIMITIVE_POINTS);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    contourFinder.setMinAreaRadius(minRadius);
    contourFinder.setMaxAreaRadius(maxRadius);
    contourFinder.setThreshold(thresh);
    
    kinect.update();
    
    if (kinect.isFrameNew()){
        faceTracker.update(kinect);
        
        depthPixels = kinect.getDepthPixels();
        // absdiff(ofImage x, ofImage y, ofImagez)
        // calculate the absolute difference between x and y
        // and assigns it to z
        if (useDepthPixels) {
            ofxCv::absdiff(depthPixels, background, diff);
        } else {
            ofxCv::absdiff(kinect, background, diff);
            ofxCv::convertColor(diff, thresholdImage, CV_RGB2GRAY);
        }
        // when we do an ofxCv operation on an image,
        // we have to update it
        // this operation happens on the graphics card
        diff.update();
        
        ofxCv::threshold(thresholdImage, thresh);
        thresholdImage.update();
        
        
        // find the contours on the ofImage diff
        contourFinder.findContours(diff);

    }
    
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw the image on grabber on the upper left corner
//    grabber.draw(0,0);
//    grabber.draw(grabber.getWidth(),0,-grabber.getWidth(),grabber.getHeight());
    
//    ofxCv::RectTracker& contourTracker = contourFinder.getTracker();

    
    if (b_drawPointCloud) {

        cam.begin();
        drawPointCloud();
        cam.end();

    } else {
        
//        kinect.draw(0, 0, kinect.width, kinect.height);
//        faceTracker.drawDebug();
//
//        kinect.drawDepth(kinect.width, 0, kinect.width, kinect.height);
        


        if (useDepthPixels) {
            kinect.drawDepth(0, 0);
        } else {
            kinect.draw(0, 0);
        }
        background.draw(kinect.width, 0);
        diff.draw(0, kinect.height);
        thresholdImage.draw(kinect.width, kinect.height);
        
        contourFinder.draw();


        gui.draw();
        
    }
    
}

void ofApp::drawPointCloud() {
    
    pointCloud.clear();
    
    for (int y = 0; y < kinect.width; y++) {
        for (int x = 0; x < kinect.height; x++) {
            pointCloud.addVertex(kinect.getWorldCoordinateAt(x, y));
            pointCloud.addColor(kinect.getColorAt(x,y));
        }
    }
    
    glPointSize(3);
    ofEnableDepthTest();
    ofPushMatrix();
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000);
    pointCloud.drawVertices();
    
    ofPopMatrix();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'p':
            b_drawPointCloud = !b_drawPointCloud;
            break;
        case ' ':
            // copy the content from kinect camera to background
            ofxCv::copy(kinect, background);
            // update the ofImage we did an ofxCv operation on
            background.update();
            break;
        case 'd':
            useDepthPixels = !useDepthPixels;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
