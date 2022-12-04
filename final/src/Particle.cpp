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
    setup();
}

void Particle::setup() {
    // setup circle drawing
    int scale = 50;
    float resolution = 0.003;
    int numPoints = 100;
    int radius = 160;
    int numRings = 20;
    
    path.setFilled(false);
    path.setStrokeWidth(2);
    path.setStrokeColor(ofColor::black);
    
    for (int r = 0; r < radius; r+= radius/numRings) {
        for(float a = 0.0; a<2*PI; a+=2*PI/numPoints){
            float x = location.x + r*cos(a);
            float y = location.y + r*sin(a);
            float xNoise = ofMap(ofSignedNoise(x*resolution), -1, 1, -scale, scale);
            float yNoise = ofMap(ofSignedNoise(y*resolution), -1, 1, -scale, scale);

//            path.arc(glm::vec2(x+xNoise,y+yNoise), 100, 100, a, a + 2*PI/numPoints);
            
            if (a == 0.0) {
                path.moveTo(glm::vec2(x+xNoise,y+yNoise));
            } else {
                if(ofRandom(0.0, 1.0)>0.8){
                    path.moveTo(glm::vec2(x+xNoise,y+yNoise));
                } else {
                    path.curveTo(glm::vec2(x+xNoise,y+yNoise));
                }
            }
            
        }
        
//        path.close();
    }
    
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
        
        circles.push_back(circle);

//        if (circles.size() > 50) {
//            circles.erase(circles.begin());
//        }
    }
}

void Particle::draw() {
    ofPushStyle();
    if (!isDead()) {
        
        ofEnableAlphaBlending();
        
//        ofSetColor(ofColor(0, 0, 0, 255));
//        for (int i = 0; i < points.size(); i++) {
//            ofDrawCircle(points.at(i).x, points.at(i).y, 4.0);
//        }
        
        path.draw();
        ofDisableAlphaBlending();
        
       
    }
    
    
    ofPopStyle();
}

void Particle::run() {
    update();
    draw();
}

bool Particle::isDead() {
//    return lifespan < 0.0;
    return false;
}
