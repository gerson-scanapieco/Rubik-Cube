#include "input_manager.hpp"

Model_manager * Input_manager::current_model_manager = NULL;
Renderer *Input_manager::current_renderer = NULL;
int Input_manager::mouseX = 0;
int Input_manager::mouseY = 0;
int Input_manager::mouseLeftDown = 0;
int Input_manager::mouseRightDown = 0;
int Input_manager::mouseMiddleDown = 0;

void Input_manager::init(Model_manager *model_manager, Renderer *renderer){
    current_renderer = renderer;
    current_model_manager = model_manager;
}

void Input_manager::keyboardCB(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27: // ESCAPE
        exit(0);
        break;
    case 'd': // switch rendering modes (fill -> wire -> point)
    case 'D':
        current_renderer->change_draw_mode();
        break;
    case 43: // tecla +
        current_model_manager->key_pressed(key,x,y);
        break;
    case 45: //tecla -
        current_model_manager->key_pressed(key,x,y);
        break;
    case 'x':
        current_model_manager->key_pressed(key,x,y);
        break;
    default:
        ;
    }
}

void Input_manager::mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void Input_manager::mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        current_renderer->set_camera_angle_y(x - mouseX);
        current_renderer->set_camera_angle_x(y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        //TODO
        //Colocar aqui chamada da funcao de girar as faces
    }

    if(mouseMiddleDown)
    {
        current_renderer->set_camera_distance((y - mouseY) * 0.2f);
        mouseY = y;
    }

}