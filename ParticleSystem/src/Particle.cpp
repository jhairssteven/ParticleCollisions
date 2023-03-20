#include "Particle.h"

//Declaracion de namespaces.
using namespace ci;
using namespace std;

Particle::Particle( const ci::vec2& position, float radius, float mass, float drag ){
    this->position = position;
    this->radius = radius;
    this->mass = mass;
    this->drag = drag;
    prevPosition = position;
    ci::vec2 forces = {0, 0};
}

void Particle::update(){
    ci::vec2 temp = position;
    ci::vec2 vel = ( position - prevPosition ) * drag;
    position += vel + forces / mass;
    prevPosition = temp;
    ci::vec2 forces = {0, 0};
}

void Particle::draw(){
    ci::gl::drawSolidCircle( position, radius );
}
