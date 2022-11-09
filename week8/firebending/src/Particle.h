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
    
    glm::vec2 location;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float lifespan;
    
    Particle();
    Particle(glm::vec2 _location);
    
    private:
};


#endif /* Particle_h */
