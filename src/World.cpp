#include "World.hpp"
#include "App.hpp"

#include <iostream>

World::World(GraphicsManager *gm) : grMananger(gm) {
    collisionMap.loadFromFile("data/maps/collision2.png");
    firstFloorCollisionMap.loadFromFile("data/maps/collisionFirstFloor.png");

    objects.push_back(Entity{grMananger->getBuffer(ObjectType::Red),
                             grMananger->getShader(ShaderType::Standard2),
                             0, 0, 5,
                             grMananger->getTexture(TextureType::Red)}
                     );
    objects.push_back(Entity{grMananger->getBuffer(ObjectType::PokojeKolumny),
                             grMananger->getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger->getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger->getBuffer(ObjectType::salaTronowa),
                             grMananger->getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger->getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger->getBuffer(ObjectType::ScianySufitPodloga),
                             grMananger->getShader(ShaderType::Standard),
                             0, 0, 5,
                             grMananger->getTexture(TextureType::Purple)}
                     );
    objects.push_back(Entity{grMananger->getBuffer(ObjectType::Okna),
                             grMananger->getShader(ShaderType::Standard2),
                             0, 0, 5,
                             grMananger->getTexture(TextureType::Red)}
                     );
    objects.push_back(Entity{grMananger->getBuffer(ObjectType::Doors),
                             grMananger->getShader(ShaderType::Standard2),
                             -4.95, 0.6, 70.5,
                             grMananger->getTexture(TextureType::Red)}
                     );
    objects.push_back(Entity{grMananger->getBuffer(ObjectType::Doors),
                             grMananger->getShader(ShaderType::Standard2),
                             -7.9, 0.6, 70.5,
                             grMananger->getTexture(TextureType::Red)}
                     );


    lights[0] = {   { 0.0,  0.0,  0.0,  0.0 },       //ambient  - kolor swiatla otoczenia
                    { 0.01, 0.01, 0.01, 1.0 },       //diffuse  - kolor swiatla rozpraszanego
                    { 1.0,  1.0,  1.0,  1.0 },       //specular - kolor swiatla odbijanego
                    { 0.0,  10.0, 40.0, 1.0 }        //position
                };

    lights[1] = {   { 0.0, 0.0,  0.0,  0.0 },       //ambient  - kolor swiatla otoczenia
                    { 0.5, 0.5,  0.5,  0.5 },       //diffuse  - kolor swiatla rozpraszanego
                    { 0.5, 0.5,  0.5,  0.5 },       //specular - kolor swiatla odbijanego
                    { 0.0, 20.0, 40.0, 1.0 }        //position
                };

    materials[0] = {    { 0.0,  0.0,  0.0,  0.0  }, //emission  -
                        { 0.0,  0.0,  0.0,  0.0  }, //ambient   - kolor swiatla otoczenia
                        { 1.0,  1.0,  1.0,  1.0  }, //diffuse   - kolor swiatla rozpraszanego
                        { 0.01, 0.01, 0.01, 0.01 }, //specular  - kolor swiatla odbijanego
                        200.0                       //shininess   - polysk
                };
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
                case Keyboard::T: checkAction(); break;
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

    // Odegraj wszystkie animacje obiektów
    for (auto &a : animations) {
        a.animate();
    }
    animations.remove_if([]() { return (getStatus() == Animation::Status::Stop); });

    float xShift = -camera.getZShift(this->go) + camera.getXShift(this->side),
          yShift = this->height,
          zShift =  camera.getXShift(this->go) + camera.getZShift(this->side);

    if ((xShift || yShift || zShift) && !isCollision(xShift, zShift))
        camera.movEye(xShift, yShift, zShift);

    if (this->go) {
        camera.setYPos(camera.getBaselineY() + 0.3*sin(headParam += 0.1f));
    }

    camera.writeCoordinates();
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    for (auto &x : objects)
        x.onRender(camera, lights[0], lights[1], materials[0]);
}

void World::onInit() {
    glEnable(GL_DEPTH_TEST);
}

bool World::isCollision(float xShift, float zShift) const {
    // zamek ma wymiary 177x120 jednostek
    constexpr float w = 3.28f,
                    p1 = 65.0f,
                    p2 = 49.0f;
    float imageCoordX = (camera.getX() + xShift + p1)*w,
          imageCoordZ = (camera.getZ() + zShift + p2)*w;
    const Image &correctMap = cameraOnFirstFloor ? firstFloorCollisionMap : collisionMap;

    if (imageCoordX < 0 || imageCoordX > correctMap.getSize().x ||
        imageCoordZ < 0 || imageCoordZ > correctMap.getSize().y)
        return false;

    Color c = correctMap.getPixel(imageCoordX, imageCoordZ);
    return !c.r;
}

void World::checkAction() {
    float distFromTeleoport1 = sqrt(pow(camera.getX() + 36, 2) + pow(camera.getZ() - 120, 2)),
          distFromTeleoport2 = sqrt(pow(camera.getX() - 30, 2) + pow(camera.getZ() - 120, 2)),
          distFromDoors = sqrt(pow(camera.getX(), 2) + pow(camera.getZ() - 70, 2));

    if (distFromTeleoport1 < 5.0f || distFromTeleoport2 < 5.0f)
        teleport();
    if (distFromDoors < 5.0f)
        openDoors();
}

void World::teleport() {
    if (camera.getY() < 10.0) {
        camera.setYPos(10.0);
        camera.setBaselineY(10.0);
        cameraOnFirstFloor = true;
    } else {
        camera.setYPos(3.0);
        camera.setBaselineY(3.0);
        cameraOnFirstFloor = false;
    }
}

void World::openDoors() {
    float dir = 1.0f;
    for (auto &o : objects) {
        if (abs(o.getX() + 6.5) < 5.0f && o.getZ() == 70.5f ) {
            Animation anim(o);
            anim.setParams(dir, 90.0f);
            animations.push_back(anim);
            dir *= -1;
        }
    }
}
