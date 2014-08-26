#include "GraphicsManager.hpp"
#include "Tga.hpp"

#include <iostream>

GraphicsManager::GraphicsManager() { }

void GraphicsManager::onLoad() {
    shaders.emplace(ShaderType::Standard,
                    unique_ptr<ShaderProgram> (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl")));
    notifyObservers(14.29, false);

    shaders.emplace(ShaderType::Standard2,
                    unique_ptr<ShaderProgram> (new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader2.glsl")));
    notifyObservers(14.29, false);

    objects.emplace(ObjectType::Red,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard2], "models/czerwone.obj")));
    notifyObservers(14.29);

    objects.emplace(ObjectType::PokojeKolumny,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/PokojeKolumny.obj")));
    notifyObservers(14.29);

    objects.emplace(ObjectType::salaTronowa,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/salaTronowa.obj")));
    notifyObservers(14.29);

    objects.emplace(ObjectType::ScianySufitPodloga,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/ScianySufitPodloga.obj")));
    notifyObservers(14.29);

    objects.emplace(ObjectType::Okna,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/okna.obj")));
    notifyObservers(14.29);
    objects.emplace(ObjectType::Drzwi,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/drzwi.obj")));
    notifyObservers(14.29);
    /*objects.emplace(ObjectType::MebleNieb,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/mebleNieb.obj")));
    objects.emplace(ObjectType::MebleDrew,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/mebleDrew.obj")));
    objects.emplace(ObjectType::MebleCzer,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/mebleCzer.obj")));
    objects.emplace(ObjectType::MebleBiale,
                    unique_ptr<ObjectBuffers> (new ObjectBuffers(shaders[ShaderType::Standard], "models/mebleBiale.obj")));*/
    textures.emplace(TextureType::Purple,readTextureFromFile("data/textures/purple.tga"));
    textures.emplace(TextureType::Red,   readTextureFromFile("data/textures/red.tga"));
    textures.emplace(TextureType::White, readTextureFromFile("data/textures/white.tga"));
    textures.emplace(TextureType::Wood,  readTextureFromFile("data/textures/wood.tga"));
}

GraphicsManager::~GraphicsManager() {
    for (auto &x : textures) {
        glDeleteTextures(1, &x.second);
    }
}

ShaderProgram *GraphicsManager::getShader(ShaderType id) {
   return shaders[id].get();
}

ObjectBuffers *GraphicsManager::getBuffer(ObjectType id) {
   return objects[id].get();
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
