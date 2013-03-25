#ifndef __GLUT__
  #include <GL/glut.h>
#endif
#ifndef __IOSTREAM__
  #include <iostream>
#endif
#include <string.h>


using namespace std;

class Cubo{

public:

  int grp_x, grp_y, grp_z;
  GLfloat vertices[72], colors[72], normals[72];
  GLubyte indices[36];

  Cubo();
  void init();

};


class CuboMagico{

public:

	float espacamento;
	static CuboMagico *currentInstance;
	Cubo cubos[27];

	static void drawCallback();
	void setupDrawCallback();
	void set_groups();
	void draw();
	CuboMagico();
 
};

