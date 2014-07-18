#version 130

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienna interpolowana
in vec4 interpolatedColor;

void main(void) {
    pixelColor = interpolatedColor;
}
