//
//  Wrist.h
//  firebending
//
//  Created by Thaís Xisto on 11/8/22.
//

#ifndef Wrist_h
#define Wrist_h

#include "ofMain.h"

class Wrist {
    public:
        
    void setup();
    void update(glm::vec3 detection, glm::vec3 neckDetection);
    void draw();
    
    float x;
    float y;
    float confidence;
    glm::vec3 detection;
    glm::vec3 neckDetection;
    ofPolyline path;
    std::vector<float> velocities;
    std::vector<float> accels;
    
    Wrist();
    
    private:
};

#endif /* Wrist_h */
