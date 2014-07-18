#ifndef LOADEROBJ_H
#define LOADEROBJ_H
#include <string>
using namespace std;

class Object {
  public:
    float *verticesObj; 
    float *textureObj;
    float *normalsObj;
    float *vertices; 
    float *texture;
    float *normals;
    string source;
    int vertexCount,
	verticesCount,
	normalsCount,
	coordsCount,
	facesCount;
    
    Object(string sourcee);
    void load();
};



#endif