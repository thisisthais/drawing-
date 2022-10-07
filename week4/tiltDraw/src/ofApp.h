#pragma once

#include "ofxiOS.h"
#include "ofxiOSCoreMotion.h"

class ofApp : public ofxiOSApp {
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
        ofNode baseNode;
        ofNode childNode;
        ofNode grandChildNode;
        ofEasyCam cam;
        ofxiOSCoreMotion coreMotion;
        ofVboMesh mesh;
        ofMesh outline;
        ofPolyline line;
    
        unsigned long last;
        int counter;
        ofColor col;
    
        ofFbo screen;
        ofImage photo;
    
        ofVec2f touchPos;
        ofVec2f centerPoint;
        float angle;
    
        bool moving;
};



