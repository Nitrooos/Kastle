#include <iostream>
#include "Entity.hpp"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

float polysk=0.0;
float stopienPolysku=0.01;
float red=0.0,blue=0.5, green=1.0;
float stopienRed=0.01, stopienBlue=0.01, stopienGreen=0.01;
int kierunek;

Entity::Entity(ObjectBuffers *ob, ShaderProgram *sp, double x, double y, double z, GLuint tex0, GLuint tex1) 
    : objectBuffers(ob), shaderProgram(sp), x(x), y(y), z(z), tex0(tex0), tex1(tex1) {
        updateMatrixM();
}

Entity::~Entity() { }

void Entity::onLoop() {
    // miejsce na kod na przyszłość
}

void Entity::onRender(const Camera &c) {
    red=0.5;
    green=0.5;
    blue=0.5;
    polysk=100;
    /*
    if(!w.drugs) cout<<"1";

    if (polysk>5) stopienPolysku=-0.01; 
    if (polysk<=0.01) stopienPolysku=0.01;
    polysk+=stopienPolysku;

    kierunek = rand() % 2;
    if (kierunek==0) red+=stopienRed; else red-=stopienRed;
    kierunek = rand() % 2;
    if (kierunek==0) blue+=stopienBlue; else blue-=stopienBlue;
    kierunek = rand() % 2;
    if (kierunek==0) green+=stopienGreen; else green-=stopienGreen;

    if (red>=1.0) red=0.0;
    if (red<=0.0) red=0.0;
    if (blue>=1.0) blue=1.0;
    if (blue<=0.0) blue=0.0;
    if (green>=1.0) green=1.0;
    if (green<=0.0) green=0.0;
    //std::cout<<red<<blue<<green;*/


    shaderProgram->use();

    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(c.getMatrixP()));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(c.getMatrixV()));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matrixM));

    //glUniform4f(shaderProgram->getUniformLocation("lightPosition"), 0, 10, 40, 1);
    glUniform4f(shaderProgram->getUniformLocation("lightPosition"), c.getX(), c.getY(), c.getZ(), 1);
    glUniform4f(shaderProgram->getUniformLocation("dragi1"), red, green, blue, 1);
    glUniform4f(shaderProgram->getUniformLocation("dragi2"), green, blue, red, 1);
    glUniform4f(shaderProgram->getUniformLocation("dragi3"), blue, red, green, 1);
    glUniform1f(shaderProgram->getUniformLocation("polysk"), polysk);

    glUniform1i(shaderProgram->getUniformLocation("textureMap0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);

    if (tex1 != 0) {
        glUniform1i(shaderProgram->getUniformLocation("textureMap1"), 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex1);
    }

    // Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powiązań slotów atrybutów z tablicami z danymi
    glBindVertexArray(objectBuffers->getVAO());

    // Narysowanie obiektu
    glDrawArrays(GL_TRIANGLES, 0, objectBuffers->getVertexCount());

    // Posprzątanie po sobie
    glBindVertexArray(0);
}

void Entity::move(double movX, double movY, double movZ) {
    x += movX;
    y += movY;
    z += movZ;
    updateMatrixM();
}

void Entity::setPosition(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    updateMatrixM();
}

void Entity::roll(double rotAngle) {
    angle += rotAngle;
    updateMatrixM();
}

void Entity::setAngle(double angle) {
    this->angle = angle;
    updateMatrixM();
}

void Entity::updateMatrixM() {
    matrixM = translate(mat4(1.0f), vec3(x, y, z));
    matrixM = rotate(matrixM, angle, vec3(0.0f, 1.0f, 0.0f));
}
