#pragma once

#include <glm/glm.hpp> // glm::mat4
#include <string>      // std::string

#include "Model.hpp"

class Skull : public Model {
  protected:
    static bool loadedModel;
    static int textureId;
    std::string MODEL_PATH;
    std::string TEXTURE_PATH;

  private:
    static int totalNbSkulls;
    static int vertexOffset;
    static int indexOffset;

  public:
    Skull(glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
          bool createRigidBody = true, bool matrixOffset = false,
          glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

    void loadModel();

    std::string getTexturePath() { return TEXTURE_PATH; }

    int getModelCount() { return totalNbSkulls; }
    int getTextureId() {
        // std::cout << "bridge getTextureId: " << textureId << std::endl;
        return textureId;
    }
    void setTextureId(int id) {
        // std::cout << "bridge setTextureId: " << id << std::endl;
        textureId = id;
    }
    int getVertexOffset() { return vertexOffset; }
    void setVertexOffset(int offset) { vertexOffset = offset; }
    int getIndexOffset() { return indexOffset; }
    void setIndexOffset(int offset) { indexOffset = offset; }
};