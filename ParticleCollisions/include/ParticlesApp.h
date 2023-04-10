#pragma once
//Declaracion de pedendencias.
#include "Mode.h"
#include "cinder/app/App.h"                                 //Para la declaracion de la clase principal y sus funciones.
#include "cinder/app/RendererGl.h"                          //Para renderizar.

#include "cinder/Perlin.h"                                  //Header para PerlinNoise.

#include "ParticleSystem.h"
#include "cinder/Rand.h"                                    //Aleatorios.
#include "cinder/gl/gl.h"                                   //OpenGl.


//Declaracion de namespaces.
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ParticlesApp {

class ParticlesApp : public Mode {
    //Funciones publicas.
    public:
        void setup();                                          //Caracteristicas iniciales de la App y sus elementos.
	    void update();                                         //Funcion que actualiza la informacion de la App y sus elementos en cada frame.
	    void draw();                                           //Funcion que utiliza la información para hacer los graficos respectivos.
        void keyDown( KeyEvent event );                        //Implementacion inputs de teclado.
        void mouseMove(MouseEvent event);                      //Implementacion input del movimiento del mouse.
        void mouseDown(MouseEvent event);                      //Implementacion input del click del mouse.
    
    //Variables y objetos(miembros) publicos.
    public:
        
        //Variables miembro para las fuerzas perlin.
        float mFrequency;                                      //Frecuencia de agrado para el ruido perlin.
        Perlin mPerlin;                                        //Objeto perlin.
        ParticleSystem mParticleSystem;                        //Se declara un objeto(member) de la clase ParticleSystem con el nombre de mParticleSystem.

        //Variables miembro para las fuerzas por input de mouse.
        vec2 attrPosition;                                     // Vector para leer la posicion del mouse.
        float attrFactor;                                      // Para la fuerza de atraccion.
        float repulsionRadius;                                 // Para el radio de efecto de la repulsion.
        float repulsionFactor;                                 // Para la fuerza de repulsión.
};

void ParticlesApp::setup(){

    //Inicialisacion de perlin.
    mFrequency = 0.01f;                                        // Frecuencia al gusto.
    mPerlin = Perlin();                                        // Se llama al constructor de la funcion Perlin() del objeto perlin para inicializarlo.

    //Inicialización de inputs de mause.
    attrPosition = getWindowCenter();                          // En un inicio si el mouse no esta en pantalla, la fuerza de atracción es al centro de la ventana.
    attrFactor = 0.7f;                                       // Factor de atracción para las particulas.

    repulsionRadius = 250.f;                                   // Radio de efecto de la repulsión.
    repulsionFactor = 10.f;                                    // Factor para el efecto de la fuerza de repulsión.

    int numParticle = 850;                                     // Numero de particulas del sistema.
    for( int i=0; i<numParticle; i++ ){                                    
        mParticleSystem.createParticle();                      // Se llama la funcion de la clase del sistema de particulas que permite crear objeto 'Particle'.
    }
}

void ParticlesApp::update(){

    vec2 oscilationVec;
    oscilationVec.x = sin(getElapsedSeconds()*0.6f)*0.5f;       //Genera un vector de oscilaciones apartir de una onda determinada por el tiempo trancurrido(Radianes). El primer numero esta relacionado a la longitud y el segundo a la amplitud.
    oscilationVec.y = sin(getElapsedSeconds()*0.6f)*0.5f;       //La funcion getElapsedSeconds() retorna el tiempo que ha transcurrido la ejecución en segundos. 

    //for para iterar cada particula en el sistema, primero se define un vector que contiene variables de tipo Particle* (Apuntadores a objetos de la clase Particle).
    std::vector<Particleperlin*>::iterator it; 
    for(it = mParticleSystem.particles.begin(); it != mParticleSystem.particles.end(); ++it ) {

        //Comprueba que la particula siga en pantalla y si no la destruye para crear otra en pantalla.
         if((*it)->position.x > getWindowWidth()  || (*it)->position.x < 0 || (*it)->position.y > getWindowHeight() || (*it)->position.y < 0){

             mParticleSystem.destroyParticle((*it));              //Si esta fuera de rango, la destruye y crea otra.
             mParticleSystem.createParticle();                    //La crea con esta función.
             continue;                                            //Continua la comprobación para la siguiente del sistema de particulas.
         }
        else{

            //Fuerza perlin.
            vec2 windForce = mPerlin.dfBm( (*it)->position * mFrequency ); // Si aun sigue en pantalla entonces tendra algo de aletoriedad perlin.

            (*it)->forces += windForce * 1.0f;                             // Esta aletoriedad se añade a las fuerzas.
            (*it)->forces += oscilationVec;                                // Tambien se agrega la oscilación calculada anteriormente.

            //Fuerza de input de mouse.
            vec2 attrForce = glm::normalize(attrPosition - (*it)->position);                // Vectoriza la fuerza de atracción respecto a la posición.
            attrForce *= attrFactor;                                                        // Aplica el factor de atracción.
            (*it)->forces += attrForce;                                                     // La incluye en la variable miembro de la particula para que haga efecto.
        }
    }

    mParticleSystem.update();                                              // Con todas las particulas listas se actualizan.
}

void ParticlesApp::draw(){
    gl::clear( Color( 0, 0, 0) );                                   //Asigna el color del fondo de la ventana. En este caso ( 0, 0, 0) para negro. El maximo es ( 1, 1, 1).
    gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );   // En 2D no es tan utili pero permite hacer un manejo adecuado de las camaras y proyecciones.
    mParticleSystem.draw();                                         // Llama las funciones de dibujado.
}

//Eventos del teclado y mouse.

void ParticlesApp::mouseMove(MouseEvent event){                     // Registra el movimiento del mouse.

    attrPosition.x = event.getPos().x;                              // Llena las variables miembros de la app para utilizarlas en las funciones. En este caso guarda la posicion del mouse.
    attrPosition.y = event.getPos().y;                              // Llena las variables miembros de la app para utilizarlas en las funciones. En este caso guarda la posicion del mouse.       
}

void ParticlesApp::mouseDown(MouseEvent event){                     // Registra si se realizo clic en el mouse.


    for( std::vector<Particleperlin*>::iterator it = mParticleSystem.particles.begin(); it != mParticleSystem.particles.end(); ++it ) {    

        vec2 repulsionForce = (*it)->position - vec2(float(event.getPos().x), float(event.getPos().y));                                    // Vectoriza la repulsion respecto de la posicion de la particula.
        repulsionForce = glm::normalize(repulsionForce) * math<float>::max(0.f, repulsionRadius - length(repulsionForce));                 // Normaliza la repulsion y le aplica un factor que depende de la distancia. Ademas si la particula esta fuera del radio de incidencia no le palica fuerzas.
        (*it)->forces += repulsionForce*repulsionFactor;                                                                                   // LE aplica un factor adicional. Para darle mas o menos fuerza a la repulsion.
    }
}
} // namespace ParticleApp
