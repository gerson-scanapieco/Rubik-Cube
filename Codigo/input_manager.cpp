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
        /*
        drawMode = ++drawMode % 3;
        if(drawMode == 0)        // fill mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
        else if(drawMode == 1)  // wireframe mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        else                    // point mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        */
        break;

    case 43: // tecla +
        current_model_manager->key_pressed(key,x,y);
        //CuboMagico::espacamento+=0.15;
        break;
    case 45: //tecla -
        current_model_manager->key_pressed(key,x,y);
        //if(CuboMagico::espacamento >= 2.15)
        //  CuboMagico::espacamento -= 0.15;
    default:
        ;
    }
    //glutPostRedisplay();
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
        current_renderer->set_camera_angle_x(x - mouseX);
        current_renderer->set_camera_angle_y(y - mouseY);
        //cameraAngleY += (x - mouseX);
        //cameraAngleX += (y - mouseY);
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
        //cameraDistance-=(y - mouseY) * 0.2f;
        mouseY = y;
    }

}