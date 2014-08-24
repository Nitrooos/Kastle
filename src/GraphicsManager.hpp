#ifndef GRAPHICSMANAGER
#define GRAPHICSMANAGER

#include <map>

#include "Observer.hpp"
#include "ShaderProgram.hpp"
#include "ObjectBuffers.hpp"

enum class ObjectType  : char { Red, PokojeKolumny, salaTronowa, ScianySufitPodloga, Okna, MebleNieb, MebleDrew, MebleCzer, MebleBiale };
enum class ShaderType : char { Standard, Standard2 };
enum class TextureType : char { Purple, Red, White, Wood };

class GraphicsManager : public Observable {
    public:
        GraphicsManager();
        virtual ~GraphicsManager();

        void onLoad();

        ShaderProgram *getShader(ShaderType id);
        ObjectBuffers *getBuffer(ObjectType id);
        GLuint getTexture(TextureType id);
    private:
        GLuint readTextureFromFile(const string &filename);

        map<ShaderType, unique_ptr<ShaderProgram>> shaders;
        map<ObjectType, unique_ptr<ObjectBuffers>> objects;
        map<TextureType, GLuint> textures;
};

#endif /* end of include guard: GRAPHICSMANAGER */
