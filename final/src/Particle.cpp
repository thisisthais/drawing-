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
    size = sqrt(abs(_matchLine.getArea()));
    matchWidth = _matchLine.getBoundingBox().getWidth();
    matchHeight = _matchLine.getBoundingBox().getHeight();
    gestureName = _gestureName;
    lifespan = 160.0;
    
    colors = {
        ofColor::cadetBlue,
        ofColor::chocolate,
        ofColor::cornflowerBlue,
        ofColor::darkorange,
        ofColor::darkSeaGreen
    };
    
    setup();
}

void Particle::setup() {
    path.setFilled(false);
    path.setStrokeWidth(2);
    path.setStrokeColor(ofColor::black);
    
    background.setFilled(true);
    background.setCircleResolution(32);
    
    bgColor = colors[(int)ofRandom(colors.size())];
    bgColor.a = 0;
    
    background.setColor(bgColor);
    
    if (gestureName == "Gesture#1") {
        // setup circle drawing
        int scale = 50;
        float resolution = 0.004;
        int numPoints = 100;
        int radius = 0.7*size;
        int numRings = size/7;
        
        matchWidth = MIN(matchWidth, 150.0);
        matchHeight = MIN(matchHeight, 150.0);
        
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
        
    } else if (gestureName == "Gesture#2") {
        float scale = CLAMP(size/ 20.0, 10.0, 20.0);
        float resolution = 0.005;
        
        for (int i = 0; i < matchWidth; i+=30) {
            float x = ofMap(i, 0, matchWidth - 1, location.x - matchWidth/2, location.x + matchWidth/2, true);
            for (int j = 0; j < matchHeight; j+=30) {

                float y = ofMap(j, 0, matchHeight - 1, location.y - matchHeight/2, location.y + matchHeight/2, true);

                float radius = ofMap(ofNoise((x+y)*resolution), 0, 1, 0.0, scale);

                path.circle(x, y, radius);
                path.close();

                glm::vec2 backgroundLocation = glm::vec2(x, y) + glm::vec2(ofRandom(-3.0, 3.0), ofRandom(-3.0, 3.0));
                background.circle(backgroundLocation, radius);
                background.close();
            }
        }

        float randRotate = ofRandom(-20.0, 20.0);
        path.rotateDeg(randRotate, location);
        background.rotateDeg(randRotate, location);
    } else {
        int scale = 50;
        float resolution = 0.04;
        int numPoints = 20;
        int radius = 0.7*size*matchWidth/200.0;
        
        matchWidth = MIN(matchWidth, 150.0);
        matchHeight = MIN(matchHeight, 150.0);
         
        path.circle(location, 20.0);
        
        
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
    }
    
}

void Particle::update() {
    if (lifespan > 0.0) {
        lifespan = lifespan - 0.5*ofGetElapsedTimef();
        float bgColorAlpha = MIN(ofMap(lifespan, 160, 0, 0, 255), 255);
        bgColor.a = bgColorAlpha;
    }
    
    background.setColor(bgColor);
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
            if (pctj <= pct){
                newLine.addVertex(lines[i][j]);
            }
        }
        newLine.draw();
    }
    
    ofDisableAlphaBlending();
    
    ofPopStyle();
}

void Particle::changeColor() {
    ofLog() << "change";
    int r = (int)ofRandom(colors.size());
    bgColor = colors[r];
    background.setColor(bgColor);
//    bgColor.a = 0;
//    lifespan = 160.0;
    ofLog() << bgColor;
}

void Particle::run() {
    update();
    draw();
}

bool Particle::isDone() {
    return false;
//    return lifespan < 0;
}
