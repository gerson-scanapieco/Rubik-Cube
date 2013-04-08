#ifndef __GLUT__
  #include <GL/glut.h>
#endif
#ifndef __MODEL__
  #include "model_manager.hpp"
#endif
#ifndef __RENDERER__
  #include "renderer.hpp"
#endif

class Input_manager{

public:
 Input_manager(){};

 void init(Model_manager *model_manager, Renderer *renderer);

 //TODO
 // Tirar esses metodos de Static para maior flexibilidade
 static void keyboardCB(unsigned char key, int x, int y);
 static void mouseCB(int button, int stat, int x, int y);
 static void mouseMotionCB(int x, int y);

 static Model_manager * current_model_manager;
 static Renderer * current_renderer;
 static int mouseX,mouseY,mouseLeftDown,mouseRightDown,mouseMiddleDown;

};