#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "GraphicModel.h"
#include "VisionModule.h"

using namespace cv;
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* graphicsWindow;
GLFWwindow* visionWindow;
VisionModule visionModule;
std::list<GameObject*> gameObjects;

void init();
void update();
void draw();

int main(void)
{
    visionModule.Start();

    if (!glfwInit())
        throw "Could not initialize glwf";
    graphicsWindow = glfwCreateWindow(1400, 800, "Graphics window", NULL, NULL);
    
    glfwMakeContextCurrent(graphicsWindow);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(graphicsWindow))
	{
		update();
		draw();
		glfwSwapBuffers(graphicsWindow);
		glfwPollEvents();
	}

    visionModule.Stop();
	glfwTerminate();

    return 0;
}


void init()
{
    glfwSetKeyCallback(graphicsWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
        if (key == GLFW_KEY_SPACE) {
            //Doe iets met X en Y.
            //Als je wil kan je ook Point lastPoint halen uit de visionmodule. Dan heb je de callback niet nodig.
            Point2d selection = visionModule.GetSelectionPos();
            cout << "Selection at: (" << selection.x << "," << selection.y << ")" << endl;
        }
    });
    glEnable(GL_DEPTH_TEST);
}


void update()
{

}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(110.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 50, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableTexture(true);

    for (auto& o : gameObjects)
        o->draw();
}