#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

//Declaracion de namespaces.
using namespace ci;
using namespace std;


class Particle{

    public:
    //Constructor.
        Particle(const ci::vec2& position, float radius,float mass, float drag)
            :position(position), prevPosition(position), radius(radius), mass(mass), drag(drag), forces({0,0}){};
    
    //Funciones de cinder.
        void update();
        void draw();

    //Las variables necesarias.
        ci::vec2 position;
        ci::vec2 prevPosition;
        ci::vec2 forces;
        float radius;
        float mass;
        float drag;
};
