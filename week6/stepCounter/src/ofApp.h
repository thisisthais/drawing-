#pragma once

#include "ofxiOS.h"
#include "ofxiOSCoreMotion.h"
#include "ofxAnimatableFloat.h"

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
    
        ofxiOSCoreMotion coreMotion;
        std::deque<float> accMagnitudes;
        float sumMagnitudes;
        float meanMagnitude;
        std::deque<float> deviationMagnitudes;
        int steps;
        int inchesTravelled;
        
        ofxAnimatableFloat ballHeight;
        ofPoint ballLocation;
        ofPoint fingerLocation;
        ofPolyline touchPoints;
};


