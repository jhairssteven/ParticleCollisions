//Declaracion de pedendencias.
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

// Configuraciones de la aplicación.
void prepareSettings( App::Settings* settings);

class ParticlesApp : public App {
    //Funciones publicas.
    public:
        void setup();                                          //Caracteristicas iniciales de la App y sus elementos.
	    void update();                                         //Funcion que actualiza la informacion de la App y sus elementos en cada frame.
	    void draw();                                           //Funcion que utiliza la información para hacer los graficos respectivos.
        void keyDown( KeyEvent event );                        //Implementacion inputs de teclado.
        void mouseMove(MouseEvent event);
        void mouseDown(MouseEvent event);
    
    //Variables y objetos(miembros) publicos.
    public:
        
        //Variables miembro para las fuerzas perlin.
        float mFrequency;                                      //Frecuencia de agrado para el ruido perlin.
        Perlin mPerlin;                                        //Objeto perlin.
        ParticleSystem mParticleSystem;                        //Se declara un objeto(member) de la clase ParticleSystem con el nombre de mParticleSystem.

        //Variables miembro para las fuerzas por input de mouse.
        vec2 attrPosition;
        float attrFactor;
        float repulsionRadius;
        float repulsionFactor;
};

void ParticlesApp::setup(){

    //Inicialisacion de perlin.
    mFrequency = 0.01f;                                        //Frecuencia al gusto.
    mPerlin = Perlin();                                        //Se llama al constructor de la funcion Perlin() del objeto perlin para inicializarlo.

    //Inicializacion de inputs de mause.
    attrPosition = getWindowCenter();
    attrFactor = 0.002f;

    repulsionRadius = 250.f;
    repulsionFactor = 10.f;

    int numParticle = 850;                                    //Numero de particulas del sistema.
    for( int i=0; i<numParticle; i++ ){                                    
        mParticleSystem.createParticle();                      //Se llama la funcion de la clase del sistema de particulas que permite crear objeto 'Particle'.
    }
}

void ParticlesApp::update(){

    vec2 oscilationVec;
    oscilationVec.x = sin(getElapsedSeconds()*0.6f)*0.5f;       //Genera un vector de oscilaciones apartir de una onda determinada por el tiempo trancurrido(Radianes). El primer numero esta relacionado a la longitud y el segundo a la amplitud.
    oscilationVec.y = sin(getElapsedSeconds()*0.6f)*0.5f;       //La funcion getElapsedSeconds() retorna el tiempo que ha transcurrido la ejecución en segundos. 

    //for para iterar cada particula en el sistema, primero se define un vector que contiene variables de tipo Particle* (Apuntadores a objetos de la clase Particle).
    std::vector<Particle*>::iterator it; 
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
            vec2 attrForce = attrPosition - (*it)->position;
            attrForce *= attrFactor;
            (*it)->forces += attrForce;
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
void ParticlesApp::keyDown( KeyEvent event ){

	if( event.getCode() == KeyEvent::KEY_ESCAPE ) {                 //Si se preciona 'ESC' cierra el programa.
			quit();
	}
}

void ParticlesApp::mouseMove(MouseEvent event){

    attrPosition.x = event.getPos().x;
    attrPosition.y = event.getPos().y;
}

void ParticlesApp::mouseDown(MouseEvent event){


    for( std::vector<Particle*>::iterator it = mParticleSystem.particles.begin(); it != mParticleSystem.particles.end(); ++it ) {

        vec2 repulsionForce = (*it)->position - vec2(float(event.getPos().x), float(event.getPos().y));
        repulsionForce = glm::normalize(repulsionForce) * math<float>::max(0.f, repulsionRadius - length(repulsionForce));
        (*it)->forces += repulsionForce*repulsionFactor;
    }
}

// Definicion de configuraciónes.
void prepareSettings(App::Settings *settings){

    settings->setWindowSize(1280, 640);
    settings->setFullScreen( false   );
    settings->setTitle( "Particle System ~ HPC" );
    settings->setFrameRate( 60 );
}

CINDER_APP(ParticlesApp, RendererGl, prepareSettings)


