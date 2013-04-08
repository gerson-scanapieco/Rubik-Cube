#include "engine.hpp"

Renderer * Engine::current_renderer = NULL;
Model_manager * Engine::current_model_manager = NULL;
Input_manager * Engine::current_input_manager = NULL;

void Engine::init(int argc, char **argv){
  current_renderer = renders[0];
  current_model_manager = model_managers[0];
  current_input_manager = input_managers[0];
  glutInit(&argc, argv);
}

void Engine::run(){

  this->current_renderer->init(current_model_manager);
  this->current_input_manager->init(current_model_manager, current_renderer);
  this->current_model_manager->init();

  glutDisplayFunc(Renderer::displayCB);
  glutTimerFunc(33, Renderer::timerCB, 33);             // redraw only every given millisec
  glutReshapeFunc(Renderer::reshapeCB);
  glutKeyboardFunc(Input_manager::keyboardCB);
  glutMouseFunc(Input_manager::mouseCB);
  glutMotionFunc(Input_manager::mouseMotionCB);

  glutMainLoop();
}