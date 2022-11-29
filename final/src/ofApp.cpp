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
    gui.add(save_to_file.setup("Save To File"));
    save_to_file.addListener(this, &ofApp::saveToFile);
    gui.add(clear_line.setup("Clear Line"));
    clear_line.addListener(this, &ofApp::clearLine);
    gui.add(create_gesture.setup("Create Gesture"));
    create_gesture.addListener(this, &ofApp::createGesture);
    gui.add(find_btn.setup("Find"));
    find_btn.addListener(this, &ofApp::find);
    gui.add(load_from_file.setup("Load From File"));
    load_from_file.addListener(this, &ofApp::loadFromFile);
  
  gui.loadFromFile("settings.xml");
  
  cam.setDeviceID(cam_id);
  cam.initGrabber(cam_w,cam_h);
  
  sender.setup(osc_host.get(), osc_port.get());
    
    //    one dollar example stuff
    
    num_created_gestures = 0;
    ofBackground(0,0,0);
    createNewGesture();
//    clear_line.setup(this, "clear_line", "Clear line", 785,10);
//    create_gesture.setup(this, "create_gesture", "Create gesture", 785,45);
//    find.setup(this,"find", "Find matching gesture",785,80);
//    save_to_file.setup(this, "save_to_file", "Save to file", 785,115);
//    load_from_file.setup(this, "load_from_file", "Load from file", 785,150);
    mode = 0;
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
            float mirrorX = abs(cam.getWidth() - hand.detections[i][j].x);
          m.addFloatArg(mirrorX);
          m.addFloatArg(hand.detections[i][j].y);
          m.addFloatArg(hand.detections[i][j].z);
        }
      }
        
      sender.sendMessage(m, false);
    }
  }

  ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    //    one dollar example stuff
    
    if(mode == 1 && ofGetElapsedTimeMillis() >= hide_message_on) {
        mode = 0;
        found_gesture.clear();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.draw(cam.getWidth(),0,-cam.getWidth(),cam.getHeight());

  if (do_hand){
    ofPushStyle();
    ofSetColor(0,255,255);
    for (int i = 0; i < hand.n_det; i++){
      for (int j = 0; j < HAND_N_PART; j++){
          float mirrorX = abs(cam.getWidth() - hand.detections[i][j].x);
        ofDrawCircle(mirrorX, hand.detections[i][j].y, 5);
      }
    }
    ofPopStyle();
  }
  
  gui.draw();
    
    save_to_file.draw();
    load_from_file.draw();
    clear_line.draw();
    create_gesture.draw();
    find_btn.draw();

    if(mode == 0) {
        ofPolyline smoothLine = line.getResampledBySpacing(5).getSmoothed(5);
        
//        glColor3f(1.0f, 1.0f, 0.0);
//        glBegin(GL_LINE_STRIP);
//        for(int i = 0; i < smoothLine.size(); ++i) {
//            glVertex2fv(smoothLine[i].getPtr());
//        }
//        glEnd();
        smoothLine.draw();
    }
    else if (mode == 1) {
        glColor3f(1.0f, 0.0f, 0.6f);
        ofDrawBitmapString(message, 10, ofGetHeight()-40);
    }
    
    glColor3f(0.0, 1.0, 0.2);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < found_gesture.size(); ++i) {
        glVertex2fv(found_gesture[i].getPtr());
    }
    glEnd();
    
    glColor3f(1.0f, 1.0f, 0.0f);
    ofDrawBitmapString("Number of gestures: " +ofToString(dollar.gestures.size()), 10, ofGetHeight()-25);
    ofDrawBitmapString("Name of current gesture: " +gesture->name, 10, ofGetHeight()-10);
}

void ofApp::resetCamOsc(){
  cam.setDeviceID(cam_id);
  cam.initGrabber(cam_w,cam_h);
  sender.setup(osc_host.get(), osc_port.get());
}

void ofApp::saveToFile() {
    dollar.save(ofToDataPath("gestures.txt",true));
    showMessage("Saved!");
}

void ofApp::clearLine() {
    line.clear();
}

void ofApp::createGesture() {
    // Add all the point we've just drawn to the gesture. This creates a "gesture".
    gesture->reset();
    for(int i = 0; i < line.size(); ++i) {
        gesture->addPoint(line[i].x, line[i].y);
    }
    
    if(gesture->points.size() <= 10) {
        message = "Please add a line first";
    }
    else {
        dollar.addGesture(gesture);
        message = "Added gesture to recognizer";
        line.clear();
        createNewGesture();
    }
    showMessage(message, 800);
    line.clear();
}

void ofApp::find() {
    // find the gesture which matches the current line.
    ofxGesture* tmp = new ofxGesture();
    for(int i = 0; i < line.size(); ++i) {
        tmp->addPoint(line[i].x, line[i].y);
    }
    line.clear();
    double score = 0.0;
    ofxGesture* match = dollar.match(tmp, &score);
    string result = "Matching score: " +ofToString(score);
    if(match != NULL) {
        result +=", which matches with gesture: " +match->name;
        found_gesture.clear();
        float dx = ofGetWidth()/2;
        float dy = ofGetHeight()/2;
        for(int i = 0; i < match->resampled_points.size(); ++i) {
            found_gesture.push_back(ofVec2f(dx+match->resampled_points[i].x, dy+match->resampled_points[i].y));
        }
    }
    showMessage(result, 1500);
    delete tmp;
}

void ofApp::loadFromFile() {
    dollar.load(ofToDataPath("gestures.txt",true));
    showMessage("Loaded! Note that saved gestures are rotated to the optimal position!",4000);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 32) { // space bar
        ofVec3f fingertip = hand.detections[0][HAND_INDEX3];
        if(mode == 0 && fingertip.z > 0.5) { // z is confidence
            float mirrorX = abs(cam.getWidth() - fingertip.x);
            line.addVertex(ofPoint(mirrorX,fingertip.y));
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(mode == 0) {
        line.addVertex(ofPoint(x, y));
    }
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

void ofApp::showMessage(string sMessage, int nDelay) {
    message = sMessage;
    mode = 1;
    hide_message_on = ofGetElapsedTimeMillis() + nDelay;
}

void ofApp::createNewGesture() {
    ++num_created_gestures;
    gesture = new ofxGesture();
    gesture->setName("Gesture#" +ofToString(num_created_gestures));
}

