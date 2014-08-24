#version 130

/*
void main()
{
    gl_FragColor = gl_Color;
}
*/
    

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 l;
in vec4 n;
in vec4 v;

uniform sampler2D textureMap0, textureMap1;
in vec2 iTexCoord;
in vec2 iTexCoord2;
uniform vec4 dragi1; 
uniform vec4 dragi2;
uniform vec4 dragi3;
uniform float polysk;

uniform vec4 Light0ambient;
uniform vec4 Light0diffuse;
uniform vec4 Light0specular;
uniform vec4 Light0position;

uniform vec4 Light01ambient;
uniform vec4 Light01diffuse;
uniform vec4 Light01specular;
uniform vec4 Light01position;

uniform vec4 Material0emission;
uniform vec4 Material0ambient;
uniform vec4 Material0diffuse;
uniform vec4 Material0specular;
uniform float Material0shininess;

void main(void) {

    //Parametry modelu oswietlenia - normalnie powinny byc przekazane jako zmienne jednorodne, ale dla uproszczenia sa zakodowane na twardo
    //vec4 La=vec4(0,0,0,0);                  //Kolor swiatla otoczenia (ambient)
    //vec4 Ma=vec4(0,0,0,0);                  //Kolor materialu dla swiatla otoczenia

    vec4 Ld=vec4(1,1,1,1);                  //Kolor swiatla rozpraszanego

    //Kolor materialu dla swiatla rozpraszanego
    vec4 Md=(3*texture(textureMap0, iTexCoord) + texture(textureMap1, iTexCoord2))/4;
    //vec4 Md=texture(textureMap0, iTexCoord2);

    vec4 Ls=vec4(1,1,1,1);                  //Kolor swiatla odbijanego
    vec4 Ms=vec4(1,1,1,1);                  //Kolor materialu dla swiatla odbijanego
    //float shininess=polysk;                         //Polyskliwosc materialu

    //Wektory potrzebne do obliczenia modelu oswietlenia
    vec4 ml=normalize(l);
    vec4 mn=normalize(n);
    vec4 mv=normalize(v);
    vec4 mr=reflect(-ml,mn);

    //Obliczenie modelu oswietlenia
    float nl=max(dot(ml,mn),0);
    float rv=pow(max(dot(mr,mv),0),Material0shininess);

    pixelColor=Light0ambient*Material0ambient+Ld*Md*vec4(nl,nl,nl,1)+Ls*Ms*vec4(rv,rv,rv,0);
    //pixelColor+=Light01ambient*Material0ambient+Light01diffuse*Md*vec4(nl,nl,nl,1)+Light01specular*Material0specular*vec4(rv,rv,rv,0);
}
