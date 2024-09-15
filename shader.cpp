//
// Created by Marko on 8/6/24.
//
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //-----------------------------FILE_READING----------------------
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream,fShaderStream;
        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode=vShaderStream.str();
        fragmentCode=fShaderStream.str();

    }
    catch(std::ifstream::failure e) {
        std::cout<<"ERROR::SHADER::FILE_NOT_READ"<<std::endl;
    }
    const char* vShaderCode=vertexCode.c_str();
    const char* fShaderCode=fragmentCode.c_str();

    //---------------------------------------------shader compilation-------------------------------------------------
    unsigned int vertex,fragment;
    int succes;
    char infoLog[512];
    //vertexShader
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&succes);
    if(!succes) {
        glGetShaderInfoLog(vertex,512,NULL,infoLog);
        std::cout<<"VERTEX::ERROR:"<<infoLog<<std::endl;
    }
    //fragmentShader
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&succes);
    if(!succes){
        glGetShaderInfoLog(fragment,512,NULL,infoLog);
        std::cout<<"FRAGMENT::ERROR:"<<infoLog<<std::endl;
    }
    //------------PROGRAM---------------
    Shader::ID=glCreateProgram();
    glAttachShader(Shader::ID,vertex);
    glAttachShader(Shader::ID,fragment);
    glLinkProgram(Shader::ID);
    //ERROR_CHECKUP
    glGetProgramiv(Shader::ID,GL_LINK_STATUS,&succes);
    if(!succes) {
        glGetProgramInfoLog(Shader::ID,512,NULL,infoLog);
        std::cout<<"PROGRAM::ERROR:"<<infoLog<<std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::use() {
    glUseProgram(ID);
}
void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(Shader::ID,name.c_str()),(int)value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(Shader::ID,name.c_str()),value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(Shader::ID,name.c_str()),value);
}




