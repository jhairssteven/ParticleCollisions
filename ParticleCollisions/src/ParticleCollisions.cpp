#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

using namespace ci::app;

class ParticleCollisions : public App {
   public:
    void setup() override;
    void update() override;
    void draw() override;
};

void ParticleCollisions::setup() {}

void ParticleCollisions::update() {}

void ParticleCollisions::draw() {}

CINDER_APP(ParticleCollisions, RendererGl)
