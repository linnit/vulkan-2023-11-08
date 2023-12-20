#pragma once

#include "FPSCamera.hpp"
#include "Render.hpp"
#include "Window.hpp"

class Application {
  public:
    Window window;
    Render render;
    FPSCamera camera;

    struct TickObject {
        float time;
        float timeDelta;
    } tickObject;

    float timeLast = 0.0f;

    Application()
        : camera(), window(camera, tickObject.timeDelta), render(window) {}
    void run();

  private:
    std::string applicationName = "Vulkan Test";

    void mainLoop();
    void cleanup();
    void tick();
};
