//Declaracion de pedendencias.
#include "cinder/app/App.h" //Para la declaracion de la clase principal.
#include "cinder/app/RendererGl.h" //Para renderizar.

#include "ParticleSystem.h"
#include "cinder/Rand.h" //Aleatorios.
#include "cinder/gl/gl.h" //OpenGl.


//Declaracion de namespaces.
using namespace ci;
using namespace ci::app;
using namespace std;



class ParticlesApp : public App {
    //Funciones publicas.
    public:
        void setup();
	    void update();
	    void draw();
        void keyDown( KeyEvent event ); //Implementacion inputs de teclado.
    
    //Variables y objetos(miembros) publicos.
    public:
        ParticleSystem mParticleSystem; //Se declara un objeto(member) de la clase ParticleSystem con el nombre de mParticleSystem.
    
};

void ParticlesApp::setup(){
    int numParticle = 100;
    for( int i=0; i<numParticle; i++ ){
        
        ci::Rand::randomize(); //Genera una semilla aleatoria para sBase el cual a su vez es la "semilla" de randfloat. ver Rand.h. Asi la posicion inicial de las particulas es diferente.
        float x = ci::randFloat( 0.0f, getWindowWidth() );
        float y = ci::randFloat( 0.0f, getWindowHeight() );
        float radius = ci::randFloat( 5.0f, 15.0f );
        float mass = radius;
        float drag = 0.95f;
        Particle *particle = new Particle( vec2( x, y ), radius, mass, drag );
        mParticleSystem.addParticle( particle );
    }
}

void ParticlesApp::update(){
    mParticleSystem.update();
}

void ParticlesApp::draw(){
    gl::clear( Color( 0, 0, 0 ) );
    gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );
    mParticleSystem.draw();
}

//Eventos del teclado.
void ParticlesApp::keyDown( KeyEvent event )
{
	if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
			quit();
	}
}

CINDER_APP(ParticlesApp, RendererGl)


