#include "GraphicsManager.hpp"

GraphicsManager::ObjectData::ObjectData(ObjectType id) {
    switch (id) {
        case ObjectType::Teapot:
            shader.reset (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl"));
            buffers.reset(new ObjectBuffers(shader, "models/teapot.obj"));
            break;
    }
}

GraphicsManager::GraphicsManager() {
    data.emplace(ObjectType::Teapot, ObjectData(ObjectType::Teapot));
}

GraphicsManager::~GraphicsManager() { }

ShaderProgram *GraphicsManager::getShader(ObjectType id) {
   return data[id].shader.get();
}

ObjectBuffers *GraphicsManager::getBuffer(ObjectType id) {
   return data[id].buffers.get();
}
