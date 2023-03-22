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
        void mouseMove(MouseEvent event);
        void mouseDown(MouseEvent event);
    
    //Variables y objetos(miembros) publicos.
    public:
        ParticleSystem mParticleSystem; //Se declara un objeto(member) de la clase ParticleSystem con el nombre de mParticleSystem.

        //Aplicando fuerzas de repulsion y atraccion.
        vec2 attrPosition;
        float attrFactor, repulsionFactor, repulsionRadius;
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

    //Inicializando las fuerzas de repulsion y atraccion.
    attrPosition = getWindowCenter();
    attrFactor = 0.000005f;
    repulsionRadius = 5.f;
    repulsionFactor = -0.0005f;
}

void ParticlesApp::update(){
    for(std::vector<Particle*>::iterator it = mParticleSystem.particles.begin(); it != mParticleSystem.particles.end(); ++it ){
        vec2 attrForce = attrPosition - (*it)->position;
        attrForce *= attrFactor;
        (*it)->forces += attrForce;
    }

    mParticleSystem.update();
}

void ParticlesApp::draw(){
    gl::clear( Color( 0, 0, 0 ) );
    gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );
    mParticleSystem.draw();
}

//Eventos del teclado.
void ParticlesApp::keyDown(KeyEvent event )
{
	if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
			quit();
	}
}

//Eventos de mouse.
void ParticlesApp::mouseMove(MouseEvent event){
    attrPosition.x = event.getPos().x;
    attrPosition.y = event.getPos().y;
}

void ParticlesApp::mouseDown(MouseEvent event){
    for( std::vector<Particle*>::iterator it = mParticleSystem.particles.begin(); it != mParticleSystem.particles.end(); ++it ) {
        //vec2 repulsionForce = (*it)->position - glm::intBitsToFloat(event.getPos()); //Genera error de type, por eso se coloca una conversion.
        vec2 repulsionForce = (*it)->position - vec2(float(event.getPos().x), float(event.getPos().y));
        repulsionForce = glm::normalize(repulsionForce) * math<float>::max(0.f, repulsionRadius - repulsionForce.length());
        (*it)->forces += repulsionForce;
    }
}

CINDER_APP(ParticlesApp, RendererGl)


