#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vect.h"
#include "Color.h"

class Light {
    Vect position;
    Color color;
    
    public:
    
    Light ();
    
    Light (Vect, Color);
    
    // method functions
    Vect getLightPosition () { return position; }
    Color getLightColor() { return color; }
      
};

Light::Light (Vect p, Color c) {
    position = p;
    color = c;
}
#endif
