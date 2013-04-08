#pragma once
#include <new>
#ifndef __GLUT__
  #include <GL/glut.h>
#endif
#ifndef __VECTOR__
  #include <vector>
#endif
#ifndef __RENDERER__
  #include "renderer.hpp"
#endif
#ifndef __INPUT__
 #include "input_manager.hpp"
#endif
#ifndef __MODEL__
 #include "model_manager.hpp"
#endif
#ifndef __IDRAWABLE__
 #include "IDrawable.hpp"
#endif

class Engine{

public:

 Engine(){
  Input_manager *my_input_manager = new Input_manager;
  Model_manager *my_model_manager = new Model_manager;
  Renderer *my_renderer = new Renderer;

  input_managers.push_back(my_input_manager);
  renders.push_back(my_renderer);
  model_managers.push_back(my_model_manager);
 }
  void init(int, char**);
  void run();

  static Renderer *current_renderer;
  static Model_manager *current_model_manager;
  static Input_manager *current_input_manager;

  std::vector<Input_manager*> input_managers;
  std::vector<Renderer*> renders;
  std::vector<Model_manager*> model_managers;
};