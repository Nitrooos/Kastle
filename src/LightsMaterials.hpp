#ifndef LIGHTSMATERIALS
#define LIGHTSMATERIALS

struct Light {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float position[4];
    float halfVector[4];
    float spotDirection[3];
    float spotExponent;
    float spotCutoff; // (range: [0.0,90.0], 180.0)
    float spotCosCutoff; // (range: [1.0,0.0],-1.0)
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

struct LightModel {
    float ambient[4];
};

struct Material {
    float emission[4];
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;
};

#endif /* end of include guard: CAMERA */
