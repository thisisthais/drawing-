#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	
    ofBackground(255);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    coreMotion.setupMagnetometer();
    coreMotion.setupGyroscope();
    coreMotion.setupAccelerometer();
    coreMotion.setupAttitude(CMAttitudeReferenceFrameXMagneticNorthZVertical);
    
    steps = 0;
    sumMagnitudes = 0;
    meanMagnitude = 0;
    inchesTravelled = 0;
    
    ballHeight.reset(ofGetHeight() - 100);
    ballHeight.setCurve(LINEAR);
//    ballHeight.setRepeatType(LOOP_BACK_AND_FORTH);
    ballHeight.setDuration(0.2);
    
    ballLocation = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
void ofApp::update(){
    coreMotion.update();
    
    glm::vec3 m = coreMotion.getUserAcceleration();
    int accSize = accMagnitudes.size();
    float magnitude = sqrt(m.x*m.x + m.y*m.y + m.z*m.z);
    accMagnitudes.push_back(magnitude);
    if (accSize >= 300) {
        sumMagnitudes -= accMagnitudes.front();
        accMagnitudes.pop_front();
        deviationMagnitudes.pop_front();
        
    }
    sumMagnitudes += magnitude;
    meanMagnitude = sumMagnitudes / accMagnitudes.size();
    float stdDevSum = 0;
    for (int i = 0; i < accMagnitudes.size(); i++) {
        stdDevSum += pow(accMagnitudes[i] - meanMagnitude, 2);
    }
    
    deviationMagnitudes.push_back(sqrt(stdDevSum/accMagnitudes.size()));
    
    if (accSize > 3) {
        float m_after = accMagnitudes.back();
        float m_middle = accMagnitudes.at(accSize - 2);
        float m_before = accMagnitudes.at(accSize - 3);
        
        if (m_middle > m_before && m_middle > m_after && m_middle > meanMagnitude + deviationMagnitudes.back()) {
            steps++;
        }
    }
    
    inchesTravelled = steps * 27;
    float targetHeight = ofMap(sin(inchesTravelled/500.0), -1, 1,  ofGetHeight() - 100, 100);
    ballHeight.animateTo(targetHeight);
    
//    float dt = 1.0f * (sin(inchesTravelled) + 1) / 60.0f;
    float dt = 1.0f / 60.0f;
    ballHeight.update(dt);
    
    ofVec2f diff = fingerLocation - ballLocation;
    diff.normalize();
    ballLocation += diff*accMagnitudes.back()*10.0; // threshold this so below a certain amount it doesn't move at all
    // also try average acceleration of last 10 points
    // name writing challenge
    touchPoints.addVertex(ballLocation.x, ballLocation.y);
    fingerLocation = ballLocation;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // accelerometer
    glm::vec3 a = coreMotion.getAccelerometerData();
    ofDrawBitmapStringHighlight("Accelerometer: (x,y,z)", 20, 125);
    ofSetColor(0);
    ofDrawBitmapString(ofToString(a.x,3), 20, 150);
    ofDrawBitmapString(ofToString(a.y,3), 120, 150);
    ofDrawBitmapString(ofToString(a.z,3), 220, 150);
    
    // user acceleration
    glm::vec3 m = coreMotion.getUserAcceleration();
    ofDrawBitmapStringHighlight("User Acceleration: (x,y,z)", 20, 225);
    ofSetColor(0);
    ofDrawBitmapString(ofToString(m.x,3), 20, 250);
    ofDrawBitmapString(ofToString(m.y,3), 120, 250);
    ofDrawBitmapString(ofToString(m.z,3), 220, 250);
    
    ofDrawBitmapStringHighlight("Mean magnitude: (x,y,z)", 20, 325);
    ofSetColor(0);
    ofDrawBitmapString(ofToString(meanMagnitude,3), 20, 350);
    
    ofDrawBitmapStringHighlight("Steps: (x,y,z)", 20, 525);
    ofSetColor(0);
    ofDrawBitmapString(ofToString(steps,1), 20, 550);
    
    ofDrawBitmapStringHighlight("Inches travelled", 20, 725);
    ofSetColor(0);
    ofDrawBitmapString(ofToString(inchesTravelled,1), 20, 750);
    
    ofDrawBitmapStringHighlight("Target", 20, 925);
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ballHeight.getTargetValue(),2), 20, 950);
    
    float height = ofGetHeight();
    ofSetCircleResolution(100);
    ofDrawCircle(ballLocation.x, ballLocation.y, 20);
    
    ofSetColor(ofColor::black);
    float barWidth = ofGetWidth()/accMagnitudes.size();
    for (int i = 0; i < accMagnitudes.size(); i++) {
        ofDrawRectangle(i*barWidth, ofGetHeight() - 300, barWidth, -accMagnitudes[i]*200.0);
    }
    
    ofSetColor(ofColor::red);
    ofDrawCircle(fingerLocation.x, fingerLocation.y, 20);
    
    ofSetColor(ofColor::blue);
    touchPoints.getResampledByCount(2);
    touchPoints.getSmoothed(2);
    touchPoints.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    fingerLocation = ofPoint(touch.x, touch.y);
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    fingerLocation = ofPoint(touch.x, touch.y);
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    fingerLocation = ofPoint(ballLocation.x, ballLocation.y);
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
