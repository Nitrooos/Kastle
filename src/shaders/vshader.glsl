#version 130

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
in vec4 vertex;             //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal;             //wektor normalny w wierzcholku (na razie ignorowany) - przestrzen modelu
in vec2 texCoord;           // współrzędne teksturowania

out vec4 l;                 //promień światła padającego
out vec4 n;                 //wektor normalny w przestrzeni oka
out vec4 v;                 //kierunek do obserwatora

out vec2 iTexCoord;
out vec2 iTexCoord2;
 
uniform vec4 lightPosition;             //wspolrzedne homogeniczne swiatla w przestrzeni swiata


uniform vec4 Light0position;

uniform vec4 Light01position;

void main(void) {
    gl_Position=P*V*M*vertex;

    l=normalize(V*(Light01position-M*vertex)); //wektor do swiatla w przestrzeni oka
    //l+=normalize(V*(Light01position-M*vertex)); 
    n=normalize(V*M*normal); //wektor normalny w przestrzeni oka - uwaga! poprawnie powinno sie mnozyc razy G=transpose(invert(M))
    v=normalize(vec4(0,0,0,1)-V*M*vertex);

    iTexCoord = texCoord;
    iTexCoord2 = (n.xy + 1)/2;

}
/*
uniform vec4 Light0ambient;
uniform vec4 Light0diffuse;
uniform vec4 Light0position;

void main()
{
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient;
	float NdotL;

	normal = normalize(V * M);
	lightDir = normalize(vec3(Light0position));
	NdotL = max(dot(normal, lightDir), 0.0);
	diffuse = gl_FrontMaterial.diffuse * Light0diffuse;
	/* Compute the ambient and globalAmbient terms */

	/*ambient = gl_FrontMaterial.ambient * Light0ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;*/
/*
	gl_Position = ftransform();
}*/