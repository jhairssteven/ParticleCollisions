#include "cinder/CinderImGui.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "Mode.h"
#include "CrazyParticles.h"
#include "MultiShape.h"

using namespace ci::app;

class ParticleCollisions : public App {
   public:
    void setup() override;
    void update() override;
    void draw() override;

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
    ImGui::End();  // Draw the ImGui UI
}

CINDER_APP(ParticleCollisions, RendererGl)
