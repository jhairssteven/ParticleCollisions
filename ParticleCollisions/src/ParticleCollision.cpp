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

using namespace ci::app;

class ParticleCollisions : public App {
   public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseDown(MouseEvent event) override;
    void imGuiUpdate();
    float radius; // Radio de la partícula
    float mass; // Masa de la partícula
    int Nump;
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

void ParticleCollisions::draw() { selectedMode->draw(); }

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
    if (ImGui::Button("Select Param")) {
        ImGui::Separator();
        ImGui::DragFloat("Radio", &radius, 0.1f, 5.0f, 20.0f);
        ImGui::DragFloat("Masa", &mass, 0.1f, 0.5f, 2.0f);
        ImGui::DragInt("Numero", &Nump, 1.0f, 2, 50);

        selectedMode = new Select_Param::SelectParam();
        Select_Param.radius2 = raius;
        Select_Param.mass2 = mass;
        Select_Param.Nump2 = Nump;
       
        selectedMode->setup();
    }
    ImGui::End();  // Draw the ImGui UI
}

void ParticleCollisions::mouseDown(MouseEvent event) {
    selectedMode->mouseDown(event);
}

CINDER_APP(ParticleCollisions, RendererGl)
