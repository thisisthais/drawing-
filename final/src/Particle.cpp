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
    lifespan = 160.0;
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
        bool bFirstPoint = true;
        for(int i = 0; i <= numPoints; i++){
            float a = ofMap(i, 0, numPoints-1, 0, TWO_PI);

            float x = location.x + r*cos(a);
            float y = location.y + r*sin(a);
            float xNoise = ofMap(ofSignedNoise(x*resolution), -1, 1, -scale, scale);
            float yNoise = ofMap(ofSignedNoise(y*resolution), -1, 1, -scale, scale);

            if (bFirstPoint == true){
                bFirstPoint = false;
                path.moveTo(glm::vec2(x+xNoise,y+yNoise));
            } else {
                path.curveTo(glm::vec2(x+xNoise,y+yNoise));
            }


            if(ofRandom(0.0, 1.0)>0.75-0.25*sin(r)){
                path.newSubPath();
                path.moveTo(glm::vec2(x+xNoise,y+yNoise));
            }
        }
   }
}

void Particle::update() {
    if (lifespan > 0.0) {
        lifespan = lifespan - 0.9*ofGetElapsedTimef();
    }
}

void Particle::draw() {
    ofPushStyle();
    
    ofEnableAlphaBlending();
    
//    path.draw();
    
    vector<ofPolyline> lines = path.getOutline();
    
    // draws each line based on pct
    
    for (int i = 0; i < lines.size(); i++){
        float pct = ofMap(lifespan, 160.0, 0.0, 0.0, 1.0, true);
        ofLog() << pct;
        ofPolyline newLine;
        for (int j = 0; j < lines[i].size(); j++){
            float pctj = ofMap(j, 0, lines[i].size()-1, 0, 1);
            if (pctj < pct){
                newLine.addVertex(lines[i][j]);
            }
        }
        newLine.draw();
    }
    
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
