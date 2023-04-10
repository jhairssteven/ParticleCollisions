#include "Particle.h"
#include <cmath>

//Declaracion de namespaces.
using namespace ci;
using namespace std;

void Particle::update(){

    ci::vec2 vel = ( position - prevPosition ) * drag;      //Calcula la velocidad de las componentes del vector respecto al frame anterior y le añade un arrastre.
    prevPosition = position;                                //Guarda la posicion en la variable prevPosition para que en el siguiente update la posicion actual sea la previa.
    position += vel + forces / mass;                        //La posicion es modificada en funcion de la velocidad que lleva y las fuerzas que le afectan, que en este caso son dos (Viento:Perlin, y una oscilación de la funcion seno. Ver en ParticlesApp::update()).
    ci::vec2 forces = {0, 0};                               //Las fuerzas se vuelven nuevamente cero.
}

void Particle::draw(){
    gl::color( 0.4f + abs(glm::normalize(position - prevPosition).x), 0.4f + abs(glm::normalize(position - prevPosition).y), 0.2);
    ci::gl::drawSolidCircle( position, radius );            //Dibuja la información de cada particula (en este caso es interezante de momento solo la posición y el radio).
}
