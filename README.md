# ParticleCollisions
Implementation of particle systems with rendering and texturing for collision simulation, using the [Cinder](https://libcinder.org/) C++ library.

# Requirements
* Linux
* Cinder - [How to install on Linux?](https://libcinder.org/docs/guides/linux-notes/ubuntu.html)

# How to create a new mode?
## Creating the main file
Create a `.h` file in the [include](../DrivingCinder/ParticleCollisions/include/) folder. If your class is named `NewMode`, it should inherit from the abstract class [`Mode`](../DrivingCinder/ParticleCollisions/include/Mode.h). The minimum class structure should be:

```cpp
namespace new_mode {
    class NewMode : public Mode {
    public:
        void setup();
        void update();
        void draw();
    };
}
```
## Startup
- To integrate the functionalities of the new mode, include the `NewMode.h` file in the main file ([ParticleCollisions.cpp](./ParticleCollisions/src/ParticleCollisions.cpp)) as a header file.
- In the [`imGuiUpdate()`](./ParticleCollisions/src/ParticleCollisions.cpp) function, include a new button with its initialization as follows:

```cpp
void ParticleCollisions::imGuiUpdate() {
    ImGui::Begin("Modes");
    ImGui::Separator();

    ...

    // New Mode
    if (ImgGui::Button("New Mode")) {
        selectedMode = new new_mode::NewMode();
        selectedMode->setup();
    }

    ImGui::End();  // Draw the ImGui UI
}
```

# Implemented modes
| ![CrazyParticles](./ParticleCollisions/assets/Crazy.png)  | ![ChangeSpeedAudioBlocks](./ParticleCollisions/assets/Change%20speed.png) | ![MultiShape](./ParticleCollisions/assets/Multi%20shape.png) |
|:---:|:---:|:---:|
| [CrazyParticles](./ParticleCollisions/include/CrazyParticles.h) |  [ChangeSpeed](./ParticleCollisions/include/ChangeSpeed.h) |  [MultiShape](./ParticleCollisions/include/MultiShape.h) | 

| ![SelectParam](./ParticleCollisions/assets/SelectParam.png) | ![GravityFalls](./ParticleCollisions/assets/Gravity%20Falls.png) |  ![CookBook](./ParticleCollisions/assets/CookBook.png)|
|:---:|:---:|:---:|
| [SelectParam](./ParticleCollisions/include/SelectParam.h) | [GravityFalls](./ParticleCollisions/include/GravityFalls.h) | [CookBook](./ParticleCollisions/include/ParticlesApp.h) |

# How to use it?
```shell
ParticleCollisions$ make -f makefile.mk
