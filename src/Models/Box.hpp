#pragma once

#include <glm/glm.hpp> // glm::mat4
#include <string>      // std::string

#include "Model.hpp"

class Box : public Model {
  protected:
    static int textureId;

  private:
    static int totalNbBoxes;
    static int vertexOffset;
    static int indexOffset;
    static int indicesCount;

  public:
    Box(glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
        bool matrixOffset = false,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        bool createRigidBody = true,
        rp3d::BodyType bodyType = rp3d::BodyType::DYNAMIC,
        rp3d::PhysicsWorld* world = nullptr,
        rp3d::PhysicsCommon* physicsCommon = nullptr);

    int getModelCount() { return totalNbBoxes; }
    int getTextureId() { return textureId; }
    void setTextureId(int id) { textureId = id; }
    int getVertexOffset() { return vertexOffset; }
    void setVertexOffset(int offset) {
        std::cout << "box setVertexOffset: " << offset << std::endl;
        vertexOffset = offset;
    }
    int getIndexOffset() { return indexOffset; }
    void setIndexOffset(int offset) { indexOffset = offset; }
    int getIndicesCount() { return indicesCount; }
    void setIndicesCount(int count) { indicesCount = count; }
};
