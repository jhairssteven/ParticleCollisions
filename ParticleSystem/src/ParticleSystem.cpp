#include "ParticleSystem.h"
#include "cinder/Rand.h" //Aleatorios.
//#include "cinder/gl/gl.h" //openGL
#include "cinder/app/App.h"

//Declaracion de namespaces.
using namespace ci;
using namespace ci::app;
using namespace std;


//Funciones de la clase ParticleSystem:

//Destructor:                                                               //Es el destructor del sistema de particulas.
ParticleSystem::~ParticleSystem(){
    std::vector<Particle*>::iterator it;                                    //Tipo vector(iterador).
    for(it = particles.begin(); it != particles.end(); ++it ){
        delete *it;                                                         //Liberando memoria. Aqui se desreferencia el iterador lo cual deja como resultado el tipo de dato del vector que en este caso es un apuntador.
    }
    particles.clear();
}

void ParticleSystem::update(){
    std::vector<Particle*>::iterator it;                                    //Tipo vector(iterador).
    for(it = particles.begin(); it != particles.end(); ++it ){
        (*it)->update();                                                    //La función 'update()' del sistema de particulas llama la función 'update()' de y para uno de los apuntadores para que se actualicen las variables miembros del objeto.
    }
}

void ParticleSystem::draw(){
    std::vector<Particle*>::iterator it;                                    //Tipo vector(iterador).
    for(it = particles.begin(); it != particles.end(); ++it ){
        (*it)->draw();                                                      //La funcion 'draw()' del sistema de particualas llama la funcion 'draw()' de y para cada uno de los apuntadores del tipo 'Particle'.
    }
}

void ParticleSystem::addParticle( Particle* particle ){
    particles.push_back( particle );                                        // Agrega la particula a la cola del vector.
}

void ParticleSystem::createParticle(){
    
    //Variables para las particulas.
    ci::Rand::randomize();                                                  //Genera una semilla aleatoria para sBase el cual a su vez es la "semilla" de randfloat. ver Rand.h. Asi la posicion inicial de las particulas es diferente.
    float x = ci::randFloat( 0.0f, getWindowWidth() );                      //Posición aleatoria en x.
    float y = ci::randFloat( 0.0f, getWindowHeight() );                     //Posición aleatoria en y.
    float radius = Rand::randFloat(1.0f, 4.0f);                             //Radio.
    float mass = radius*100;                                                //Mass.
    float drag = 0.2f;                                                      //Arrastre.
    Particle *particle = new Particle( vec2( x, y ), radius, mass, drag );  //Creacion del apuntador del tipo 'Particle' que simula una particula.
    this->addParticle(particle);                                            //Se añade el apuntador al sistema de particulas.
}



void ParticleSystem::destroyParticle( Particle* particle ){                                     //Hace de función destructora de cada particula (En este caso apuntadores tipo 'Particle'). 
    std::vector<Particle*>::iterator it;                                                        //Declaración del iterador del vector de apuntadores de objetos Particle. 
    it = std::find( particles.begin(), particles.end(), particle );                             //Encuentra el apuntador 
    delete *it;                                                                                 //Esta liberando la memoria del apuntador, it itera datos del tipo apuntador. Al desenvolver
    particles.erase( it );                                                                      //ELimina del vector del sistema de particulas el apuntador que ya no hace parte de ninguna clase. 
}
