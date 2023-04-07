#pragma once
#include "Particle.h"
#include <vector>

//Declaracion de namespaces.
using namespace ci;
using namespace std;

class ParticleSystem{
    public:
        ~ParticleSystem();
        //Funcion integradora de particulas.
        void addParticle( Particle* particle );
        
        //funciones cinder.
        void update();
        void draw();
        
        //Funciones de maniobralidad del sistema de particulas.
        void createParticle();
        void destroyParticle( Particle* particle );
        
    public:
        std::vector<Particle*> particles;
};
