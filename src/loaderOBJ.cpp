#include "loaderOBJ.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int cyfry(int liczba)
{
  int b=1;
  while(liczba=liczba/10)b++;
  return b;
}

int znajdzLiczbe(string ciag, int i, char znak)
{
  string liczba;
  do {
    liczba+=ciag.at(i);
    i++;	      
  }while(ciag.at(i)!=znak);
  //cout<<liczba<<':';
  int c = atoi(liczba.c_str());
  return c;
}

void znajdzFloat(string ciag, int j, float *tablica)
{
  string liczba;
  int i=2;
  do {
    liczba+=ciag.at(i);
    i++;	      
  }while(ciag.at(i)!=' ');
  float c = atof(liczba.c_str());
  
  liczba="";
  do {
    liczba+=ciag.at(i);
    i++;	      
  }while(ciag.at(i)!=' ');
  float d = atof(liczba.c_str());
  
  //cout<<i<<ciag.length()<<endl;
  liczba=ciag.substr(i,ciag.length());
  float e = atof(liczba.c_str());
  tablica[j]=c;
  tablica[j+1]=d;
  tablica[j+2]=e;

  
 // cout<<tablica[j]<<tablica[j+1]<<tablica[j+2]<<endl;

}

void znajdzFaces(float *verticesObj, float *normalsObj, float *textureObj, float *vertices, float *normals, float *texture, string ciag, int l)
{
  //cout<<l<<endl;
  int i=2,c,d,e;//c=vertices,d=textcoords,e=normals
  for (int j=0; j<3;j++) 
  {
    c=znajdzLiczbe(ciag, i, '/');
    i=i+1+cyfry(c);  
    d=znajdzLiczbe(ciag, i, '/');
    i=i+1+cyfry(d);
    e=znajdzLiczbe(ciag, i, ' ');
    i=i+1+cyfry(e);
    //cout<<c<<" "<<d<<" "<<e<<" "<<endl;
    c--; d--; e--;
    c*=3; d*=3; e*=3;
    //cout<<verticesObj[c]<<verticesObj[c+1]<<verticesObj[c+2]<<endl;
    vertices[l]=verticesObj[c];
    vertices[l+1]=verticesObj[c+1];
    vertices[l+2]=verticesObj[c+2];
    vertices[l+3]=1.0;
    
    texture[l]=textureObj[d];
    texture[l+1]=textureObj[d+1];
    texture[l+2]=textureObj[d+2];
    texture[l+3]=1.0;
    
    normals[l]=normalsObj[e];
    normals[l+1]=normalsObj[e+1];
    normals[l+2]=normalsObj[e+2];
    normals[l+3]=0.0;
   // cout<<vertices[l]<<vertices[l+1]<<vertices[l+2]<<vertices[l+3]<<endl;
    l+=4;
  }

}

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
  ifstream plik,plik2;
  plik.open(source.c_str());
  
  if(plik.good()){
    
    while( true ) 
    {
        string a;
        getline(plik, a);

        if( plik.good() ) {
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
	if(a[0]=='v' && a[1]==' ') {znajdzFloat(a,i,verticesObj); i+=3;}
	if(a[0]=='v' && a[1]=='n' && a[2]==' ') {znajdzFloat(a,j,normalsObj); j+=3;}
	if(a[0]=='v' && a[1]=='t' && a[2]==' ') {znajdzFloat(a,k,textureObj); k+=3;}
	if(a[0]=='f' && a[1]==' ') { znajdzFaces(verticesObj, normalsObj, textureObj, vertices, normals, texture, a, l); l+=12;}
	
      }
      else
	break; 
    
    }
  
  }
  
  //for (int i=0;i<144;i++)  {cout<<vertices[i]<<',';}

}

