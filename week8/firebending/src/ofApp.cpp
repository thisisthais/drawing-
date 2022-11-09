#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.setDeviceID(1);
        cam.initGrabber(640,480);
    #else
        vid.load("kungfu_slow.mp4");
        vid.setVolume(0);
        vid.play();
        vid.setLoopState(OF_LOOP_NORMAL);
    #endif
    
    leftWrist.setup();
    rightWrist.setup();
    
    particle = Particle(glm::vec2(ofGetWidth()/2, ofGetHeight()/2));
    
    gui.setup();
    gui.setPosition(640+50, 50);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.update();
        if (cam.isFrameNew()){
            ofPixels & pixels = cam.getPixels();
            body.detect(pixels);
        }
    #else
        vid.update();
        if (vid.isFrameNew()){
            ofPixels & pixels = vid.getPixels();
            body.detect(pixels);
        }
    #endif
    

    leftWrist.update(body.detections[0][BODY_LEFTWRIST], body.detections[0][BODY_NECK]);
    rightWrist.update(body.detections[0][BODY_RIGHTWRIST], body.detections[0][BODY_NECK]);
    
    particle.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.draw(0,0);
    #else
        vid.draw(0,0);
    #endif
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 99);
//    for (int i = 0; i < body.n_det; i++){
//        for (int j = 0; j < BODY_N_PART; j++){
//            if (body.detections[i][j].z >= 0.5) { /// z is the confidence score
//                ofDrawCircle(body.detections[i][j].x, body.detections[i][j].y, 4);
//            }
//        }
//    }
    
    glm::vec3 LEFT = body.detections[0][BODY_LEFTWRIST];
    glm::vec3 RIGHT = body.detections[0][BODY_RIGHTWRIST];
    glm::vec3 NECK = body.detections[0][BODY_NECK];
    
    if (LEFT.z > 0.5) {
        ofDrawCircle(LEFT.x, LEFT.y, 4);
    }
    
    if (RIGHT.z > 0.5) {
        ofDrawCircle(RIGHT.x, RIGHT.y, 4);
    }
    
    if (NECK.z > 0.5) {
        ofDrawCircle(NECK.x, NECK.y, 4);
    }
    
        
    ofPopStyle();
    
    leftWrist.draw();
    rightWrist.draw();

    particle.draw();
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
