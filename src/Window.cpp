#include <iostream>

#include "Window.hpp"

void Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    glfwSetKeyCallback(window, keyCallback);
}

void Window::updateTitle(std::string title) {
    double currentTime = glfwGetTime();

    if (currentTime - lastUpdate >= 1.0f) {
        title += " | FPS: " + std::to_string(frameCount);
        frameCount = 0;
        lastUpdate = currentTime;

        if (fullscreen) {
            title += " | Fullscreen";
        } else {
            title += " | Windowed";
        }

        glfwSetWindowTitle(window, title.c_str());
    }

    frameCount++;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
        std::cout << "F11 pressed" << std::endl;
        if (app->fullscreen) {
            std::cout << "F11 pressed and fullscreen" << std::endl;
            app->fullscreen = false;
            glfwSetWindowMonitor(window, nullptr, 0, 0, WIDTH, HEIGHT,
                                 GLFW_DONT_CARE);
        } else {
            std::cout << "F11 pressed and not fullscreen" << std::endl;
            app->fullscreen = true;
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, WIDTH,
                                 HEIGHT, GLFW_DONT_CARE);
        }
    }
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width,
                                       int height) {
    auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

void Window::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
