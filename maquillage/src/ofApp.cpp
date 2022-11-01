#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    tracker.setup();
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    b_drawPointCloud = false;
    pointCloud.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    
    if (kinect.isFrameNew()){
        tracker.update(kinect);
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw the image on grabber on the upper left corner
//    grabber.draw(0,0);
//    grabber.draw(grabber.getWidth(),0,-grabber.getWidth(),grabber.getHeight());

    
    if (b_drawPointCloud) {

        cam.begin();
        drawPointCloud();
        cam.end();

    } else {
        
        kinect.draw(0, 0, kinect.width, kinect.height);
        tracker.drawDebug();

        kinect.drawDepth(kinect.width, 0, kinect.width, kinect.height);
        
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
