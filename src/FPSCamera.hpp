#pragma once

#include <glm/glm.hpp> // glm::mat4
#include <glm/gtc/quaternion.hpp>
#include <iostream> // std::cout

class FPSCamera {
    // pitch (rot around x in radians),
    // yaw (rot around y in radians),
    // roll (rot around z in radians)
    float pitch = 0.0f;
    float yaw = -90.0f;
    // float roll = 0.0f;

    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);

  private:
    float fov;
    float znear, zfar;
    float movementSpeed = 2.5f;

    void updateViewMatrix() {
        glm::vec3 cameraTarget = cameraPos + cameraFront;

        // ubo.view = glm::lookAt(
        //     // eye: Camera position in world space
        //     glm::vec3(0.0f, 1.0f, 3.0f), // cameraPo
        //     // center: Point in world space to look at
        //     glm::vec3(0.0f, 0.0f, 0.0f), // cameraTarget
        //     // up: Normalized vector pointing up
        //     glm::vec3(0.0f, 1.0f, 0.0f)  // cameraUp
        // );

        matrices.view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
    }

  public:
    FPSCamera() {
        std::cout << "FPSCamera constructor" << std::endl;
        updateViewMatrix();
    }

    glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    struct Matrices {
        glm::mat4 projection;
        glm::mat4 view;
    } matrices;

    struct {
        double x = 0.0;
        double y = 0.0;
        double lastX = 0.0;
        double lastY = 0.0;
        double xoffset = 0.0;
        double yoffset = 0.0;
        bool firstMouse = true;
        float sensitivity = 0.1f;
    } mouse;

    struct {
        bool forward = false;
        bool back = false;
        bool left = false;
        bool right = false;
        bool shift = false;
        bool space = false;
    } keys;

    void setPerspective(float fov, float aspect, float znear, float zfar) {
        this->fov = fov;
        this->znear = znear;
        this->zfar = zfar;

        matrices.projection =
            glm::perspective(glm::radians(fov), aspect, znear, zfar);

        // flip y axis
        matrices.projection[1][1] *= -1.0f;
    };

    void updateCameraPos(float timeDelta) {
        float velocity = movementSpeed * timeDelta;

        if (keys.forward) {
            cameraPos += cameraFront * velocity;
        }
        if (keys.back) {
            cameraPos -= cameraFront * velocity;
        }

        if (keys.left) {
            cameraPos -=
                glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
        }
        if (keys.right) {
            cameraPos +=
                glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
        }

        if (keys.shift) {
            cameraPos -= cameraUp * velocity;
        }
        if (keys.space) {
            cameraPos += cameraUp * velocity;
        }

        updateViewMatrix();
    }

    void updateCameraDirection() {
        // -= to invert mouse y movement
        pitch -= mouse.yoffset;
        yaw += mouse.xoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraDirection.y = sin(glm::radians(pitch));
        cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(cameraDirection);

        updateViewMatrix();
    }

    void setMovementSpeed(float speed) { movementSpeed = speed; }

    void setCameraPos(glm::vec3 pos) {
        cameraPos = pos;
        updateViewMatrix();
    }

    void setCameraDirection(glm::vec3 dir) {
        cameraDirection = dir;
        updateViewMatrix();
    }

    void updateFOV(float inc) {
        this->fov += inc;

        if (this->fov < 10.0f)
            this->fov = 10.0f;

        if (this->fov > 145.0f)
            this->fov = 145.0f;

        // [TODO] save aspect ratio instead of hardcoding
        setPerspective(fov, (float)1920 / (float)1080, znear, zfar);
    }
};
