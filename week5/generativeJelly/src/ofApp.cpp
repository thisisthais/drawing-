#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    headSegments.addListener(this, &ofApp::headSegmentsChanged);
    
    gui.setup();
    gui.add(headSegments.set( "headSegments", 32, 8, 128 ));
    
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
    float wobble = radius * (1 + 0.075 * cos(angle * 10));
    p.x = wobble * cos(angle - PI/2);
    p.y = wobble * sin(angle - PI/2);
    return p;
}

//--------------------------------------------------------------
void ofApp::headSegmentsChanged(int & numSegments) {
    head.clear();
    cout << numSegments << endl;
    
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
