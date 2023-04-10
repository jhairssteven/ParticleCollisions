#pragma once

#include <iostream>
#include <vector>

#include "Mode.h"
#include "cinder/Rand.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define NUM_PARTICLES 50
#define REPULSION_FORCE_AMPLIFICATION_FACTOR 10.0f


namespace Wall_particle {
class Particle {
   public:
    vec2 position;      // Posición actual de la partícula
    vec2 velocity;      // Velocidad actual de la partícula
    float radius;       // Radio de la partícula
    float mass;         // Masa de la partícula
    vec2 acceleration;  // Aceleración actual de la partícula
    vec2 force;         // Fuerza resultante que actúa sobre la partícula
    ColorA color;
};

class SolidObject {
   public:
    vec2 position;
    float size;
};

class Wallparticle : public Mode {
   public:
    void setup();
    void update();
    void draw();

   private:
    vector<Particle> particles;
    SolidObject solidObject;
};

void Wallparticle::setup() {
    // Inicializar las partículas
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle p;
        // Configurar valores iniciales
        p.position = vec2(Rand::randFloat(getWindowWidth()),
                          Rand::randFloat(getWindowHeight()));
        p.velocity =
            vec2(Rand::randFloat(-5.0f, 5.0f), Rand::randFloat(-5.0f, 5.0f));
        p.radius = Rand::randFloat(5.0f, 20.0f);
        p.mass = p.radius * 0.1f;
        p.acceleration = vec2(0, 0);
        p.force = vec2(0, 0);
        // Asigna un color random
        p.color =
            Color(CM_HSV, lmap<float>(i, 0.0f, NUM_PARTICLES, 0.0f, 0.66f),
                  1.0f, 1.0f);
        particles.push_back(p);
    }
    solidObject.position = vec2(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);
    solidObject.size = 200.0f;

}
void Wallparticle::update() {
    float offset = 5.0f;
    // Actualizar las partículas
    for (int i = 0; i < particles.size(); i++) {
        Particle& p = particles[i];
        // Calcular la fuerza resultante que actúa sobre la partícula
        p.force = vec2(0, 0);
        for (int j = 0; j < particles.size(); j++) {
            if (i != j) {
                Particle& other = particles[j];
                // Calcular la fuerza de colisión entre las dos partículas
                vec2 direction = other.position - p.position;
                float distance = glm::length(direction);
                float overlap = p.radius + other.radius - distance + offset;
                if (overlap > 0) {
                    vec2 normal = glm::normalize(direction);
                    vec2 collision_force =
                        normal * overlap * REPULSION_FORCE_AMPLIFICATION_FACTOR;
                    p.force -= collision_force;
                }
            }
        }
// Verificar si alguna partícula ha colisionado con el objeto sólido
        for (int i = 0; i < particles.size(); i++) {
            Particle& p = particles[i];

        // Calcular la distancia entre la partícula y el objeto sólido
            vec2 direction = solidObject.position - p.position;
            float distance = glm::length(direction);

        // Si la partícula ha colisionado con el objeto sólido, evitar que se mueva hacia esa dirección
            if (distance < p.radius + solidObject.size / 2.0f) {
                vec2 normal = glm::normalize(direction);
                float overlap = p.radius + solidObject.size / 2.0f - distance;
                p.position -= normal * overlap;
                p.velocity -= glm::dot(p.velocity, normal) * normal;
            }
        }            

        float x = p.position[0];
        float y = p.position[1];
        x += x < p.radius ? -p.radius : p.radius;
        y += y < p.radius ? -p.radius : p.radius;

        if (x < 0 || x > getWindowWidth()) {
            p.velocity[0] = -p.velocity[0];
            p.position[0] = x < 0 ? p.radius : getWindowWidth() - p.radius;
        } else if (y < 0 || y > getWindowHeight()) {
            p.velocity[1] = -p.velocity[1];
            p.position[1] = y < 0 ? p.radius : getWindowHeight() - p.radius;
        }
        float timeStep = 0.1f;

        // Aplicar la fuerza resultante sobre la partícula
        p.acceleration = p.force / p.mass;
        p.velocity += p.acceleration * timeStep;
        // Actualizar la posición de la partícula en base a su velocidad
        p.position += p.velocity * timeStep;
        // Resetear la fuerza acumulada para la siguiente iteración
        p.force = vec2(0, 0);
    }
}
void Wallparticle::draw() {
    gl::clear(Color(0, 0, 0));

    // Darle color y posicion al objeto solido (un cuadrado)
    gl::color(Color::white());
    gl::drawSolidRect(Rectf(solidObject.position - vec2(solidObject.size / 2.0f), solidObject.position + vec2 (solidObject.size / 2.0f)));

    // Dibujar todas las partículas
    for (const auto& p : particles) {
        gl::color(p.color);
        gl::drawSolidCircle(p.position, p.radius);
    }
}
}
