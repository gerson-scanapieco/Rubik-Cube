#pragma once
#include <string.h>
#ifndef __GLUT__
  #include <GL/glut.h>
#endif
#ifndef __MODEL__
 #include "model_manager.hpp"
#endif

class Renderer{

public:
 Renderer(){
  text_width = 8;      
  text_height = 13;
  draw_mode = 0; // 0:fill, 1: wireframe, 2:points
 }

 void init(Model_manager *model_manager);
 static void displayCB();
 static void reshapeCB(int w, int h);
 static void timerCB(int millisec);
 void initGL();
 int  initGLUT();
 bool initSharedMem();
 void clearSharedMem();
 void initLights();
 void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
 void drawString(const char *str, int x, int y, float color[4], void *font);
 void showInfo();
 static void toPerspective();
 void change_draw_mode();
 void set_camera_angle_x(int angle);
 void set_camera_angle_y(int angle);
 void set_camera_distance(float distance);
 
 static Model_manager *current_model_manager;
 static int screen_width,screen_height;   
 static float camera_distance,camera_angle_x,camera_angle_y;
 int   text_width;      
 int   text_height;
 int   draw_mode;

};