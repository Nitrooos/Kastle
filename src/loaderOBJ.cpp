#include "loaderOBJ.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//funkcja zwraca ilość cyfr w liczbie
int cyfry(int liczba)
{
  int b=1;
  while(liczba=liczba/10)b++;
  return b;
}

//funkcja zwraca liczbę z "ciag", począwszy od i-tego znaku a kończy na "znak", gdzie "znak" nie jest liczbą, jest przerywnikiem, np "/" czy " "
int znajdzLiczbe(string ciag, int i, char znak)
{
  string liczba;

  do {
    liczba+=ciag.at(i);
    i++;	      
  } while(ciag.at(i)!=znak);

  //cout<<liczba<<':';
  int c = atoi(liczba.c_str());

  return c;
}

//funckja znajduje liczby w podanym ciągu począwszy od 3 znaku i przypisuje do tablicy począwszy od j-tego rekordu, zkładamy że w podanym ciągu są 3 liczby oddzielone spacją
void znajdzFloat(string ciag, int j, float *tablica)
{
  string liczba;
  int i=2;

  //znajdowanie pierwszej liczby
  do {
    liczba+=ciag.at(i);
    i++;	      
  }while(ciag.at(i)!=' ');
  float c = atof(liczba.c_str());
  
  //znajdowanie drugiej liczby
  liczba="";
  do {
    liczba+=ciag.at(i);
    i++;	      
  }while(ciag.at(i)!=' ');
  float d = atof(liczba.c_str());
  
  //znajdowanie trzeciej liczby
  liczba=ciag.substr(i,ciag.length());
  float e = atof(liczba.c_str());

  //przypisywanie do tablicy
  tablica[j]=c;
  tablica[j+1]=d;
  tablica[j+2]=e;
  
  //cout<<tablica[j]<<tablica[j+1]<<tablica[j+2]<<endl;
}

//funkcja przekształcająca wierzchołki z pliku .obj na wierzchołki OpenGL za pomocą podanego "ciag"u, l oznacza numer w tablicy. 
void znajdzFaces(float *verticesObj, float *normalsObj, float *textureObj, float *vertices, float *normals, float *texture, string ciag, int l)
{
  //cout<<l<<endl;
  int i=2,c,d,e;
  
  //pętla 3 kroków, ponieważ każdy wierzchołek ma 3 współrzędne w pliku .obj
  for (int j=0; j<3;j++) 
  {
    // 7/6/5 <- struktura pierwszej współrzędnej w pliku .obj, gdzie 7 oznacza numer wierzchołka, 6 numer współrzędnej teksturowania, a 5 wierzchołka normalnego, liczenie zaczynamy od 1 
    c=znajdzLiczbe(ciag, i, '/');
    i=i+1+cyfry(c);  
    d=znajdzLiczbe(ciag, i, '/');
    i=i+1+cyfry(d);
    e=znajdzLiczbe(ciag, i, ' ');
    i=i+1+cyfry(e);

    c--; d--; e--; //zmiejszamy o 1, ponieważ w pliku .obj liczymy od 1, nie od 0
    c*=3; d*=3; e*=3; //mnożymy, ponieważ wierzchołek ma 3 współrzędne

    //cout<<verticesObj[c]<<verticesObj[c+1]<<verticesObj[c+2]<<endl;
    
    //przypisujemy dane do tablic wyjściowych
    vertices[l]=verticesObj[c];
    vertices[l+1]=verticesObj[c+1];
    vertices[l+2]=verticesObj[c+2];
    vertices[l+3]=1.0;	//ostatnia współrzędna wierzchołka musi być równa 1
    
    texture[l]=textureObj[d];
    texture[l+1]=textureObj[d+1];
    texture[l+2]=textureObj[d+2];
    texture[l+3]=1.0; //ostatnia współrzędna teksturowania musi być równa 1
    
    normals[l]=normalsObj[e];
    normals[l+1]=normalsObj[e+1];
    normals[l+2]=normalsObj[e+2];
    normals[l+3]=0.0; //ostatnia współrzędna wierzchołka normalnego musi być równa 0

    //cout<<vertices[l]<<vertices[l+1]<<vertices[l+2]<<vertices[l+3]<<endl;
    l+=4;  
  }

}

//kostruktor zeruje wszystkie int i wypisuje wczytany obiekt
Object::Object(string sourcee):source(sourcee)
{
  verticesCount=0;
  normalsCount=0;
  coordsCount=0;
  facesCount=0;

  cout<<"Create Object from: "<<source<<endl;
    
}


void Object::load()
{
  //otwarcie pliku
  ifstream plik,plik2;
  plik.open(source.c_str());
  
  if(plik.good()){
    
    while( true ) 
    {
        string a;
        getline(plik, a);

        if( plik.good() ) {
	  //odczytywanie z pliku danych potrzebnych do utworzenia tablic
	  size_t found = a.find("vertices");
	  if (found!=string::npos)
	  {
	    verticesCount=znajdzLiczbe(a,2,' ');
	    cout << "Vertices: " << verticesCount << '\n';
	  }
	  found = a.find("normals");
	  if (found!=string::npos)
	  {
	    normalsCount=znajdzLiczbe(a,2,' ');
	    cout << "Vertex normals: " << normalsCount << '\n';
	  }
	  found = a.find("coords");
	  if (found!=string::npos)
	  {
	    coordsCount=znajdzLiczbe(a,2,' ');
	    cout << "Texture coords: " << coordsCount << '\n';
	  }
	  found = a.find("faces");
	  if (found!=string::npos)
	  {
	    facesCount=znajdzLiczbe(a,2,' ');
	    cout << "Faces: " << facesCount << '\n';
	    vertexCount=facesCount*3;
	    cout << "Vertex count: " << vertexCount << '\n';
	  }
	  
	  
	}
        else
             break; 
       
    } 
    
  } else cout<<"Blad pliku: "<<source<<endl;
  
  if (verticesCount!=0 && normalsCount!=0 && coordsCount!=0 && facesCount!=0)
  {
    //inicjowanie tablic
    verticesObj = new float[verticesCount*3];
    normalsObj = new float[normalsCount*3];
    textureObj = new float[coordsCount*3];
    vertices = new float[facesCount*4*3];
    normals = new float[facesCount*4*3];
    texture = new float[facesCount*4*3];
    int i=0,j=0,k=0, l=0;
    
    plik2.open(source.c_str());
    
    while( true ) 
    {
      if( plik2.good() ) {
	string a;
	getline(plik2, a);
	//wczytywanie danych z pliku .obj do tablic
	if(a[0]=='v' && a[1]==' ') {znajdzFloat(a,i,verticesObj); i+=3;}
	if(a[0]=='v' && a[1]=='n' && a[2]==' ') {znajdzFloat(a,j,normalsObj); j+=3;}
	if(a[0]=='v' && a[1]=='t' && a[2]==' ') {znajdzFloat(a,k,textureObj); k+=3;}
	//przekształcanie danych z .obj na OpenGL	
	if(a[0]=='f' && a[1]==' ') { znajdzFaces(verticesObj, normalsObj, textureObj, vertices, normals, texture, a, l); l+=12;}
	
      }
      else
	break; 
    
    }
  
  }
  

}

