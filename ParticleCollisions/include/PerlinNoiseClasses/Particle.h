#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include <cmath>

//Declaracion de namespaces.
using namespace ci;
using namespace std;


class Particleperlin{

    public:
    //Constructor.
        Particleperlin(const ci::vec2& position, float radius,float mass, float drag)                                         // Constructor de los objetos de tipo 'Particle'.
            :position(position), prevPosition(position), radius(radius), mass(mass), drag(drag), forces({0,0}){};       // Lista de asignación para las variables miembro.
    
    //Funciones de cinder.
        void update();                                                                                                  //Contiene el algoritmo para la funcion update() de la App principal.
        void draw();                                                                                                    //Contiene el algoritmo para la funcion draw() de la App principal.

    //Variables miembros de la clase.
        ci::vec2 position;                          // Posición.
        ci::vec2 prevPosition;                      // Posicion previa.
        ci::vec2 forces;                            // Fuerzas que se experimentan.
        float radius;                               // Radio de particula.
        float mass;                                 // Masa de parcula. 
        float drag;                                 // Arrastre.
};

void Particleperlin::update(){

    ci::vec2 vel = ( position - prevPosition ) * drag;      //Calcula la velocidad de las componentes del vector respecto al frame anterior y le añade un arrastre.
    prevPosition = position;                                //Guarda la posicion en la variable prevPosition para que en el siguiente update la posicion actual sea la previa.
    position += vel + forces / mass;                        //La posicion es modificada en funcion de la velocidad que lleva y las fuerzas que le afectan, que en este caso son dos (Viento:Perlin, y una oscilación de la funcion seno. Ver en ParticlesApp::update()).
    ci::vec2 forces = {0, 0};                               //Las fuerzas se vuelven nuevamente cero.
}

void Particleperlin::draw(){
    gl::color( 0.4f + abs(glm::normalize(position - prevPosition).x), 0.4f + abs(glm::normalize(position - prevPosition).y), 0.2);
    ci::gl::drawSolidCircle( position, radius );            //Dibuja la información de cada particula (en este caso es interezante de momento solo la posición y el radio).
}