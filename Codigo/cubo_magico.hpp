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
#ifndef __MATH3D__
  #include "shared/math3d.h"
#endif

class Cubo {

 public:
   Cubo(){
    this->is_rotating = 0;
    for(int i=0; i<16;i++){
      if(i % 5 == 0)
        this->matriz_de_transformacao[i] = 1;
      else
        this->matriz_de_transformacao[i] = 0;
    }
   }
   void init();

   int is_rotating;
   M3DMatrix44f matriz_de_transformacao;
   GLfloat vertices[72], colors[72], normals[72];
   GLubyte indices[36];
};


class CuboMagico{

public:
  void drawCallback();
  void setupDrawCallback();
  void set_initial_translation();
  void draw();
  void raise_gap();
  void lower_gap();
  void reaction_to_keyboard(unsigned char key, int x, int y);
  void reaction_to_mouse_motion(int button, int stat, int x, int y);
  void reaction_to_click(int x, int y);
  void rotate_face(int face, int orientation);
  void draw_rotation(int face, int orientation);
  void animation();

  CuboMagico(){
    gap = 1.2f;
    angle = 0;
    for(int i=0; i<3;i++){
      for(int j=0; j<3;j++){
        for(int k=0;k<3;k++){
          this->cubos[i][j][k] = new Cubo;
          this->cubos[i][j][k]->init();
        }
      }
    }
    this->set_initial_translation();
  }
  float gap;
  Cubo *cubos[3][3][3];
  float angle;
};

