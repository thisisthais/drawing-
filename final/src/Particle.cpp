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
    lifespan = 160;
    setup();
}

void Particle::setup() {
    // setup circle drawing
    int scale = 50;
    float resolution = 0.004;
    int numPoints = 100;
    int radius = 160;
    int numRings = 30;
    
    path.setFilled(false);
    path.setStrokeWidth(2);
    path.setStrokeColor(ofColor::black);
    
    for (int r = 0; r < radius; r+= radius/numRings) {
        path.newSubPath();
        for(float a = 0.0; a<=2*PI; a+=2*PI/numPoints){
            float x = location.x + r*cos(a);
            float y = location.y + r*sin(a);
            float xNoise = ofMap(ofSignedNoise(x*resolution), -1, 1, -scale, scale);
            float yNoise = ofMap(ofSignedNoise(y*resolution), -1, 1, -scale, scale);

            path.curveTo(glm::vec2(x+xNoise,y+yNoise));
            
            if(ofRandom(0.0, 1.0)>0.75-0.25*sin(r)){
                path.newSubPath();
                path.moveTo(glm::vec2(x+xNoise,y+yNoise));
            }
        }
        path.newSubPath();
    }
}

void Particle::update() {
    if (lifespan > 0) {
        lifespan = lifespan - 1;
        
        float pathPercentage = ofMap(lifespan, 160, 0, 0.0, 1.0);
//        vector<Command> commands = path.getCommands();
//        ofLog() << commands.size();
    }
}

void Particle::draw() {
    ofPushStyle();
    
    ofEnableAlphaBlending();
    
    path.draw();
    
    ofDisableAlphaBlending();
    
    ofPopStyle();
}

void Particle::run() {
    update();
    draw();
}

bool Particle::isDone() {
    return false;
//    return lifespan < 0;
}
