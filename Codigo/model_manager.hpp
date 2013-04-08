#pragma once
#ifndef __CUBOMAGICO__
 #include "cubo_magico.hpp"
#endif

class Model_manager{

public:
 Model_manager(){};
 void init();
 void init(CuboMagico *drawable);
 void key_pressed(unsigned char key, int x, int y);
 void mouse_click(int button, int stat, int x, int y);
 void mouse_motion(int x, int y);

 static CuboMagico * current_drawable;

};