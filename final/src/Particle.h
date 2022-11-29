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
    
    ofPolyline path;
    std::vector<glm::vec3> circles;
    std::vector<ofColor> colors;
    glm::vec2 location;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float lifespan;
    
    Particle();
    Particle(glm::vec2 _location, glm::vec2 _velocity);
    
    private:
};


#endif /* Particle_h */
