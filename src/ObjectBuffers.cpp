#include "ObjectBuffers.hpp"

ObjectBuffers::ObjectBuffers(unique_ptr<ShaderProgram> const& sp, const string &filename)
    : model(filename) {
    setupVBO();
    setupVAO(sp);
}

ObjectBuffers::~ObjectBuffers() {
    glDeleteBuffers(1, &bufVertices);
    glDeleteBuffers(1, &bufNormals);
    glDeleteBuffers(1, &bufTexCoords);

    glDeleteVertexArrays(1, &vao);
}

GLuint ObjectBuffers::getVAO() const {
    return vao;
}

int ObjectBuffers::getVertexCount() const {
    return model.vertexCount;
}

void ObjectBuffers::setupVBO() {
    bufVertices  = makeBuffer(model.vertices, sizeof(float)*4);   //Współrzędne wierzchołków
    bufTexCoords = makeBuffer(model.texture,  sizeof(float)*2);   //Współrzędne teksturowania
    bufNormals   = makeBuffer(model.normals,  sizeof(float)*4);   //Wektory normalne wierzchołków
}

GLuint ObjectBuffers::makeBuffer(void *data, int vertexSize) {
    GLuint handle;

    glGenBuffers(1,&handle);               // Wygeneruj uchwyt na Vertex Buffer Object (VBO), który będzie zawierał tablicę danych
    glBindBuffer(GL_ARRAY_BUFFER,handle);  // Uaktywnij wygenerowany uchwyt VBO
    glBufferData(GL_ARRAY_BUFFER, model.vertexCount*vertexSize, data, GL_STATIC_DRAW);        // Wgraj tablicę do VBO

    return handle;
}

void ObjectBuffers::setupVAO(unique_ptr<ShaderProgram> const& sp) {
    // Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej
    glGenVertexArrays(1, &vao);

    // Uaktywnij nowo utworzony VAO
    glBindVertexArray(vao);

    assignVBOtoAttribute(sp, "vertex",   bufVertices,  4);
    assignVBOtoAttribute(sp, "normal",   bufNormals,   4);
    assignVBOtoAttribute(sp, "texCoord", bufTexCoords, 2);

    // Zakończ modyfikację VAO
    glBindVertexArray(0);
}

void ObjectBuffers::assignVBOtoAttribute(unique_ptr<ShaderProgram> const& sp, const string &attributeName, GLuint bufVBO, int variableSize) {
    GLuint location = sp->getAttribLocation(attributeName.c_str());             // Pobierz numery slotów dla atrybutu
    glBindBuffer(GL_ARRAY_BUFFER, bufVBO);                                      // Uaktywnij uchwyt VBO
    glEnableVertexAttribArray(location);        // Włącz używanie atrybutu o numerze slotu zapisanym w zmiennej location
    glVertexAttribPointer(location, variableSize, GL_FLOAT, GL_FALSE, 0, NULL); // Dane do slotu location mają być brane z aktywnego VBO
}
