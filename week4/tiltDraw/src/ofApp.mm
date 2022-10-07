#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::white);
    
    baseNode.setPosition(0, 0, 0);
    childNode.setParent(baseNode);
    childNode.setPosition(0, 0, 200);
    grandChildNode.setParent(childNode);
    grandChildNode.setPosition(0,50,0);
    
    coreMotion.setupAccelerometer();
    
    mesh.addVertex(grandChildNode.getGlobalPosition());
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    line.addVertex(grandChildNode.getGlobalPosition());
    outline.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    cam.removeAllInteractions();
    
    last = ofGetElapsedTimeMillis();
    col.setHsb(0,240,250);
    
//    screen.allocate(ofGetWidth(), ofGetHeight());
//
//    screen.begin();
//    ofClear(127,127,127, 255);
//    screen.end();
    
    centerPoint = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    touchPos = centerPoint;
    angle = 0;
    
    moving = true;
}

    

//--------------------------------------------------------------
void ofApp::update(){
    coreMotion.update();
    glm::vec3 acc = coreMotion.getAccelerometerData();
    
    if (moving) {
        baseNode.move(10.0*acc.x, 10.0*acc.y, 0.0);
        
        if(ofGetElapsedTimeMillis() - last > 25) {
            col.setHue(counter % 256);
            counter ++;
            last = ofGetElapsedTimeMillis();
        }
        
//        ofVec2f lineBetween = touchPos - centerPoint;
//        angle = ofRadToDeg(glm::atan(lineBetween.y,lineBetween.x));
//        col.setHue(((angle + 180)*255)/360);
        mesh.addVertex(grandChildNode.getGlobalPosition());
        mesh.addColor(col);
    }
    
//    line.addVertex(grandChildNode.getGlobalPosition());
//    
//    for (int i = 0; i < line.size(); i++){
//            
//        int i_m_1 = i-1;
//        int i_p_1 = i+1;
//        if (i_m_1 < 0) i_m_1 = 0;
//        if (i_p_1 == line.size()) i_p_1 = line.size()-1;
//        ofPoint a = line[i_m_1];
//        ofPoint b = line[i];
//        ofPoint c = line[i_p_1];
//        ofPoint diff  = (c-a).getNormalized();
//        diff = diff.getRotated(90, ofPoint(0, 0, 1));
//        
//        outline.addVertex(b + diff*10);
//        outline.addVertex(b - diff*10);
//        outline.addColor(ofColor::black);
//        outline.addColor(ofColor::black);
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
//    baseNode.draw();
//    childNode.draw();
    grandChildNode.draw();
//    outline.draw();
    mesh.draw();
    
    // accelerometer
//    glm::vec3 a = coreMotion.getAccelerometerData();
//    ofDrawBitmapStringHighlight("Accelerometer: (x,y,z)", 20, 125);
//    ofSetColor(0);
//    ofDrawBitmapString(ofToString(a.x,3), 20, 150);
//    ofDrawBitmapString(ofToString(a.y,3), 120, 150);
//    ofDrawBitmapString(ofToString(a.z,3), 220, 150);
    
//    ofDrawBitmapStringHighlight("touchPos", 0, 0);
//    ofDrawBitmapString(ofToString(touchPos), 0, 10);
    
//    ofDrawBitmapStringHighlight("hue", 0, 30);
//    ofDrawBitmapString(ofToString(((angle + 180)*255)/360), 0, 40);
    
//    ofDrawBitmapStringHighlight("center", 0, 60);
//    ofDrawBitmapString(ofToString(centerPoint), 0, 70);
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    touchPos.x = touch.x;
    touchPos.y = touch.y;
    
    moving = !moving;
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    touchPos.x = touch.x;
    touchPos.y = touch.y;
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
