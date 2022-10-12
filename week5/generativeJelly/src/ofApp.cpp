#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::black);
    headSegments.addListener(this, &ofApp::headSegmentsChanged);
//    headA.addListener(this, &ofApp::headAChanged);
    headB.addListener(this, &ofApp::headBChanged);
    headC.addListener(this, &ofApp::headCChanged);
    bodyA.addListener(this, &ofApp::bodyAChanged);
    bodyB.addListener(this, &ofApp::bodyBChanged);
    
    gui.setup();
    gui.add(headSegments.set( "headSegments", 32, 8, 128 ));
//    gui.add(headA.set("headA", 1.0, 0.25, 2.0));
    gui.add(headB.set("headB", 0.075, 0.0, 0.3));
    gui.add(headC.set("headC", 10, 0, 20));
    gui.add(bodyA.set("bodyA", 1.0, 0.25, 2.0));
    gui.add(bodyB.set("bodyB", 1.0, 1.0, 1.6));
    
    width = ofGetWidth();
    height = ofGetHeight();
    radius = 0.25*height;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    makeHead();
    makeBody();
    makeMesh();
    makeFatLines();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushView();
    cam.begin();
    ofTranslate(-width/4, height/10);
    ofSetColor(ofColor::white);
//    head.draw();
    for (int i = 0; i < heads.size(); i++) {
        heads[i].draw();
    }
    //    body.draw();
    for (int i = 0; i < bodies.size(); i++) {
        bodies[i].draw();
    }
    ofNoFill();
    ofSetColor(ofColor::red);
      for (int i = 0; i < tentaclePlacements.size(); i++){
        int x = tentaclePlacements[i].x;
        int z = tentaclePlacements[i].y;
        ofDrawCircle(glm::vec3(x,0,z), 5);
      }
    ofTranslate(width/2, 0);
    ofSetColor(ofColor::white);
    for (int i = 0; i < fatlines.size(); i++) {
        fatlines[i].draw();
    }
    ofTranslate(-width/4, -height/2.5);
    mesh.draw();
    ofTranslate(-width/2,0);
    cam.end();
    ofPopView();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::makeFatLines() {
    fatlines.clear();
    ofFloatColor c;
    vector<ofFloatColor> colors;
    vector<double> weights;
    for (int i = 0; i < bodies.size(); i++) {
        bodies[i].close();
        auto vertices = bodies[i].getVertices();
        for (int j = 0; j < vertices.size(); j++) {
            c.setHsb(0.5, 0.5, 1 );
            colors.push_back(c);
            weights.push_back(5);
        }
        ofxFatLine line = ofxFatLine(vertices, colors, weights);
        line.enableFeathering();
        line.setFeather(2);
        line.setJointType(OFX_FATLINE_JOINT_MITER);
        line.setCapType(OFX_FATLINE_CAP_BUTT);
        fatlines.push_back(line);
        colors.clear();
        weights.clear();
    }
    
    for (int i = 0; i < heads.size(); i++) {
        heads[i].close();
        auto vertices = heads[i].getVertices();
        for (int j = 0; j < vertices.size(); j++) {
            c.setHsb(0.3, 0.5, 1 );
            colors.push_back(c);
            weights.push_back(5);
        }
        ofxFatLine line = ofxFatLine(vertices, colors, weights);
        line.enableFeathering();
        line.setFeather(2);
        line.setJointType(OFX_FATLINE_JOINT_MITER);
        line.setCapType(OFX_FATLINE_CAP_BUTT);
        fatlines.push_back(line);
        colors.clear();
        weights.clear();
    }
}

//--------------------------------------------------------------
void ofApp::makeMesh() {
    for (int i = 0; i < bodies.size(); i++) {
//        ofLog() << ofToString(bodies[i].getVertices());
        mesh.addVertices(bodies[i].getVertices());
    }
    for (int i = 0; i < heads.size(); i++) {
        mesh.addVertices(heads[i].getVertices());
    }
}

