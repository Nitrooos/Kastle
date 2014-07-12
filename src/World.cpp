#include "World.hpp"
#include "App.hpp"
#include "Teapot.hpp"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

World::World()
{
    matP = perspective(45.0f, (float)App::getWindowWidth()/(float)App::getWindowHeight(), 1.0f, 100.0f);
    matV = lookAt(vec3(0.0f, 0.0f, 7.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    matM = rotate(mat4(1.0f), 0.0f, vec3(0.5f, 1.0f, 0.0f));

    /*Object obj(grMananger.getBuffer(ObjectType::Teapot),
               grMananger.getShader(ObjectType::Teapot), 0, 0, 0);
    objects.push_back(obj);*/

    onInit();
}

World::~World() { }

void World::onEvent(Event e) {
    // zakładamy, że obiekty mogą reagować tylko na wciśnięcie klawisza
    if (e.type == Event::KeyPressed) {
        // sprawdzamy czy nie trzeba zaktualizować obiektu kamery
        switch (e.key.code) {
           default:
                break;
        }
    }
}

void World::onLoop() {
    // tutaj miejsce na kod w przyszłości
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    //~ for (auto &x : objects)
        //~ x.onRender(camera);

    shaderProgram->use();

    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(matP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(matV));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matM));

    // Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
    glBindVertexArray(objectBuffers->vao);

    // Narysowanie obiektu
    glDrawArrays(GL_TRIANGLES, 0, objectBuffers->vertexCount);

    // Posprzątanie po sobie
    glBindVertexArray(0);
}

void World::onInit() {
    shaderProgram.reset(new ShaderProgram("src/shaders/vshader.glsl", nullptr, "src/shaders/fshader.glsl"));
    objectBuffers.reset(new ObjectBuffers(shaderProgram, teapotVertices, teapotNormals, teapotColors, teapotVertexCount));

    glEnable(GL_DEPTH_TEST);
}
