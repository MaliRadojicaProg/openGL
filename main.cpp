#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void processInput(GLFWwindow* window);
void resize(GLFWwindow* window,int width,int height);
void opacityChange(GLFWwindow* window,float& mix);
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    //make a window object
    GLFWwindow* window=glfwCreateWindow(800,600,"windowww",nullptr,nullptr);


    if(window==NULL) {
        std::cout<<"NE RADI PROZOR\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"no glad rip";
        return -1;
    }
    // glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,resize);

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
   };
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    // glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    // glm::mat4 trans=glm::mat4(1.0f);
    // trans=glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
    // vec=trans*vec;
    // std::cout<<vec.x<<vec.y<<vec.z<<std::endl;
    //
    //
 //   glm::mat4 trans=glm::mat4(1.0f);
    //trans=glm::scale(trans, glm::vec3(0.5f,0.5f,0.5f));

  //  trans=glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0f,0.0f,1.0f));




    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };
    Shader myShader("/home/Marko/CLionProjects/triangleOpenGL4/vertex.vert","/home/Marko/CLionProjects/triangleOpenGL4/fragment.frag");

    GLuint VBO,VAO,EBO;
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    //------IMAGE LOADING-----
    GLuint texture1,texture2;

    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    int height,width,nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data=stbi_load("/home/Marko/CLionProjects/triangleOpenGL4/container.jpg",&width,&height,&nrChannels,0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout<<"IMAGE FAILED TO LOAD\n";
    }
    stbi_image_free(data);
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    int height2,width2,nrChannels2;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data2=stbi_load("/home/Marko/CLionProjects/triangleOpenGL4/awesomeface.png",&width2,&height2,&nrChannels2,0);
    if(data2) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width2,height2,0,GL_RGBA,GL_UNSIGNED_BYTE,data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout<<"SMILLING FUCK NOT LOADED\n";
    }
    stbi_image_free(data2);
    //--------------TEXTURES--------------
    myShader.use();
    // glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0);
    // glUniform1i(glGetUniformLocation(myShader.ID, "texture2"), 1);
    myShader.setInt("texture1",0);
    myShader.setInt("texture2",1);
    float mixValue=0.2f;
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.7f,0.4f,0.2f,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);
     //   glBindTexture(GL_TEXTURE_2D,texture);
        opacityChange(window,mixValue);
        myShader.setFloat("opacity",mixValue);

        glm::mat4 transform=glm::mat4(1.0);
        transform=glm::translate(transform,glm::vec3(0.5f,-0.5f,0.0f));
        transform=glm::rotate(transform,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
        myShader.use();
        unsigned int transformLoc=glGetUniformLocation(myShader.ID,"transform"); //Gets the location of the uniform from the shader
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform)); //sets the uniform
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glm::mat4 trans2=glm::mat4(1.0);
        trans2=glm::translate(trans2,glm::vec3(-0.5,0.5,0.0));
        float scaleAmount=static_cast<float>(sin(glfwGetTime()));
        trans2=glm::scale(trans2,glm::vec3(scaleAmount,scaleAmount,scaleAmount));
        myShader.use();
        unsigned int trans2loc=glGetUniformLocation(myShader.ID,"transform");
        glUniformMatrix4fv(trans2loc,1,GL_FALSE,glm::value_ptr(trans2));
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


//transformation matrix

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();



    return 0;
}
void opacityChange(GLFWwindow* window,float& mix) {
if(glfwGetKey(window,GLFW_KEY_UP)) {
        mix=mix+0.1f;
    }
    else if(glfwGetKey(window,GLFW_KEY_DOWN)) {
        mix=mix-0.1f;
    }

}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
    if(glfwGetKey(window,GLFW_KEY_Y)) {
         glfwSetWindowShouldClose(window,true);
     }

}
void resize(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width,height);
}



