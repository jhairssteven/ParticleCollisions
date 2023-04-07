#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

//Declaracion de namespaces.
using namespace ci;
using namespace std;


class Particle{

    public:
    //Constructor.
        Particle(const ci::vec2& position, float radius,float mass, float drag);
    
    //Funciones basicas de cinder.
        void update();
        void draw();

    //Las variables necesarias.
        ci::vec2 position, prevPosition;
        ci::vec2 forces;
        float radius;
        float mass;
        float drag;
};
