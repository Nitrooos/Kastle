#ifndef LOADEROBJ_H
#define LOADEROBJ_H

#include <string>

using namespace std;

struct OBJLoader {
    public:
        OBJLoader(string source);
        ~OBJLoader();

        void write() const;

        float *vertices, *texture, *normals;
        int vertexCount;
    private:
        void load();

        int verticesCount, normalsCount, coordsCount, facesCount;
        string source;
};

#endif
