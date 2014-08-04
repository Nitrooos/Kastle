#version 130

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
in vec4 vertex;             //wspolrzedne wierzcholka w przestrzeni modelu
//in vec4 color;              //kolor wierzcholka (na razie ignorowany)
in vec4 normal;             //wektor normalny w wierzcholku (na razie ignorowany) - przestrzen modelu

in vec2 texCoord;           // współrzędne teksturowania

out vec4 l;
out vec4 n;
out vec4 v;
out vec4 interpolatedColor;

out vec2 iTexCoord;
out vec2 iTexCoord2;

uniform vec4 lightPosition;             //wspolrzedne homogeniczne swiatla w przestrzeni swiata

void main(void) {
    gl_Position=P*V*M*vertex;

    l=normalize(V*(lightPosition-M*vertex)); //wektor do swiatla w przestrzeni oka
    n=normalize(V*M*normal); //wektor normalny w przestrzeni oka - uwaga! poprawnie powinno sie mnozyc razy G=transpose(invert(M))
    v=normalize(vec4(0,0,0,1)-V*M*vertex);

    iTexCoord = texCoord;
    iTexCoord2 = (n.xy + 1)/2;

    //interpolatedColor=color;
}
