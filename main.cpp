#include <GL/glfw.h>
#include <cmath>
#include "Coverflow.h"
#include "Thread.cpp"

void paint(Coverflow& cf){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
    cf.paint();
    glfwSwapBuffers();
}

int main(){
    glfwInit();
    GLFWvidmode dvm;
    glfwGetDesktopMode(&dvm);
    glfwSetWindowTitle("FPS!");
    glfwOpenWindow(800, 400, dvm.RedBits, dvm.GreenBits, dvm.BlueBits,
                        8, 24, 0, GLFW_WINDOW);
    glEnable(GL_DEPTH_TEST);
    
        
    Coverflow cf;
    cf.initialise();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,2.0,0.01,100);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
        
    bool running = true;
    char keys[256] = {0};
    
    while (running){
        paint(cf);
        Thread<Coverflow,int>::sleep(10);
        
        running = glfwGetKey('Q')!=GLFW_PRESS;
        int leftKey = glfwGetKey('A')==GLFW_PRESS, rightKey = glfwGetKey('D')==GLFW_PRESS;
        if (leftKey ^ rightKey){
            cf.scroll(leftKey? -1: 1);
        }
    }
    
    glfwTerminate();
    return 0;
}