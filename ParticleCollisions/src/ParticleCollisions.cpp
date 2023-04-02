#include <iostream>

#include "cinder/CinderImGui.h"
#include "cinder/app/RendererGl.h"
#include "cinder/app/App.h"

#include "Mode.h"
#include "CrazyParticles.h"
#include "ChangeSpeed.h"
#include "MultiShape.h"
#include "GravityFalls.h"
#include "SelectParam.h"
#include "ParticlesApp.h"

using namespace ci::app;

class ParticleCollisions : public App {
   public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseDown(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void mouseMove(MouseEvent event) override;
    void imGuiUpdate();

   private:
    Mode *selectedMode;
};

void ParticleCollisions::setup() {
    ImGui::Initialize();
    selectedMode = new crazy_particles::CrazyParticles();
    selectedMode->setup();
}

void ParticleCollisions::update() {
    selectedMode->update();
    imGuiUpdate();
}

void ParticleCollisions::draw() { selectedMode->draw(); }

void ParticleCollisions::imGuiUpdate() {
    ImGui::Begin("Modos");
    ImGui::Separator();

    if (ImGui::Button("Crazy")) {
        selectedMode = new crazy_particles::CrazyParticles();
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
    if (ImGui::Button("Select Param")) {
        selectedMode = new select_Param::SelectParam();       
        selectedMode->setup();
    }
    if (ImGui::Button("CookBook")) {
        selectedMode = new particles_app::ParticlesApp();       
        selectedMode->setup();
    }
    ImGui::End();  // Draw the ImGui UI
}

void ParticleCollisions::mouseDown(MouseEvent event) {
    selectedMode->mouseDown(event);
}
//Implementacion inputs de teclado.
void ParticleCollisions::keyDown( KeyEvent event) {
    /* selectedMode->keyDown(event); */
    if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
        quit();
	}
};
void ParticleCollisions::mouseMove(MouseEvent event) {
    selectedMode->mouseMove(event);
};

CINDER_APP(ParticleCollisions, RendererGl)
