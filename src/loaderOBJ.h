#ifndef LOADEROBJ_H
#define LOADEROBJ_H
#include <string>
using namespace std;

class Object {
  public:
    float *verticesObj, //tablice danych bezpośrednio wczytanych z pliku
    	  *textureObj,
    	  *normalsObj,
    	  *vertices, 	//tablica wierzchołków
    	  *texture,	//tablica współrzędnych tekturowania
    	  *normals;	//tablica wierzchołków normalnych

    string source;	//ścieżka do pliku .obj

    int vertexCount,	//liczba wierzchołków w OpenGL
	verticesCount,	//liczby wierzchołków w pliku .obj
	normalsCount,
	coordsCount,
	facesCount;	//liczba ścian
    
    Object(string sourcee);
    void load();	//załadowanie tablic z pliku do obiektu
};



#endif
