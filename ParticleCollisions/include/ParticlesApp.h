#pragma once
// Declaracion de pedendencias.

#include <vector>

#include "Mode.h"
#include "cinder/Rand.h"  //Aleatorios.
#include "cinder/Vector.h"
#include "cinder/app/App.h"         //Para la declaracion de la clase principal.
#include "cinder/app/RendererGl.h"  //Para renderizar.
#include "cinder/gl/gl.h"           //OpenGl.

// Declaracion de namespaces.
using namespace ci;
using namespace ci::app;
using namespace std;

namespace particles_app {
class Particle {
    // Constructor.
   public:
    Particle(const ci::vec2 &position, float radius, float mass, float drag);

    // Funciones basicas de cinder.
    void update();
    void draw();

    // Las variables necesarias.
    ci::vec2 position, prevPosition;
    ci::vec2 forces;
    float radius;
    float mass;
    float drag;
};

Particle::Particle(const ci::vec2 &position, float radius, float mass,
                   float drag) {
    this->position = position;
    this->radius = radius;
    this->mass = mass;
    this->drag = drag;
    prevPosition = position;
    ci::vec2 forces = {0, 0};
}

void Particle::update() {
    ci::vec2 temp = position;
    ci::vec2 vel = (position - prevPosition) * drag;
    position += vel + forces / mass;
    prevPosition = temp;
    ci::vec2 forces = {0, 0};
}

void Particle::draw() { ci::gl::drawSolidCircle(position, radius); }

class ParticleSystem {
   public:
    ParticleSystem();
    void update();
    void draw();
    void addParticle(Particle *particle);
    void destroyParticle(Particle *particle);
    std::vector<Particle *> particles;
};

ParticleSystem::ParticleSystem() {
    for (std::vector<Particle *>::iterator it = particles.begin();
         it != particles.end(); ++it) {
        delete *it;
    }

    particles.clear();
}

void ParticleSystem::update() {
    for (std::vector<Particle *>::iterator it = particles.begin();
         it != particles.end(); ++it) {
        (*it)->update();
    }
}

void ParticleSystem::draw() {
    for (std::vector<Particle *>::iterator it = particles.begin();
         it != particles.end(); ++it) {
        (*it)->draw();
    }
}

void ParticleSystem::addParticle(Particle *particle) {
    particles.push_back(particle);
}

void ParticleSystem::destroyParticle(Particle *particle) {
    std::vector<Particle *>::iterator it =
        std::find(particles.begin(), particles.end(), particle);
    delete *it;
    particles.erase(it);
}

class ParticlesApp : public Mode {
    // Funciones publicas.
   public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseMove(MouseEvent event) override;
    void mouseDown(MouseEvent event) override;

    // Variables y objetos(miembros) publicos.
   public:
    ParticleSystem
        mParticleSystem;  // Se declara un objeto(member) de la clase
                          // ParticleSystem con el nombre de mParticleSystem.

    // Aplicando fuerzas de repulsion y atraccion.
    vec2 attrPosition;
    float attrFactor, repulsionFactor, repulsionRadius;
};

void ParticlesApp::setup() {
    int numParticle = 100;
    for (int i = 0; i < numParticle; i++) {
        ci::Rand::randomize();  // Genera una semilla aleatoria para sBase el
                                // cual a su vez es la "semilla" de randfloat.
                                // ver Rand.h. Asi la posicion inicial de las
                                // particulas es diferente.
        float x = ci::randFloat(0.0f, getWindowWidth());
        float y = ci::randFloat(0.0f, getWindowHeight());
        float radius = ci::randFloat(5.0f, 15.0f);
        float mass = radius;
        float drag = 0.95f;
        Particle *particle = new Particle(vec2(x, y), radius, mass, drag);
        mParticleSystem.addParticle(particle);
    }

    // Inicializando las fuerzas de repulsion y atraccion.
    attrPosition = getWindowCenter();
    attrFactor = 0.000005f;
    repulsionRadius = 5.f;
    repulsionFactor = -0.0005f;
}

void ParticlesApp::update() {
    for (std::vector<Particle *>::iterator it =
             mParticleSystem.particles.begin();
         it != mParticleSystem.particles.end(); ++it) {
        vec2 attrForce = attrPosition - (*it)->position;
        attrForce *= attrFactor;
        (*it)->forces += attrForce;
    }

    mParticleSystem.update();
}

void ParticlesApp::draw() {
    gl::clear(Color(0, 0, 0));
    gl::setMatricesWindow(getWindowWidth(), getWindowHeight());
    mParticleSystem.draw();
}

// Eventos de mouse.
void ParticlesApp::mouseMove(MouseEvent event) {
    attrPosition.x = event.getPos().x;
    attrPosition.y = event.getPos().y;
}

void ParticlesApp::mouseDown(MouseEvent event) {
    for (std::vector<Particle *>::iterator it =
             mParticleSystem.particles.begin();
         it != mParticleSystem.particles.end(); ++it) {
        // vec2 repulsionForce = (*it)->position -
        // glm::intBitsToFloat(event.getPos()); //Genera error de type, por eso
        // se coloca una conversion.
        vec2 repulsionForce = (*it)->position - vec2(float(event.getPos().x),
                                                     float(event.getPos().y));
        repulsionForce =
            glm::normalize(repulsionForce) *
            math<float>::max(0.f, repulsionRadius - repulsionForce.length());
        (*it)->forces += repulsionForce;
    }
}

/* CINDER_APP(ParticlesApp, RendererGl)     */

}  // namespace particles_app