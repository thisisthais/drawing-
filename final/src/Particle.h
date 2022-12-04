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
    bool isDead();
    
    std::vector<ofPath> circles;
    std::vector<ofColor> colors;
    std::vector<ofPoint> points;
    ofPath path;
    glm::vec2 location;
    float lifespan;
    string gestureName;
    
    Particle();
    Particle(glm::vec2 _location, string _gestureName);
    
    private:
};


#endif /* Particle_h */
