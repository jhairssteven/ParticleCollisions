#pragma once
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

//Declaracion de namespaces.
using namespace ci;
using namespace std;


class Particle{

    public:
    //Constructor.
        Particle(const ci::vec2& position, float radius,float mass, float drag)                                         // Constructor de los objetos de tipo 'Particle'.
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
