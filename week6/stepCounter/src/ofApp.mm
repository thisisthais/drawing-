#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofDisableArbTex();
    
    coreMotion.setupMagnetometer();
    coreMotion.setupGyroscope();
    coreMotion.setupAccelerometer();
    coreMotion.setupAttitude(CMAttitudeReferenceFrameXMagneticNorthZVertical);
    
    steps = 0;
    sumMagnitudes = 0;
    meanMagnitude = 0;
    inchesTravelled = 0;
    
    ballLocation = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    debugView = false;
    showTitleScreen = true;
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB, 0);
    retroComputer.load("retro_computer.ttf", 64);
    shader.load("shader.vert", "shader.frag");
    chalk.load("chalk.jpg");
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
    
    ofVec2f diff = fingerLocation - ballLocation;
    diff.normalize();
    float processedMagnitude = 0.0;
    
    if (accMagnitudes.back() >= 0.02) {
        processedMagnitude = accMagnitudes.back();
    }
    
    if (processedMagnitude >= 1.0) {
        processedMagnitude = 1.0;
    }
    
    ballLocation += diff*processedMagnitude*10.0;
    // name writing challenge
    ballLine.addVertex(ballLocation.x, ballLocation.y);
    lineMagnitudes.push_back(accMagnitudes.back());
    fingerLocation = ballLocation;
    
    float time = ofGetElapsedTimeMillis();
    if (time > 3000) {
        if (time > 7000) {
            showTitleScreen = false;
        } else {
            if (remainder(time, 1000.0) > 0) {
                showTitleScreen = true;
            } else {
                showTitleScreen = false;
            }
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (debugView) {
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
        
        ofSetCircleResolution(100);
        ofDrawCircle(ballLocation.x, ballLocation.y, 20);
        
        ofSetColor(ofColor::black);
        float barWidth = ofGetWidth()/accMagnitudes.size();
        for (int i = 0; i < accMagnitudes.size(); i++) {
            ofDrawRectangle(i*barWidth, ofGetHeight() - 300, barWidth, -accMagnitudes[i]*200.0);
        }
    }
    
    
    ballLine.getSmoothed(2);
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for (int i = 0; i < ballLine.size(); i++){
            
            int i_m_1 = i-1;
            int i_p_1 = i+1;
            if (i_m_1 < 0) i_m_1 = 0;
            if (i_p_1 == ballLine.size()) i_p_1 = ballLine.size()-1;
            ofPoint a = ballLine[i_m_1];
            ofPoint b = ballLine[i];
            ofPoint c = ballLine[i_p_1];
            ofPoint diff  = (c-a).getNormalized();
            diff = diff.getRotated(90, ofPoint(0, 0, 1));
            
            float lineWidth = ofMap(lineMagnitudes[i], 0.0, 2.0, 5, 50);
            mesh.addVertex(b + diff*lineWidth);
            mesh.addVertex(b - diff*lineWidth);
            mesh.addColor(ofColor::white);
            mesh.addColor(ofColor::white);
            
        }
    
    fbo.begin();
        mesh.draw();
    fbo.end();
    
    shader.begin();
    shader.setUniform1f("screenHeight", ofGetHeight());
    shader.setUniform1f("screenWidth", ofGetWidth());
    shader.setUniformTexture("chalkImg", chalk.getTexture(), 0);
    shader.setUniformTexture("fbo", fbo.getTexture(), 1);
    shader.setUniform2f("textureInternal",fbo.getTexture().getCoordFromPoint(fbo.getWidth(), fbo.getHeight()));

    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    
    ofSetColor(ofColor::red);
    if (showTitleScreen) {
        retroComputer.drawString("YOU", ofGetWidth()/4 - 35, ofGetHeight()/2 - 180);
        retroComputer.drawString("MUST", ofGetWidth()/4 - 35 , ofGetHeight()/2 - 80);
        retroComputer.drawString("RUN", ofGetWidth()/4 - 35, ofGetHeight()/2 + 20);
    }
    ofDrawCircle(fingerLocation.x, fingerLocation.y, 20);
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
