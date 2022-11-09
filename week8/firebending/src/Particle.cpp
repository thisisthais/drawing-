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
Particle::Particle(glm::vec2 _location, glm::vec2 _velocity) {
    location = _location;
    velocity = _velocity;
    acceleration = glm::vec2(-0.5, 0.01);
//    acceleration = glm::vec2(0, 0.05);
//    velocity = glm::vec2(ofRandom(-1.0, 1.0), ofRandom(-2.0, 0.0));
    lifespan = 255.0;
}

void Particle::setup() {
    
}

void Particle::update() {
    velocity = velocity + acceleration;
    location = location + velocity;
    lifespan = lifespan - 2.0;
    
    path.addVertex(location.x, location.y);
//    circles.push_back(glm::vec3(location.x, location.y, ofRandom(5.0, 20.0)));
//    colors.push_back(ofColor(255, 69, 0, lifespan));
    
    if (path.size() > 20) {
        path.getVertices().erase(path.begin());
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
        ofDisableAlphaBlending();
        
        ofSetColor(ofColor::purple);
        path.draw();
        
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
