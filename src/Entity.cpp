#include "Entity.hpp"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

Entity::Entity(ObjectBuffers *ob, ShaderProgram *sp, double x, double y, double z)
    : objectBuffers(ob), shaderProgram(sp), x(x), y(y), z(z) {
        updateMatrixM();
}

Entity::~Entity() { }

void Entity::onLoop() {
    // miejsce na kod na przyszłość
}

void Entity::onRender(const Camera &c) {
    shaderProgram->use();

    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(c.getMatrixP()));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(c.getMatrixV()));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matrixM));

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
    matrixM = rotate(matrixM, angle, vec3(0.5f, 1.0f, 0.3f));
}
