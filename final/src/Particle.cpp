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
//    velocity = _velocity;
//    acceleration = glm::vec2(-0.5, 0.01);
//    acceleration = glm::vec2(0, 0.05);
//    velocity = glm::vec2(ofRandom(-1.0, 1.0), ofRandom(-2.0, 0.0));
    lifespan = 150.0;
}

void Particle::setup() {
    
}

void Particle::update() {
//    velocity = velocity + acceleration;
//    location = location + velocity;
    lifespan = lifespan - 2.0;
    
    path.addVertex(location.x, location.y);
    float radius = ofMap(lifespan, 150.0, 0.0, 0.5, 30.0);
    float angle = ofRandom(ofDegToRad(360.0));
    float distance = ofRandom(25.0);
    float xOffset = cos(angle) * distance;
    float yOffset = sin(angle) * distance;
    circles.push_back(glm::vec3(location.x + xOffset, location.y + yOffset, radius));
    colors.push_back(ofColor(ofRandom(130, 255), ofRandom(100), 0, lifespan));
    
    if (path.size() > 20) {
        path.getVertices().erase(path.begin());
    }
    
    if (circles.size() > 20) {
        circles.erase(circles.begin());
    }
}

void Particle::draw() {
    if (!isDead()) {
        ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 69, 0, lifespan);
        ofDrawCircle(location.x, location.y, 10);
        for (int i = 0; i < circles.size(); i++) {
            ofSetColor(colors.at(i));
            ofDrawCircle(circles.at(i).x, circles.at(i).y, circles.at(i).z);
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
    return lifespan < 0.0;
}
