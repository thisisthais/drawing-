//
//  Wrist.cpp
//  firebending
//
//  Created by Thaís Xisto on 11/8/22.
//

#include <stdio.h>
#include "Wrist.h"
Wrist::Wrist() {
    
}

void Wrist::setup() {

}

void Wrist::update(glm::vec3 _detection, glm::vec3 _neckDetection) {
    if (ofGetElapsedTimef() <= 0.5) { // first time changing detection
        detection = _detection;
        neckDetection = _neckDetection;
    } else {
        detection = detection * 0.7 + _detection*0.3;
        neckDetection = neckDetection * 0.7 + _neckDetection*0.3;
    }
    x = detection.x;
    y = detection.y;
    confidence = detection.z;
    
    if (confidence > 0.5) {
        path.addVertex(x, y);
        
        if (path.size() > 1) {
            ofPoint prev = path[path.size() - 2];
            ofPoint curr = path[path.size() - 1];
            
            glm::vec2 vel = glm::vec2(curr.x, curr.y) - glm::vec2(prev.x, prev.y);
            if (vel.length() > 0 && vel.length() < 10000) {
                velocities.push_back(vel);
            }
            
            if (velocities.size() > 1) {
                glm::vec2 prev = velocities.at(velocities.size() - 2);
                glm::vec2 curr = velocities.back();
                
                glm::vec2 acc = curr - prev;
                accels.push_back(acc);
                
                if (neckDetection.z > 0.4) {
                    ofPoint diff = ofPoint(x, y) - ofPoint(neckDetection.x, neckDetection.y);
                    float angle = atan2f(diff.x, diff.y) * RAD_TO_DEG;
//                    ofLog() << angle;
//
                    // get just the integer part of the magnitude of acceleration
                    float whole = 1.;
                    modf(glm::length(acc), &whole);
    //                ofLog() << whole;
                    
                    float xDiff = abs(x - neckDetection.x);
                    if (whole == 0 && abs(angle) > 70.0 && abs(angle) < 100.0 && xDiff > 100.0) {
                        particles.push_back(Particle(glm::vec2(x, y), vel));
                    }
                }
            }
        }
        
    }
    
    if (path.size() > 100) {
        path.getVertices().erase(path.begin());
    }
    
    if (velocities.size() > 1000) {
        velocities.erase(velocities.begin());
    }
    
}

void Wrist::draw() {
    if (confidence > 0.5) {
        ofPushStyle();
        
//        glm::vec2 acc;
//        if (accels.size() > 0) {
//            acc = accels.back();
//        } else {
//            acc = glm::vec2(-1, -1);
//        }
//
//        // get just the integer part of the magnitude of acceleration
//        float whole = 1.;
//        modf(glm::length(acc), &whole);
//
//        if (whole == 0) {
//            ofSetColor(ofColor::red);
//        } else {
//            ofSetColor(ofColor::blue);
//        }
        ofSetColor(ofColor::blue);
//        ofDrawCircle(x, y, 20);
        ofPopStyle();
    }
    
    ofLog() << particles.size();
    for (int i = particles.size() - 1; i >= 0 ; i--) {
        if (particles.at(i).isDead()) {
            particles.erase(particles.begin() + i);
        } else {
            particles.at(i).run();
        }
    }
}
