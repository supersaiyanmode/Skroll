#include <GL/glfw.h>
#include <cmath>
#include "Coverflow.h"
#include "Thread.cpp"
#include "FileLister.h"

void paint(TileDisplay& td){
    static int init;
    static std::vector<double> cameraParams;
    if (!init++){
        td.setCamera(&cameraParams);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraParams[0],cameraParams[1],cameraParams[2],
              cameraParams[3],cameraParams[4],cameraParams[5],
              cameraParams[6],cameraParams[7],cameraParams[8]);
    td.paint();
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
    
        
    Cooliris cf;
    cf.initialise();
    //std::cout<<cf.maxHorizPos<<std::endl;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,2.0,0.01,100);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
        
    bool running = true;
    
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