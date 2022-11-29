//
//  Particle.cpp
//  firebending
//
//  Created by Thaís Xisto on 11/9/22.
//

#include <stdio.h>
#include "Particle.h"
Particle::Particle() {
    
}
Particle::Particle(glm::vec2 _location, string _gestureName) {
    location = _location;
    gestureName = _gestureName;
    lifespan = 150.0;
}

void Particle::setup() {
    
}

void Particle::update() {
    lifespan = lifespan - 1.0;
    
    if (lifespan > 0.0) {
        float radius = ofMap(lifespan, 150.0, 0.0, 0.5, 30.0)*5.0;
        ofPath circle;
        circle.arc(location, radius, radius, 0, 360);
        circle.close();
        circle.arc(location, radius - 2.0, radius - 2.0, 0, 360);
        if (gestureName == "Gesture#1") {
            circle.setColor(ofColor(ofRandom(130, 255), ofRandom(100), 0, lifespan));
        } else if (gestureName == "Gesture#2") {
            circle.setColor(ofColor(ofRandom(100), ofRandom(130, 255), 0, lifespan));
        } else {
            circle.setColor(ofColor(ofRandom(50), ofRandom(50), ofRandom(50), lifespan));
        }
        
        circles2.push_back(circle);
    //    float angle = ofRandom(ofDegToRad(360.0));
    //    float distance = ofRandom(100.0);
    //    float xOffset = cos(angle) * distance;
    //    float yOffset = sin(angle) * distance;
    //    circles.push_back(glm::vec3(location.x + xOffset, location.y + yOffset, radius));
    //    colors.push_back(ofColor(ofRandom(130, 255), ofRandom(100), 0, 128));
        
    //
        if (circles.size() > 50) {
            circles.erase(circles.begin());
        }
    }
}

void Particle::draw() {
    if (!isDead()) {
        ofPushStyle();
        ofEnableAlphaBlending();
//        ofSetColor(255, 69, 0, lifespan);
//        ofDrawCircle(location.x, location.y, 10);
//        for (int i = 0; i < circles.size(); i++) {
//            ofSetColor(colors.at(i));
//            ofDrawCircle(circles.at(i).x, circles.at(i).y, circles.at(i).z);
//        }
        for (int i = 0; i < circles2.size(); i++) {
            circles2.at(i).draw();
        }
        ofDisableAlphaBlending();
        
//        ofSetColor(ofColor::purple);
//        path.draw();
        
        ofPopStyle();
    }
}

void Particle::run() {
    update();
    draw();
}

bool Particle::isDead() {
//    return lifespan < 0.0;
    return false;
}
