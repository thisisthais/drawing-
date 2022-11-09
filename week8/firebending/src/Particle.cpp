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
Particle::Particle(glm::vec2 _location) {
    location = _location;
//    acceleration = glm::vec2(0, 0);
//    velocity = glm::vec2(0, 0);
    acceleration = glm::vec2(0, 0.05);
    velocity = glm::vec2(ofRandom(-1.0, 1.0), ofRandom(-2.0, 0.0));
    lifespan = 255;
}

void Particle::setup() {
    
}

void Particle::update() {
    velocity = velocity + acceleration;
    location = location + velocity;
    lifespan = lifespan - 1;
}

void Particle::draw() {
    if (!isDead()) {
        ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 69, 0, lifespan);
        ofDrawCircle(location.x, location.y, 10);
        ofDisableAlphaBlending();
        ofPopStyle();
    }
}

bool Particle::isDead() {
    return lifespan < 0.0;
}
