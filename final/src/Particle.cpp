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
Particle::Particle(ofPolyline _matchLine, string _gestureName) {
    location = _matchLine.getCentroid2D();
    size = sqrt(_matchLine.getArea());
    matchWidth = MIN(_matchLine.getBoundingBox().getWidth(), 150.0);
    matchHeight = MIN(_matchLine.getBoundingBox().getHeight(), 150.0);
    gestureName = _gestureName;
    lifespan = 160.0;
    setup();
}

void Particle::setup() {
    if (gestureName == "Gesture#1") {
        // setup circle drawing
        int scale = 50;
        float resolution = 0.004;
        int numPoints = 100;
        int radius = 0.7*size;
        int numRings = size/7;
        
        path.setFilled(false);
        path.setStrokeWidth(2);
        path.setStrokeColor(ofColor::black);
        
        background.setFilled(true);
        background.setColor(ofColor(143, 188, 143, 0));
        background.setCircleResolution(32);
        
        for (int r = 0; r <= radius; r+= radius/numRings) {
            path.newSubPath();
            bool bFirstPoint = true;
            for(int i = 0; i <= numPoints; i++){
                float a = ofMap(i, 0, numPoints-1, 0, TWO_PI);

                float x = location.x + r*cos(a)*matchWidth/200.0;
                float y = location.y + r*sin(a)*matchHeight/200.0;
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
        
        // Figure out the background ellipse shape
        glm::vec2 backgroundLocation = location + glm::vec2(ofRandom(-10.0, 10.0), ofRandom(-10.0, 10.0));
        
        ofRectangle boundingBox;
        vector<ofPolyline> outlines = path.getOutline();
        for (int i = 0; i < outlines.size(); i++) {
            ofRectangle b = outlines.at(i).getBoundingBox();
            if (i == 0) {
                boundingBox = b;
            } else {
                boundingBox.growToInclude(b);
            }
        }
        
        background.ellipse(backgroundLocation, boundingBox.width, boundingBox.height);
    } else {
        
    }
    
}

void Particle::update() {
    if (lifespan > 0.0) {
        lifespan = lifespan - 0.5*ofGetElapsedTimef();
        float bgColorAlpha = MIN(ofMap(lifespan, 160, 0, 0, 255), 255);
        ofLog() << bgColorAlpha;
        background.setColor(ofColor(143, 188, 143, bgColorAlpha));
    }
}

void Particle::draw() {
    ofPushStyle();
    
    ofEnableAlphaBlending();
    
    background.draw();
    
//    path.draw();
    
    vector<ofPolyline> lines = path.getOutline();
    
    // draws each line based on pct
    ofSetColor(ofColor::black);
    for (int i = 0; i < lines.size(); i++){
        float pct = ofMap(lifespan, 160.0, 0.0, 0.0, 1.0, true);
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
