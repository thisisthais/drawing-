#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    headSegments.addListener(this, &ofApp::headSegmentsChanged);
    headA.addListener(this, &ofApp::headAChanged);
    headB.addListener(this, &ofApp::headBChanged);
    headC.addListener(this, &ofApp::headCChanged);
    
    gui.setup();
    gui.add(headSegments.set( "headSegments", 32, 8, 128 ));
    gui.add(headA.set("headA", 1.0, 0.0, 4.0));
    gui.add(headB.set("headB", 0.075, 0.0, 0.3));
    gui.add(headC.set("headC", 10, 0, 20));
    
    width = ofGetWidth();
    height = ofGetHeight();
    radius = 0.25*height;
    
    makeHead();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofPolyline bodyLeft;
    ofPolyline bodyRight;
    ofPoint tempPoint;
//    for (float theta = 0; theta < PI; theta += steps) {
//        tempPoint = makeHeadVertex(theta);
//        bodyLeft.addVertex(tempPoint);
//        tempPoint.x = -tempPoint.x;
//        bodyRight.addVertex(tempPoint);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushView();
    ofTranslate(width/2, height/2);
    ofSetColor(ofColor::white);
    head.draw();
    ofSetColor(ofColor::red);

    ofNoFill();
      int n = 30;
      for (int i = 0; i < tentaclePlacements.size(); i++){
        int x = tentaclePlacements[i].x;
        int y = tentaclePlacements[i].y;
        ofDrawCircle(x, y, 5);
      }
    ofPopView();

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::makeHead() {
    head.clear();
    float steps = PI / headSegments;
    for (float angle = 0; angle < TWO_PI; angle += steps) {
        head.addVertex(makeHeadVertex(angle));
    }
    int numTentacles = 8;
    for(float tentaclePos = 0; tentaclePos < TWO_PI; tentaclePos += TWO_PI/numTentacles) {
        tentaclePlacements.push_back(makeHeadVertex(tentaclePos));
    }
}

//--------------------------------------------------------------
ofPoint ofApp::makeHeadVertex(float angle) {
    ofPoint p = ofPoint();
    float wobble = radius * (headA + headB * cos(angle * headC));
    p.x = wobble * cos(angle - PI/2);
    p.y = wobble * sin(angle - PI/2);
    return p;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

//--------------------------------------------------------------
void ofApp::headSegmentsChanged(int & numSegments) {
    head.clear();
    tentaclePlacements.clear();
    makeHead();
}

//--------------------------------------------------------------
void ofApp::headAChanged(float & num) {
    head.clear();
    tentaclePlacements.clear();
    makeHead();
}

//--------------------------------------------------------------
void ofApp::headBChanged(float & num) {
    head.clear();
    tentaclePlacements.clear();
    makeHead();
}

//--------------------------------------------------------------
void ofApp::headCChanged(int & num) {
    head.clear();
    tentaclePlacements.clear();
    makeHead();
}

