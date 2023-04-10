#include <iostream>

#include "cinder/CinderImGui.h"
#include "cinder/app/RendererGl.h"
#include "cinder/app/App.h"

#include "Mode.h"
#include "CrazyParticles.h"
#include "ChangeSpeed.h"
#include "MultiShape.h"
#include "GravityFalls.h"
#include "ParticlesApp.h"

using namespace ci::app;

// Configuraciones de la aplicación.
void prepareSettings( App::Settings* settings);

class ParticleCollisions : public App {
   public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseDown(MouseEvent event) override;
    void mouseMove(MouseEvent event) override;
    void keyDown( KeyEvent event ) override;
    void imGuiUpdate();

   private:
    Mode *selectedMode;
};

void ParticleCollisions::setup() {
    ImGui::Initialize();
    selectedMode = new CrazyParticles();
    selectedMode->setup();
}

void ParticleCollisions::update() {
    selectedMode->update();
    imGuiUpdate();
}

void ParticleCollisions::draw() { 
    selectedMode->draw(); 
}

void ParticleCollisions::imGuiUpdate() {
    ImGui::Begin("Modos");
    ImGui::Separator();

    if (ImGui::Button("Crazy")) {
        selectedMode = new CrazyParticles();
        selectedMode->setup();
    }
    if (ImGui::Button("Multi Shape")) {
        selectedMode = new multi_shape::MultiShape();
        selectedMode->setup();
    }
    if (ImGui::Button("Change Speed")) {
        selectedMode = new change_speed::ChangeSpeed();
        selectedMode->setup();
    }
    if (ImGui::Button("Gravity Falls")) {
        selectedMode = new gravity_falls::GravityFalls();
        selectedMode->setup();
    }
    if (ImGui::Button("PerlinNoise")) {
        selectedMode = new ParticlesApp::ParticlesApp();
        selectedMode->setup();
    }
    ImGui::End();  // Draw the ImGui UI
}

void ParticleCollisions::mouseDown(MouseEvent event) {
    selectedMode->mouseDown(event);
}

void ParticleCollisions::mouseMove(MouseEvent event){
    selectedMode->mouseMove(event);
}

void ParticleCollisions::keyDown( KeyEvent event ){

	if( event.getCode() == KeyEvent::KEY_ESCAPE ) {                 //Si se preciona 'ESC' cierra el programa.
			quit();
	}
}

// Definicion de configuraciónes.
void prepareSettings(App::Settings *settings){

    settings->setWindowSize(1280, 640);                 //Tamaño de la pantalla.
    settings->setFullScreen( false   );                 //Si es pantalla completa.
    settings->setTitle( "Particle System ~ HPC" );      //Titulo de la ventana.
    settings->setFrameRate( 60 );                       //Frames maximos.
}


CINDER_APP(ParticleCollisions, RendererGl, prepareSettings)
