#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

#define NUM_PARTICLES 50
#define REPULSION_FORCE_AMPLIFICATION_FACTOR 10.0f
class Particle {
    public:
        vec2 position; // Posición actual de la partícula
        vec2 velocity; // Velocidad actual de la partícula
        float radius; // Radio de la partícula
        float mass; // Masa de la partícula
        vec2 acceleration; // Aceleración actual de la partícula
        vec2 force; // Fuerza resultante que actúa sobre la partícula
        ColorA color;
        void changeSpeed(vec2 newSpeed) {
            velocity = newSpeed;
        }
};

class ParticleCollision : public App {
    public:
        void setup() override;
        void update() override;
        void draw() override;
        void mouseDown( MouseEvent event ) override;
    private:
        vector<Particle> particles;
        int speedFactor = 1;
};



//void speedUpOnClick(MouseEvent event) {
    //if(event.isLeftDown()) {
        //for (int i = 0; i < particles.size(); i++) {
            //Particle& p = particles[i];
            //p.velocity *= 1.1f;
        //}
    //}
//}

void ParticleCollision::setup() {
    // Inicializar las partículas
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle p;
        // Configurar valores iniciales
        p.position = vec2(Rand::randFloat(getWindowWidth()), Rand::randFloat(getWindowHeight()));
        p.velocity = vec2(Rand::randFloat(-5.0f, 5.0f), Rand::randFloat(-5.0f, 5.0f));
        p.radius = Rand::randFloat(5.0f, 20.0f);
        p.mass = p.radius * 0.1f;
        p.acceleration = vec2(0, 0);
        p.force = vec2(0, 0);
        // Asigna un color random
        p.color = Color( CM_HSV, lmap<float>( i, 0.0f, NUM_PARTICLES, 0.0f, 0.66f ), 1.0f, 1.0f );
        particles.push_back(p);
    }
}

void ParticleCollision::update() {
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
                    vec2 collision_force = normal * overlap * REPULSION_FORCE_AMPLIFICATION_FACTOR;
                    p.force -= collision_force;
                }
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

void drawParticleSpeed(const Particle& p) {
    gl::color(Color(1, 1, 1));
    gl::drawLine(p.position, p.position + p.velocity);
    // draw speed value over the particle
    gl::drawStringCentered(to_string(glm::length(p.velocity)), p.position);
}

void ParticleCollision::mouseDown( MouseEvent event ) {
    //if right click, increase
    if(event.isLeftDown()) {
       if(speedFactor < 100) {
            for (int i = 0; i < particles.size(); i++) {
                Particle& p = particles[i];
                p.velocity *= 1.5f;
            }

            speedFactor++;
        } 
    }

    //if left click, decrease
    if(event.isRightDown()) {
       if(speedFactor > 1) {
            for (int i = 0; i < particles.size(); i++) {
                Particle& p = particles[i];
                p.velocity *= 0.5f;
            }

            speedFactor--;
        }
    }

    //if middle click, reset
    if(event.isMiddleDown()) {
        for (int i = 0; i < particles.size(); i++) {
            Particle& p = particles[i];
            p.velocity = vec2(Rand::randFloat(-5.0f, 5.0f), Rand::randFloat(-5.0f, 5.0f));
        }

        speedFactor = 1;
    }
} 

void ParticleCollision::draw() {
    gl::clear(Color(0, 0, 0));
     // Dibujar todas las partículas
    for (const Particle& p : particles) {
        gl::color(p.color);
        gl::drawSolidCircle(p.position, p.radius);
        drawParticleSpeed(p);
    }

    //draw how to increase and decrease the speed
    gl::color(Color(1, 1, 1));
    gl::drawStringCentered("Click left to increase speed", vec2(100, 50));
    gl::drawStringCentered("Click right to decrease speed", vec2(100, 75));
    gl::drawStringCentered("Click middle to reset speed", vec2(100, 100));
    //draw speed factor
    gl::drawStringCentered("Speed factor: " + to_string(speedFactor), vec2(100, 150));
}

CINDER_APP(ParticleCollision, RendererGl)
