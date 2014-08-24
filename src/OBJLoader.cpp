#include "OBJLoader.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>

// ile cyfr ma liczba?
int cyfry(int liczba) {
    int b = 1;
    while ( liczba=liczba/10 )
        b++;
    return b;
}


int znajdzLiczbe(string ciag, int i, char znak) {
    string liczba;
    do {
        liczba += ciag.at(i);
        i++;
    } while(ciag.at(i)!=znak);

    int c = strtol(liczba.c_str(), nullptr, 10);
    return c;
}

void znajdzFloat(string ciag, int j, float *tablica) {
    string liczba;
    int i = 2;
    do {
        liczba += ciag.at(i);
        i++;
    } while (ciag.at(i) != ' ');
    float c = strtof(liczba.c_str(), nullptr);

    liczba = "";
    do {
        liczba += ciag.at(i);
        i++;
    } while (ciag.at(i) != ' ');
    float d = strtof(liczba.c_str(), nullptr);

    liczba = ciag.substr(i,ciag.length());
    float e = strtof(liczba.c_str(), nullptr);
    tablica[j]=c;
    tablica[j+1]=d;
    tablica[j+2]=e;
}

void znajdzFaces(float *verticesObj, float *normalsObj, float *textureObj, float *vertices, float *normals, float *texture, string ciag, int l, int t) {
    int i = 2, c, d, e;                 //c=vertices,d=textcoords,e=normals
    for (int j = 0; j < 3; j++) {
        c = znajdzLiczbe(ciag, i, '/');
        i = i+1+cyfry(c);
        d = znajdzLiczbe(ciag, i, '/');
        i = i+1+cyfry(d);
        e = znajdzLiczbe(ciag, i, ' ');
        i = i+1+cyfry(e);

        c--;
        d--;
        e--;
        c*=3;
        d*=3;
        e*=3;

        vertices[l]=verticesObj[c];
        vertices[l+1]=verticesObj[c+1];
        vertices[l+2]=verticesObj[c+2];
        vertices[l+3]=1.0;

        texture[t]=textureObj[d];
        texture[t+1]=textureObj[d+1];
        //texture[t+2]=textureObj[d+2];

        normals[l]=normalsObj[e];
        normals[l+1]=normalsObj[e+1];
        normals[l+2]=normalsObj[e+2];
        normals[l+3]=0.0;

        l+=4;
        t+=2;
    }
}

OBJLoader::OBJLoader(string source)
    : source(source) {
    verticesCount = 0;
    normalsCount = 0;
    coordsCount = 0;
    facesCount = 0;

    //cout << "Create OBJLoader from: " << source << "\n";
    load();
    //cout << "Done\n";
}

OBJLoader::~OBJLoader() {
    delete vertices;
    delete normals;
    delete texture;
}

void OBJLoader::load() {
    ifstream plik;
    plik.open(source.c_str());

    if(plik.good()) {
        while( true ) {
            string a;
            getline(plik, a);

            if( plik.good() ) {
                size_t found = a.find("vertices");
                if (found!=string::npos) {
                    verticesCount = znajdzLiczbe(a,2,' ');
                    //cout << "Vertices: " << verticesCount << '\n';
                }
                found = a.find("normals");
                if (found!=string::npos) {
                    normalsCount = znajdzLiczbe(a,2,' ');
                    //cout << "Vertex normals: " << normalsCount << '\n';
                }
                found = a.find("coords");
                if (found!=string::npos) {
                    coordsCount = znajdzLiczbe(a,2,' ');
                    //cout << "Texture coords: " << coordsCount << '\n';
                }
                found = a.find("faces");
                if (found!=string::npos) {
                    facesCount=znajdzLiczbe(a,2,' ');
                    //cout << "Faces: " << facesCount << '\n';
                    vertexCount = facesCount*3;
                    //cout << "Vertex count: " << vertexCount << '\n';
                }
            } else break;
        }
    } else {
        // Exception
    }

    plik.clear();
    plik.seekg(0, plik.beg);

    if (verticesCount!=0 && normalsCount!=0 && coordsCount!=0 && facesCount!=0) {
        float *verticesObj = new float[verticesCount*3];
        float *normalsObj = new float[normalsCount*3];
        float *textureObj = new float[coordsCount*3];

        vertices = new float[facesCount*4*3];
        normals = new float[facesCount*4*3];
        texture = new float[facesCount*3*3];

        int i = 0, j = 0, k = 0, l = 0, t = 0;

        while ( true ) {
            if ( plik.good() ) {
                string a;
                getline(plik, a);
                if (a[0]=='v' && a[1]==' ') {
                    znajdzFloat(a,i,verticesObj);
                    i += 3;
                }
                if (a[0]=='v' && a[1]=='n' && a[2]==' ') {
                    znajdzFloat(a,j,normalsObj);
                    j += 3;
                }
                if (a[0]=='v' && a[1]=='t' && a[2]==' ') {
                    znajdzFloat(a,k,textureObj);
                    k += 3;
                }
                if (a[0]=='f' && a[1]==' ') {
                    znajdzFaces(verticesObj, normalsObj, textureObj, vertices, normals, texture, a, l, t);
                    l += 12;
                    t += 6;
                }
            } else break;
        }

        delete verticesObj;
        delete normalsObj;
        delete textureObj;

    }
    plik.close();
}

void OBJLoader::write() const {
    cout << "\nLoaded vertices:\n";
    for (int i = 0; i < vertexCount; i += 4) {
        cout << "\t" << vertices[i] << "\t" << vertices[i+1] << "\t" << vertices[i+2] << "\t" << vertices[i+3] << "\n";
    }

    cout << "\nLoaded normals:\n";
    for (int i = 0 ; i < verticesCount; i += 4) {
        cout << "\t" << normals[i] << "\t" << normals[i+1] << "\t" << normals[i+2] << "\t" << normals[i+3] << "\n";
    }

    cout << "\nLoaded vertex count: " << verticesCount << "\n";
}
