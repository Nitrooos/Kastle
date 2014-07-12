#ifndef GRAPHICSMANAGER
#define GRAPHICSMANAGER

#include <map>

#include "ShaderProgram.hpp"
#include "ObjectBuffers.hpp"

class GraphicsManager {
    public:
        GraphicsManager();
        virtual ~GraphicsManager();

        ShaderProgram *getShader(ObjectType id);
        ObjectBuffers *getBuffer(ObjectType id);
    private:
        struct ObjectData {
            ObjectData() { }
            ObjectData(ObjectType id);

            unique_ptr<ObjectBuffers> buffers;
            unique_ptr<ShaderProgram> shader;
        };

        // Dla każdego typu obiektu bufory VBO, program cieniujący i VAO
        map<ObjectType, ObjectData> data;
};

#endif /* end of include guard: GRAPHICSMANAGER */
