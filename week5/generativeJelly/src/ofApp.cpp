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
    
    float steps = PI / headSegments;
    for (float angle = 0; angle < TWO_PI; angle += steps) {
        head.addVertex(makeHeadVertex(angle));
    }
    
    head.draw();
}

//--------------------------------------------------------------
void ofApp::update(){
    float steps = PI / headSegments;
    for (float angle = 0; angle < TWO_PI; angle += steps) {
        head.addVertex(makeHeadVertex(angle));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushView();
    ofTranslate(width/2, height/2);
    head.draw();
    ofPopView();
    
    gui.draw();
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
    cout << numSegments << endl;
}

//--------------------------------------------------------------
void ofApp::headAChanged(float & num) {
    head.clear();
}

//--------------------------------------------------------------
void ofApp::headBChanged(float & num) {
    head.clear();
}

//--------------------------------------------------------------
void ofApp::headCChanged(int & num) {
    head.clear();
}

