#include "ShaderProgram.hpp"

//Procedura wczytuje plik do tablicy znak�w.
char* ShaderProgram::readFile(char* fileName) {
    int filesize;
    FILE *plik;
    char* result;

    plik=fopen(fileName,"r");
    fseek(plik,0,SEEK_END);
    filesize=ftell(plik);
    fseek(plik,0,SEEK_SET);
    result=new char[filesize+1];
    fread(result,1,filesize,plik);
    result[filesize]=0;
    fclose(plik);

    return result;
}

//Metoda wczytuje i kompiluje shader, a nast�pnie zwraca jego uchwyt
GLuint ShaderProgram::loadShader(GLenum shaderType,char* fileName) {
    //Wygeneruj uchwyt na shader
    GLuint shader=glCreateShader(shaderType);//shaderType to GL_VERTEX_SHADER, GL_GEOMETRY_SHADER lub GL_FRAGMENT_SHADER
    //Wczytaj plik ze �r�d�em shadera do tablicy znak�w
    const GLchar* shaderSource=readFile(fileName);
    //Powi�� �r�d�o z uchwytem shadera
    glShaderSource(shader,1,&shaderSource,NULL);
    //Skompiluj �r�d�o
    glCompileShader(shader);
    //Usu� �r�d�o shadera z pami�ci (nie b�dzie ju� potrzebne)
    delete [] shaderSource;

    //Pobierz log b��d�w kompilacji i wy�wietl
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 1) {
        infoLog = new char[infologLength];
        glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        delete []infoLog;
    }

    //Zwr�� uchwyt wygenerowanego shadera
    return shader;
}

ShaderProgram::ShaderProgram(char* vertexShaderFile,char* geometryShaderFile,char* fragmentShaderFile) {
    //Wczytaj vertex shader
    printf("Loading vertex shader...\n");
    vertexShader=loadShader(GL_VERTEX_SHADER,vertexShaderFile);

    //Wczytaj geometry shader
    if (geometryShaderFile!=NULL) {
        printf("Loading geometry shader...\n");
        geometryShader=loadShader(GL_GEOMETRY_SHADER,geometryShaderFile);
    } else {
        geometryShader=0;
    }

    //Wczytaj fragment shader
    printf("Loading fragment shader...\n");
    fragmentShader=loadShader(GL_FRAGMENT_SHADER,fragmentShaderFile);

    //Wygeneruj uchwyt programu cieniuj�cego
    shaderProgram=glCreateProgram();

    //Pod��cz do niego shadery i zlinkuj program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    if (geometryShaderFile!=NULL) glAttachShader(shaderProgram,geometryShader);
    glLinkProgram(shaderProgram);

    //Pobierz log b��d�w linkowania i wy�wietl
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 1)
    {
        infoLog = new char[infologLength];
        glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        delete []infoLog;
    }

    printf("Shader program created \n");
}

ShaderProgram::~ShaderProgram() {
    //Od��cz shadery od programu
    glDetachShader(shaderProgram, vertexShader);
    if (geometryShader!=0) glDetachShader(shaderProgram, geometryShader);
    glDetachShader(shaderProgram, fragmentShader);

    //Wykasuj shadery
    glDeleteShader(vertexShader);
    if (geometryShader!=0) glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);

    //Wykasuj program
    glDeleteProgram(shaderProgram);
}


//W��cz u�ywanie programu cieniuj�cego reprezentowanego przez aktualny obiekt
void ShaderProgram::use() const {
    glUseProgram(shaderProgram);
}

//Pobierz numer slotu odpowiadaj�cego zmiennej jednorodnej o nazwie variableName
GLuint ShaderProgram::getUniformLocation(char* variableName) const {
    return glGetUniformLocation(shaderProgram,variableName);
}

//Pobierz numer slotu odpowiadaj�cego atrybutowi o nazwie variableName
GLuint ShaderProgram::getAttribLocation(char* variableName) const {
    return glGetAttribLocation(shaderProgram,variableName);
}
