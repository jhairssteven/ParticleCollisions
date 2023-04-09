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
        void update();                                          //Contiene el algoritmo para la funcion update() de la App principal.
        void draw();                                            //Contiene el algoritmo para la funcion draw() de la App principal.
        
        //Funciones de maniobralidad del sistema de particulas.
        void createParticle();                                  // Funcion que crea particulas en el sistema de particulas.
        void destroyParticle( Particle* particle );             // Funcion que destruye particulas en el sistema de particulas.
        
    public:
        std::vector<Particle*> particles;                       //La unica variable miembro del sistema es un vector. Se llena al inicio en la funcion 'setup()' de la App principal.
};
