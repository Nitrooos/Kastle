#include <iostream>
#include "Entity.hpp"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

Entity::Entity(ObjectBuffers *ob, ShaderProgram *sp, double x, double y, double z, GLuint tex0, GLuint tex1)
    : objectBuffers(ob), shaderProgram(sp), x(x), y(y), z(z), tex0(tex0), tex1(tex1) {
        updateMatrixM();
}

Entity::~Entity() { }

void Entity::onLoop() {
    // miejsce na kod na przyszłość
}

void Entity::onRender(const Camera &c, const Light &l, const Light &l1, const Material &m) {
    shaderProgram->use();

    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(c.getMatrixP()));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(c.getMatrixV()));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matrixM));

    glUniform4f(shaderProgram->getUniformLocation("Light0ambient"), l.ambient[0], l.ambient[1], l.ambient[2], l.ambient[3]);
    glUniform4f(shaderProgram->getUniformLocation("Light0diffuse"), l.diffuse[0], l.diffuse[1], l.diffuse[2], l.diffuse[3]);
    glUniform4f(shaderProgram->getUniformLocation("Light0specular"), l.specular[0], l.specular[1], l.specular[2], l.specular[3]);
    glUniform4f(shaderProgram->getUniformLocation("Light0position"), l.position[0], l.position[1], l.position[2], l.position[3]);

    glUniform4f(shaderProgram->getUniformLocation("Light01ambient"), l1.ambient[0], l1.ambient[1], l1.ambient[2], l1.ambient[3]);
    glUniform4f(shaderProgram->getUniformLocation("Light01diffuse"), l1.diffuse[0], l1.diffuse[1], l1.diffuse[2], l1.diffuse[3]);
    glUniform4f(shaderProgram->getUniformLocation("Light01specular"), l1.specular[0], l1.specular[1], l1.specular[2], l1.specular[3]);
    glUniform4f(shaderProgram->getUniformLocation("Light01position"), c.getX(), c.getY(), c.getZ(), 1.0);

    glUniform4f(shaderProgram->getUniformLocation("Material0emission"), m.emission[0], m.emission[1], m.emission[2], m.emission[3]);
    glUniform4f(shaderProgram->getUniformLocation("Material0ambient"), m.ambient[0], m.ambient[1], m.ambient[2], m.ambient[3]);
    glUniform4f(shaderProgram->getUniformLocation("Material0diffuse"), m.diffuse[0], m.diffuse[1], m.diffuse[2], m.diffuse[3]);
    glUniform4f(shaderProgram->getUniformLocation("Material0specular"), m.specular[0], m.specular[1], m.specular[2], m.specular[3]);
    glUniform1f(shaderProgram->getUniformLocation("Material0shininess"), m.shininess);

    //glUniform4f(shaderProgram->getUniformLocation("lightPosition"), 0, 10, 40, 1);
    glUniform4f(shaderProgram->getUniformLocation("lightPosition"), c.getX(), c.getY(), c.getZ(), 1);

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
