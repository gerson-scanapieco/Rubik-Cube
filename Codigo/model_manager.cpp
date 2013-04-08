#include "model_manager.hpp"

CuboMagico* Model_manager::current_drawable = NULL;

void init(){

}

void Model_manager::init(CuboMagico *drawable){
  current_drawable = drawable;
  CuboMagico * cubo_magico = new CuboMagico;
  Model_manager::current_drawable = cubo_magico;
}

void Model_manager::key_pressed(unsigned char key, int x, int y){
  this->current_drawable->reaction_to_keyboard(key,x,y);
}

void Model_manager::mouse_click(int button, int stat, int x, int y){
  this->current_drawable->reaction_to_mouse_motion(button,stat,x,y);
}

void Model_manager::mouse_motion(int x, int y){
  this->current_drawable->reaction_to_click(x,y);
}
