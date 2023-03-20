#pragma once
#include "Particle.h"
#include <vector>

//Declaracion de namespaces.
using namespace ci;
using namespace std;

class ParticleSystem{
    public:
        ~ParticleSystem();
        void update();
        void draw();
        void addParticle( Particle *particle );
        void destroyParticle( Particle *particle );
        std::vector<Particle*> particles;
};
