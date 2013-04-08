#pragma once
#ifndef __GLUT__
  #include <GL/glut.h>
#endif
#ifndef __IOSTREAM__
  #include <iostream>
#endif
#ifndef __MATH3D__
  #include "shared/math3d.h"
#endif
#ifndef __IDRAWABLE__
  #include "IDrawable.hpp"
#endif

class Cubo {

 public:
   Cubo(){
    for(int i=0; i<16;i++){
      if(i % 5 == 0)
        this->matriz_de_transformacao[i] = 1;
      else
        this->matriz_de_transformacao[i] = 0;
    }
   }
   void init();

   M3DMatrix44f matriz_de_transformacao;
   GLfloat vertices[72], colors[72], normals[72];
   GLubyte indices[36];
};


class CuboMagico{

public:
  void reaction_to_input(unsigned char key, int x, int y);
  void reaction_to_input(int button, int stat, int x, int y);
  void reaction_to_input(int x, int y);
  void drawCallback();
  void setupDrawCallback();
  void set_initial_translation();
  void draw();
  void raise_gap();
  void lower_gap();
  void reaction_to_keyboard(unsigned char key, int x, int y);
  void reaction_to_mouse_motion(int button, int stat, int x, int y);
  void reaction_to_click(int x, int y);

  CuboMagico(){
    for(int i=0; i<27;i++){
      this->cubos[i].init();
    }
  }

  float gap;
  Cubo cubos[27];

};



