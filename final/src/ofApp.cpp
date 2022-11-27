#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetDataPathRoot("../Resources/");
  
  gui.setup("", "settings.xml");
  
  gui.add(osc_group);
  gui.add(cam_group);
  gui.add(btn_reset.setup("Apply OSC/Cam Settings"));
  btn_reset.addListener(this, &ofApp::resetCamOsc);
  gui.add(do_group);
  
  gui.loadFromFile("settings.xml");
  
  cam.setDeviceID(cam_id);
  cam.initGrabber(cam_w,cam_h);
  
  sender.setup(osc_host.get(), osc_port.get());
}

//--------------------------------------------------------------
void ofApp::update(){
  cam.update();
  if (cam.isFrameNew()){
    ofPixels & pixels = cam.getPixels();

    if (do_hand) hand.detect(pixels);
    
    
    if (do_hand){
      ofxOscMessage m;
      m.setAddress("/hands/arr");
      m.addIntArg(cam.getWidth());
      m.addIntArg(cam.getHeight());
      m.addIntArg(hand.n_det);
      for (int i = 0; i < hand.n_det; i++){
        m.addFloatArg(hand.scores[i]);
        for (int j = 0; j < HAND_N_PART; j++){
          m.addFloatArg(hand.detections[i][j].x);
          m.addFloatArg(hand.detections[i][j].y);
          m.addFloatArg(hand.detections[i][j].z);
        }
      }
        
      sender.sendMessage(m, false);
    }
  }

  ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.draw(0,0, ofGetWidth(), ofGetHeight());

  if (do_hand){
    ofPushStyle();
    ofSetColor(0,255,255);
    for (int i = 0; i < hand.n_det; i++){
      for (int j = 0; j < HAND_N_PART; j++){
        ofDrawCircle(hand.detections[i][j].x, hand.detections[i][j].y, 5);
      }
    }
    ofPopStyle();
  }
  
  gui.draw();
}

void ofApp::resetCamOsc(){
  cam.setDeviceID(cam_id);
  cam.initGrabber(cam_w,cam_h);
  sender.setup(osc_host.get(), osc_port.get());
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
