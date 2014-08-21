#include "World.hpp"
#include "App.hpp"

#include <iostream>

World::World() {
    collisionMap.loadFromFile("data/maps/collision.png");

    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Red),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Red)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::PokojeKolumny),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::salaTronowa),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::ScianySufitPodloga),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Okna),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Red)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::MebleNieb),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::MebleDrew),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Wood)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::MebleCzer),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Red)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::MebleBiale),
                             grMananger.getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::White)}
                     );
    onInit();
}

World::~World() { }

void World::onKeyboardEvent(Event e) {
    // zakładamy, że obiekty mogą reagować tylko na wciśnięcie klawisza
    switch (e.type) {
        case Event::KeyPressed:
            switch (e.key.code) {
                case Keyboard::W: go     = -sensitivity; break;
                case Keyboard::S: go     =  sensitivity; break;
                case Keyboard::A: side   = -sensitivity; break;
                case Keyboard::D: side   =  sensitivity; break;
                case Keyboard::K: height =  sensitivity; break;
                case Keyboard::M: height = -sensitivity; break;
                case Keyboard::X: rotateObjects = !rotateObjects; break;
            }
            break;
        case Event::KeyReleased:
            switch (e.key.code) {
                case Keyboard::W: case Keyboard::S: go     = 0.0f; break;
                case Keyboard::A: case Keyboard::D: side   = 0.0f; break;
                case Keyboard::K: case Keyboard::M: height = 0.0f; break;
            }
            break;
    }
}

void World::onMouseEvent(const Vector2<int> &pos) {
    int diffX = App::getWindowCenterX() - pos.x,
        diffY = App::getWindowCenterY() - pos.y;

    camera.roll(diffX/400.0f, diffY/400.0f);
}

void World::onLoop() {
    if (this->rotateObjects) {
        float angle = 0.1f;
        for (auto &x : objects) {
            x.roll(angle);
            angle *= -1;
        }
    }

    float xShift = -camera.getZShift(this->go) + camera.getXShift(this->side),
          yShift =  this->height,
          zShift =  camera.getXShift(this->go) + camera.getZShift(this->side);

    if ((xShift || yShift || zShift) && !isCollision(xShift, yShift, zShift))
        camera.movEye(xShift, yShift, zShift);

    /*if (this->go != 0.0f || this->height != 0.0f)
        camera.movEye(-camera.getZShift(this->go), this->height, camera.getXShift(this->go));
    if (this->side != 0.0f)
        camera.movEye(camera.getXShift(this->side), 0, camera.getZShift(this->side));*/

    camera.writeCoordinates();
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    for (auto &x : objects)
        x.onRender(camera);
}

void World::onInit() {
    glEnable(GL_DEPTH_TEST);
}

bool World::isCollision(float xShift, float yShift, float zShift) const {
    // zamek ma wymiary 177x120 jednostek
    constexpr float w = 3.28f,
                    p1 = 65.0f,
                    p2 = 50.0f;
    float imageCoordX = (camera.getX() + xShift + p1)*w,
          imageCoordZ = (camera.getZ() + zShift + p2)*w; 
    if (imageCoordX > collisionMap.getSize().x || imageCoordZ > collisionMap.getSize().y)
        return false;

    Color c = collisionMap.getPixel(imageCoordX, imageCoordZ);
    cout << "imageCoordX: " << imageCoordX << "\t\timageCoordZ: " << imageCoordZ << "\n";
    return !c.r;
}
