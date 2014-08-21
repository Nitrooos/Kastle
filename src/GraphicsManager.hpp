#ifndef GRAPHICSMANAGER
#define GRAPHICSMANAGER

#include <map>

#include "ShaderProgram.hpp"
#include "ObjectBuffers.hpp"

enum class ObjectType  : char { Red, PokojeKolumny, salaTronowa, ScianySufitPodloga, Okna, MebleNieb, MebleDrew, MebleCzer, MebleBiale };
enum class TextureType : char { Purple, Red, White, Wood };

class GraphicsManager {
    public:
        GraphicsManager();
        virtual ~GraphicsManager();

        ShaderProgram *getShader(ObjectType id);
        ObjectBuffers *getBuffer(ObjectType id);
        GLuint getTexture(TextureType id);
    private:
        struct ObjectData {
            ObjectData() { }
            ObjectData(ObjectType id);

            unique_ptr<ObjectBuffers> buffers;
            unique_ptr<ShaderProgram> shader;
        };

        GLuint readTextureFromFile(const string &filename);

        // Dla każdego typu obiektu bufory VBO, program cieniujący i VAO
        map<ObjectType, ObjectData> data;
        map<TextureType, GLuint> textures;
};

#endif /* end of include guard: GRAPHICSMANAGER */
