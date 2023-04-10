#pragma once
#include <iostream>

#include "cinder/app/App.h"

class Mode {
   public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void mouseDown(ci::app::MouseEvent event){};
    virtual void mouseMove(ci::app::MouseEvent event){};
};
