#ifndef OBJECTBUFFERS
#define OBJECTBUFFERS

#include <memory>
#include <string>
#include <GL/glew.h>

#include "ShaderProgram.hpp"

using namespace std;

enum class ObjectType : char { Teapot };

struct ObjectBuffers {
        ObjectBuffers(const string &filename);
        ObjectBuffers(unique_ptr<ShaderProgram> const& sp, float *vert, float *norm, float *col, int vertCount);
        ~ObjectBuffers();

        GLuint vao,                     // uchwyt na VAO
               bufVertices,             // bufory wierzchołków
               bufNormals,              // wektorów normalnych
               bufColors;               // kolorów

        float *vertices{nullptr},       // wskaźniki na tablice wierzchołków
              *normals{nullptr},        // wektorów normalnych
              *colors{nullptr};         // kolorów
        int vertexCount{0};
    private:
        void loadFromFile(const string &filename);
        // Funkcje z kodu Witka
        GLuint makeBuffer(void *data, int vertexSize);
        void setupVBO();
        void setupVAO(unique_ptr<ShaderProgram> const& sp);
        void assignVBOtoAttribute(unique_ptr<ShaderProgram> const& sp, char* attributeName, GLuint bufVBO, int variableSize);
};

#endif /* end of include guard: OBJECTBUFFERS */
