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
    makeBody();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushView();
    ofTranslate(width/2, height/2);
    ofSetColor(ofColor::white);
//    head.draw();
    body.draw();
    ofSetColor(ofColor::red);

//    ofNoFill();
//      for (int i = 0; i < tentaclePlacements.size(); i++){
//        int x = tentaclePlacements[i].x;
//        int y = tentaclePlacements[i].y;
//        ofDrawCircle(x, y, 5);
//      }
    
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

void ofApp::makeBody() {
    body.clear();
    float steps = PI / headSegments;
    // at what angle we should start swopping line back up
    float wrapAngle = PI/2 + steps * 3;
    float smoothRange = steps * 4;
    ofPoint p;

    for (float theta = -PI + steps; theta < PI; theta += steps) {
        
        //this section draws the most circular top part of the jelly
        if (abs(theta) < wrapAngle) {
            p.x = radius * cos(theta - PI/2);
            p.y = radius * sin(theta - PI/2);
            body.addVertex(p);
        } else {
            // this section draws the tips of the jelly, left and right
            if ((abs(theta) <= wrapAngle + smoothRange + 0.01)) {
                float t = ofMap(abs(theta), wrapAngle, wrapAngle + smoothRange, 0, PI);
                p.x = truncf(radius * cos(theta - PI/2));
                p.y = truncf(radius * sin(wrapAngle - PI/2) + 20 * sin(t));
                body.addVertex(p);
            // this section draws the curvy bottom/inner part of the jelly
            } else if (theta > 0) {
                float t = ofMap(abs(theta), wrapAngle + smoothRange, PI, -PI, 0);
                p.x = truncf(0.75 * radius * cos(t - PI));
                p.y = truncf(-0.75 * radius * sin(t - PI) + radius * 0.5);
                body.addVertex(p);
            }
        }
        body.close();
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
ofPoint ofApp::makeBodyVertex(float angle) {
    ofPoint p = ofPoint();
    p.x = radius * cos(angle - PI/2);
    p.y = radius * sin(angle - PI/2);
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
    cout << x - width/2 << endl;
    cout << y - height/2 << endl;
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

