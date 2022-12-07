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
        ofColor::crimson,
        ofColor::darkorange,
        ofColor::darkSeaGreen,
        ofColor::darkRed,
        ofColor::darkSlateBlue,
        ofColor::fireBrick,
        ofColor::gainsboro,
        ofColor::gold,
        ofColor::goldenRod,
        ofColor::honeyDew,
        ofColor::indianRed,
        ofColor::khaki,
        ofColor::lavender,
        ofColor::lavenderBlush,
        ofColor::lightBlue,
        ofColor::lightCoral,
        ofColor::lightSalmon,
        ofColor::lightSeaGreen,
        ofColor::lightSlateGray,
        ofColor::maroon,
        ofColor::mediumAquaMarine,
        ofColor::mediumPurple,
        ofColor::mediumSeaGreen,
        ofColor::mediumSlateBlue,
        ofColor::mediumTurquoise,
        ofColor::midnightBlue,
        ofColor::mistyRose,
        ofColor::olive,
        ofColor::oliveDrab,
        ofColor::orange,
        ofColor::paleGoldenRod,
        ofColor::paleVioletRed,
        ofColor::peru,
        ofColor::plum,
        ofColor::powderBlue,
        ofColor::rosyBrown,
        ofColor::royalBlue,
        ofColor::saddleBrown,
        ofColor::salmon,
        ofColor::sandyBrown,
        ofColor::seaGreen,
        ofColor::slateBlue,
        ofColor::steelBlue,
        ofColor::tan,
        ofColor::teal,
        ofColor::thistle,
        ofColor::white,
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
    } else if (gestureName == "Gesture#3"){
        
        int nTips = 4 + ofRandom(1, 12);
        int nStarPts = nTips * 2;
        float angleChangePerPt = TWO_PI / (float)nStarPts;
        float innerRadius = matchWidth/4.0;
        float outerRadius = innerRadius + 30;
        glm::vec2 bgNoise = glm::vec2(ofRandom(-5.0, 5.0), ofRandom(-5.0, 5.0));
        
        float angle = 0;
        
//        for (int j = 0; j < 3; j++) {
//            float xNoise = ofRandom(j*outerRadius*1.2, j*outerRadius*2.0);
//            if (ofRandom(1.0) >= 0.5) {
//                xNoise *= -1.0;
//            }
//            float yNoise = ofRandom(j*outerRadius*1.2, j*outerRadius*2.0);
//            if (ofRandom(1.0) >= 0.5) {
//                xNoise *= -1.0;
//            }
        float origx = location.x;
        float origy = location.y;
        glm::vec2 bgOrig = location + bgNoise;
            
            for (int i = 0; i <= nStarPts; i++){
                if (i % 2 == 0) {
                    // inside point:
                    float x = origx + innerRadius * cos(angle);
                    float y = origy + innerRadius * sin(angle);
                    path.curveTo(x,y);
                    
                    float bgX = bgOrig.x + innerRadius * cos(angle);
                    float bgY = bgOrig.y + innerRadius * sin(angle);
                    background.curveTo(bgX, bgY);
                } else {
                    // outside point
                    float x = origx + outerRadius * cos(angle);
                    float y = origy + outerRadius * sin(angle);
                    path.curveTo(x,y);
                    
                    float bgX = bgOrig.x + outerRadius * cos(angle);
                    float bgY = bgOrig.y + outerRadius * sin(angle);
                    background.curveTo(bgX, bgY);
                }
                angle += angleChangePerPt;
            }
            
            //starting point
            float x = origx + innerRadius * cos(0);
            float y = origy + innerRadius * sin(0);
            path.curveTo(x, y);
            path.close();
        
            float bgX = bgOrig.x + innerRadius * cos(0);
            float bgY = bgOrig.y + innerRadius * sin(0);
            background.curveTo(bgX, bgY);
            background.close();
//        }
    } else if (gestureName == "Gesture#4") {
//        background.circle(location.x, location.y, 20.0);
        
        location.y -= matchHeight/2;
        ofPoint start(location);
        
        // define the parameters of the spiral
          float angle = PI;   // initial angle of the spiral
          float delta = 0.1; // increment of the angle at each step
          float speed = 1;   // rate at which the spiral grows
        float downwards = 0;
        float length = CLAMP(20.0, matchHeight, 200.0);
        float radius = ofMap(length, 1.0, ofGetHeight(), 10.0, 60.0); // initial radius of the spiral
        float scale = 20.0;
        float resolution = 0.005;
        
        if (ofRandom(1.0) >= 0.5) {
            delta *= -1.0;
        }
        // draw the spiral
        while (downwards < length) {
          // update the radius and angle of the spiral
//          radius += speed;
          angle += delta;
            downwards += speed;

          // calculate the next point on the spiral
          ofPoint next(start.x + radius * cos(angle), start.y + downwards + radius*0.8 * sin(angle));
          path.curveTo(next); // draw a line from the current position to the next point
            
            if ((int)downwards % 4 == 0) {
                background.lineTo(next);
            }
        }
        
        path.close();
        background.close();
        background.translate(glm::vec2(ofRandom(-5.0, 5.0), ofRandom(-5.0, 5.0)));
    } else {
        ofPoint start(location);
        
        // define the parameters of the spiral
          float angle = PI;   // initial angle of the spiral
          float delta = 0.1; // increment of the angle at each step
          float speed = 1;   // rate at which the spiral grows
        float downwards = 0;
        float length = CLAMP(20.0, matchHeight, 200.0);
        float radius = 200.0/length; // initial radius of the spiral
        float scale = 20.0;
        float resolution = 0.005;
        
        if (ofRandom(1.0) >= 0.5) {
            delta *= -1.0;
        }
        // draw the spiral
        while (downwards < length) {
          // update the radius and angle of the spiral
//          radius += speed;
          angle += delta;
            downwards += speed;

          // calculate the next point on the spiral
          ofPoint next(start.x + radius * cos(angle), start.y + downwards + radius*0.8 * sin(angle));
          path.lineTo(next); // draw a line from the current position to the next point
        }
        
        path.close();
    }
    
}

void Particle::update() {
    if (lifespan > 0.0) {
        lifespan = lifespan - 0.5*ofGetElapsedTimef();
        float bgColorAlpha = MIN(ofMap(lifespan, 160, 0, 0, 150), 150);
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
    int r = (int)ofRandom(colors.size());
    this->bgColor = colors[r];
    this->background.setColor(this->bgColor);
}

void Particle::run() {
    update();
    draw();
}

bool Particle::isDone() {
    return false;
//    return lifespan < 0;
}