//--------------------------------------------------------------
void ofApp::makeHead() {
    head.clear();
    heads.clear();
    float steps = PI / headSegments;
    for (float angle = 0; angle < TWO_PI; angle += steps) {
        head.addVertex(makeHeadVertex(angle));
    }
    head.close();
    manyHeads();
    for (int i = 0; i < heads.size(); i++) {
        heads[i].rotateDeg(90, glm::vec3(1,0,0));
    }
    head.rotateDeg(90, glm::vec3(1,0,0));
    int numTentacles = 8;
    ofPoint temp;
    for(float tentaclePos = 0; tentaclePos < TWO_PI; tentaclePos += TWO_PI/numTentacles) {
        temp = makeHeadVertex(tentaclePos);
        tentaclePlacements.push_back(temp);
    }
    
}

void ofApp::makeBody() {
    body.clear();
    bodies.clear();
    float steps = PI / 32;
    // at what angle we should start swopping line back up
    float wrapAngle = PI/2 + steps * 3;
    float smoothRange = steps * 4;
    ofPoint p;

    for (float theta = -PI + steps; theta < PI; theta += steps) {
        //this section draws the most circular top part of the jelly
        if (abs(theta) < wrapAngle) {
            p.x = bodyA*radius * cos(theta - PI/2);
            p.y = -bodyB*1.1*radius * sin(theta - PI/2);
            body.addVertex(p);
        } else {
            // this section draws the tips of the jelly, left and right
            if ((abs(theta) <= wrapAngle + smoothRange + 0.01)) {
                float t = ofMap(abs(theta), wrapAngle, wrapAngle + smoothRange, 0, PI);
                p.x = truncf(bodyA*radius * cos(theta - PI/2));
                p.y = -truncf(bodyB*radius * sin(wrapAngle - PI/2) + 20 * sin(t));
                body.addVertex(p);
            // this section draws the curvy bottom/inner part of the jelly
            } else if (theta > 0) {
                float t = ofMap(abs(theta), wrapAngle + smoothRange, PI, -PI, 0);
                p.x = truncf(0.75 *radius * cos(t - PI))*bodyA*1.05;
                p.y = -truncf(-0.75 * bodyB*radius * bodyB*sin(t - PI) + radius * 0.5);
                body.addVertex(p);
            }
        }
    }
    body.close();
    rotateBody();
}

void ofApp::rotateBody() {
    float step;
    if (headC == 0.0) {
        step = 18;
    } else {
        step = 180/ headC;
    }
//    cout << headC << endl;
    for (float bodyAngle = 0; bodyAngle < 180; bodyAngle += step) {
        body.end();
        bodies.push_back(body.getVertices());
        bodies.back().close();
        body.rotateDeg(bodyAngle, glm::vec3(0, 1, 0));
    }
}

void ofApp::manyHeads() {
    for (float height = 0; height < PI; height+= PI/8/bodyB) {
        heads.push_back(head.getVertices());
        head.translate(glm::vec3(0, 0, -bodyB*20));
        head.scale(cos(height/4), cos(height/4));
    }
}

//--------------------------------------------------------------
ofPoint ofApp::makeHeadVertex(float angle) {
    ofPoint p = ofPoint();
    float wobble = radius * (bodyA + headB * cos(angle * headC));
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
//    cout << x - width/2 << endl;
//    cout << y - height/2 << endl;
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

void ofApp::reset() {
    head.clear();
    body.clear();
    tentaclePlacements.clear();
    mesh.clear();
    fatlines.clear();
    makeHead();
    makeBody();
    makeMesh();
    makeFatLines();
}

//--------------------------------------------------------------
void ofApp::headSegmentsChanged(int & numSegments) {
    reset();
}

//--------------------------------------------------------------
void ofApp::headAChanged(float & num) {
    reset();
}

//--------------------------------------------------------------
void ofApp::headBChanged(float & num) {
    reset();
}

//--------------------------------------------------------------
void ofApp::headCChanged(int & num) {
    reset();
}

//--------------------------------------------------------------
void ofApp::bodyAChanged(float & num) {
    reset();
}

//--------------------------------------------------------------
void ofApp::bodyBChanged(float & num) {
    reset();
}


