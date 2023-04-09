#include "Particle.h"

//Declaracion de namespaces.
using namespace ci;
using namespace std;

void Particle::update(){

    ci::vec2 vel = ( position - prevPosition ) * drag;
    prevPosition = position;
    position += vel + forces / mass;
    ci::vec2 forces = {0, 0};
}

void Particle::draw(){
    ci::gl::drawSolidCircle( position, radius );
}
