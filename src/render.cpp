#include "renderer.h"
#include "core/shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ostream>
#include <cmath>
using namespace std;



// settings
const uint16_t SCR_WIDTH = 800;
const uint16_t SCR_HEIGHT = 600;

// set up vertex data (and buffer(s)) and configure vertex attributes
float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
};

float screen1[] = {
    // positions
     1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f
};
float screen2[] = {
    // positions
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
};



void awake(Renderer* r) {}
// render loop
void update(Renderer* r) {
    // get uniform values
    float time = glfwGetTime();
    // get uniform locations
    int timeLocation = glGetUniformLocation(r->shader->program, "time");
    int resLocation = glGetUniformLocation(r->shader->program, "resolution");
    // set uniform values
    glUniform1f(timeLocation, time);
    glUniform2f(resLocation, SCR_WIDTH, SCR_HEIGHT);

    if (r->getInput(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
        r->close();
    }
}

// window dimensions altered
void sizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(int argc, char *argv[])
{
    // initialize renderer
    Renderer r = Renderer("Renderer", SCR_WIDTH, SCR_HEIGHT);
    // error occurred
    if (r.status) {
        return -1;
    }
    // create shader program
    Shader s = Shader("core/shaders/vertex.vs", "core/shaders/fragment.fs");
    r.shader = &s;
    r.setVertices(screen1, sizeof(screen1), 0);
    r.setVertices(screen2, sizeof(screen2), 1);
    s.use();

    // set renderer attributes
    r.sizeCallback(sizeCallback);
    r.awake = &awake;
    r.update = &update;

    // run mainloop
    r.run();

    return 0;
}
