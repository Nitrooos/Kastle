#version 130

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;  //kolor wierzcholka (na razie ignorowany)
in vec4 normal; //wektor normalny w wierzcholku (na razie ignorowany)

//Zmienna interpolowana
out vec4 interpolatedColor;

void main(void) {
    vec4 observer = vec4(0, 0, 0, 1);
    float d = distance(observer, V*M*vertex);
    d = 1 - (d - 5.3)/1.7;
    interpolatedColor = color*vec4(d, d, d, 1);
    //interpolatedColor = color;

    gl_Position=P*V*M*vertex;
}
