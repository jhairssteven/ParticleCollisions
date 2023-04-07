//Declaracion de pedendencias.
#include "cinder/app/App.h" //Para la declaracion de la clase principal y sus funciones.
#include "cinder/app/RendererGl.h" //Para renderizar.

#include "cinder/Perlin.h" //Header para PerlinNoise.

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
        float mFrequency;
        Perlin mPerlin;
        ParticleSystem mParticleSystem; //Se declara un objeto(member) de la clase ParticleSystem con el nombre de mParticleSystem.
    
};

void ParticlesApp::setup(){

    mFrequency = 0.01f;
    mPerlin = Perlin();

    int numParticle = 10;
    for( int i=0; i<numParticle; i++ ){
        mParticleSystem.createParticle();
    }
}

void ParticlesApp::update(){
    //cout <<(getElapsedSeconds())<< "\n\t~Sin:"<<sin(getElapsedSeconds())<< endl;

    vec2 oscilationVec;
    oscilationVec.x = sin(getElapsedSeconds()*0.6f)*0.2f; //Genera un vector de oscilaciones apartir de una onda determinada por el tiempo trancurrido(Radianes). El primer numero esta relacionado a la longitud y el segundo a la amplitud.
    oscilationVec.y = sin(getElapsedSeconds()*0.6f)*0.2f; //La funcion getElapsedSeconds() retorna el tiempo que ha transcurrido la ejecución en segundos. 

    //for para iterar cada particula en el sistema, primero se define un vector que contiene variables de tipo Particle*.
    std::vector<Particle*>::iterator it; 
    for(it = mParticleSystem.particles.begin(); it != mParticleSystem.particles.end(); ++it ) {

        if((*it)->position.x > getWindowWidth() || (*it)->position.y > getWindowHeight()){
            //Comprueba que la particula siga en pantalla y si no la destruye para crear otra en pantalla.
            mParticleSystem.destroyParticle((*it));
            mParticleSystem.createParticle();
            continue;
        }
        else{
            vec2 windForce = mPerlin.dfBm( (*it)->position * mFrequency );
            (*it)->forces += windForce * 0.2f;
            (*it)->forces += oscilationVec;
        }
    }

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


