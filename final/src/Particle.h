//
//  Particle.h
//  firebending
//
//  Created by Thaís Xisto on 11/9/22.
//

#ifndef Particle_h
#define Particle_h

#include "ofMain.h"

class Particle {
    public:
        
    void setup();
    void update();
    void draw();
    void run();
    bool isDone();
    
    std::vector<ofPath> circles;
    std::vector<ofColor> colors;
    ofPath path;
    ofPath background;
    glm::vec2 location;
    float lifespan;
    float size;
    float matchWidth;
    float matchHeight;
    ofPolyline matchLine;
    
    string gestureName;
    
    Particle();
    Particle(ofPolyline _matchLine, string _gestureName);
    
    private:
};


#endif /* Particle_h */
