#include "ParticleSystem.h"
#include "cinder/Rand.h" //Aleatorios.
//#include "cinder/gl/gl.h" //openGL
#include "cinder/app/App.h"

//Declaracion de namespaces.
using namespace ci;
using namespace ci::app;
using namespace std;


//Funciones de la clase ParticleSystem:

//Destructor:
ParticleSystem::~ParticleSystem(){
    std::vector<Particle*>::iterator it; //Tipo vector(iterador).
    for(it = particles.begin(); it != particles.end(); ++it ){
        delete *it; //Liberando memoria. Aqui se desreferencia el iterador lo cual deja como resultado el tipo de dato del vector que en este caso es un apuntador.
    }
    particles.clear();
}

void ParticleSystem::update(){
    std::vector<Particle*>::iterator it; //Tipo vector(iterador).
    for(it = particles.begin(); it != particles.end(); ++it ){
        (*it)->update();
    }
}

void ParticleSystem::draw(){
    std::vector<Particle*>::iterator it; //Tipo vector(iterador).
    for(it = particles.begin(); it != particles.end(); ++it ){
        (*it)->draw();
    }
}

void ParticleSystem::addParticle( Particle* particle ){
    particles.push_back( particle );
}

void ParticleSystem::createParticle(){
    
    //Variables para las particulas.
    ci::Rand::randomize(); //Genera una semilla aleatoria para sBase el cual a su vez es la "semilla" de randfloat. ver Rand.h. Asi la posicion inicial de las particulas es diferente.
    float x = ci::randFloat( 0.0f, getWindowWidth() ); //Posición aleatoria en x.
    float y = ci::randFloat( 0.0f, getWindowHeight() ); //Posición aleatoria en y.
    float radius = Rand::randFloat(1.0f, 1.5f); //Radio.
    float mass = radius*100; //Mass
    float drag = 0.2f;
    Particle *particle = new Particle( vec2( x, y ), radius, mass, drag );
    this->addParticle(particle);
}



void ParticleSystem::destroyParticle( Particle* particle ){
    std::vector<Particle*>::iterator it;                                                        //declaración del iterador del vector de apuntadores de objetos Particle. 
    it = std::find( particles.begin(), particles.end(), particle );                             //Encuentra el apuntador 
    delete *it;                                                                                 //Esta liberando la memoria del apuntador, it itera datos del tipo apuntador. Al desenvolver
    particles.erase( it );
}
