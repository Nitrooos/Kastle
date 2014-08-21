#include "GraphicsManager.hpp"
#include "Tga.hpp"

#include <iostream>

GraphicsManager::ObjectData::ObjectData(ObjectType id) {
    switch (id) {
        case ObjectType::Red:
            shader.reset (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl"));
            buffers.reset(new ObjectBuffers(shader, "models/czerwone.obj"));
            break;
        case ObjectType::PokojeKolumny:
            shader.reset (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl"));
            buffers.reset(new ObjectBuffers(shader, "models/PokojeKolumny.obj"));
            break;
        case ObjectType::salaTronowa:
            shader.reset (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl"));
            buffers.reset(new ObjectBuffers(shader, "models/salaTronowa.obj"));
            break;
        case ObjectType::ScianySufitPodloga:
            shader.reset (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl"));
            buffers.reset(new ObjectBuffers(shader, "models/ScianySufitPodloga.obj"));
            break;
    }
}

GraphicsManager::GraphicsManager() {
    data.emplace(ObjectType::Red, ObjectData(ObjectType::Red));
    data.emplace(ObjectType::PokojeKolumny,   ObjectData(ObjectType::PokojeKolumny));
    data.emplace(ObjectType::salaTronowa,   ObjectData(ObjectType::salaTronowa));
    data.emplace(ObjectType::ScianySufitPodloga,   ObjectData(ObjectType::ScianySufitPodloga));

    textures.emplace(TextureType::Metal, readTextureFromFile("data/textures/metal.tga"));
    textures.emplace(TextureType::Brick, readTextureFromFile("data/textures/bricks.tga"));
    textures.emplace(TextureType::Sky,   readTextureFromFile("data/textures/sky.tga"));
    textures.emplace(TextureType::Stone, readTextureFromFile("data/textures/stones.tga"));
    textures.emplace(TextureType::Purple,readTextureFromFile("data/textures/purple.tga"));
    textures.emplace(TextureType::Red, readTextureFromFile("data/textures/red.tga"));
}

GraphicsManager::~GraphicsManager() {
    for (auto &x : textures) {
        glDeleteTextures(1, &x.second);
    }
}

ShaderProgram *GraphicsManager::getShader(ObjectType id) {
   return data[id].shader.get();
}

ObjectBuffers *GraphicsManager::getBuffer(ObjectType id) {
   return data[id].buffers.get();
}

GLuint GraphicsManager::getTexture(TextureType id) {
    return textures[id];
}

GLuint GraphicsManager::readTextureFromFile(const string &filename) {
    GLuint tex;
    TGAImg img;

    glActiveTexture(GL_TEXTURE0);
    if (img.Load(filename) == IMG_OK) {
        glGenTextures(1, &tex);                     // Zainicjuj uchwyt tex
        glBindTexture(GL_TEXTURE_2D, tex);          // Przetwarzaj uchwyt tex
        if (img.GetBPP() == 24)                     // Obrazek 24bit
            glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0, GL_RGB,GL_UNSIGNED_BYTE, img.GetImg());
        else if (img.GetBPP() == 32)                // Obrazek 32bit
                glTexImage2D(GL_TEXTURE_2D, 0, 4, img.GetWidth(), img.GetHeight(), 0, GL_RGBA,GL_UNSIGNED_BYTE, img.GetImg());
        else {
            // InvalidImageFormatException
        }
    } else {
        // LoadImageErrorException
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return tex;
}
