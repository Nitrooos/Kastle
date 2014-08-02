#ifndef OBJECTBUFFERS
#define OBJECTBUFFERS

#include <memory>
#include <string>
#include <GL/glew.h>

#include "ShaderProgram.hpp"
#include "OBJLoader.hpp"

using namespace std;

class ObjectBuffers {
    public:
        ObjectBuffers(unique_ptr<ShaderProgram> const& sp, const string &filename);
        ~ObjectBuffers();

        GLuint getVAO() const;
        int getVertexCount() const;
    private:
        void loadFromFile(const string &filename);
        // Funkcje z kodu Witka
        GLuint makeBuffer(void *data, int vertexSize);
        void setupVBO();
        void setupVAO(unique_ptr<ShaderProgram> const& sp);
        void assignVBOtoAttribute(unique_ptr<ShaderProgram> const& sp, const string &attributeName, GLuint bufVBO, int variableSize);

        OBJLoader model;                // dane modelu wczytane z pliku obj
        GLuint vao,                     // uchwyt na VAO
               bufVertices,             // bufory wierzchołków
               bufNormals,              // wektorów normalnych
               bufTexCoords;            // współrzędnych teksturowania
};

#endif /* end of include guard: OBJECTBUFFERS */
