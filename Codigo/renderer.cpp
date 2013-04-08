#include "renderer.hpp"

Model_manager * Renderer::current_model_manager = NULL;
int Renderer::screen_width = 800;
int Renderer::screen_height = 600;
float Renderer::camera_distance = 15.0f;
float Renderer::camera_angle_x = 0;
float Renderer::camera_angle_y = 0;

void Renderer::init(Model_manager *model_manager){
    current_model_manager = model_manager;
    initGLUT();
    initGL();
    initLights();
}
///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int Renderer::initGLUT(){
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    //glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(Renderer::screen_width, Renderer::screen_height);  // window size

    glutInitWindowPosition(100, 100);               // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow("cubo");     // param is the title of window

    // register GLUT callback functions
    /*
    glutDisplayFunc(Renderer::displayCB);
    glutTimerFunc(33, Renderer::timerCB, 33);             // redraw only every given millisec
    glutReshapeFunc(Renderer::reshapeCB);
    glutKeyboardFunc(Renderer::current_input_manager->keyboardCB);
    glutMouseFunc(Renderer::current_input_manager->mouseCB);
    glutMotionFunc(Renderer::current_input_manager->mouseMotionCB);
    */
    return handle;
}


///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void Renderer::initGL(){
    glShadeModel(GL_FLAT);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
}

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void Renderer::drawString(const char *str, int x, int y, float color[4], void *font){
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

///////////////////////////////////////////////////////////////////////////////
// clean up global vars
///////////////////////////////////////////////////////////////////////////////
void Renderer::clearSharedMem(){
    
}



///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void Renderer::initLights(){
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}


///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void Renderer::setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}


///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void Renderer::showInfo(){
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, Renderer::screen_width, 0, Renderer::screen_height); // set to orthogonal projection

    float color[4] = {1, 1, 1, 1};

    //std::stringstream ss;
    //ss << "Aperte \"+\" para aumentar o espacamento ou \"-\" para diminuir"  << std::ends;
    //drawString(ss.str().c_str(), 1, screen_height-text_height, color, font);
    //ss.str("");
    /*
    ss << "Use o mouse para girar a camera" << ends;      
    drawString(ss.str().c_str(), 1, screenHeight-TEXT_HEIGHT, color, font);
    ss.str("");

    ss << "Use Ctrl + mouse para brincar com o cubo" << ends;
    drawString(ss.str().c_str(), 1, screenHeight-TEXT_HEIGHT, color, font);
    ss.str("");
    */
    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}

///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void Renderer::toPerspective(){
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)Renderer::screen_width, (GLsizei)Renderer::screen_height);

    // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)(Renderer::screen_width)/Renderer::screen_height, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::change_draw_mode(){


}

//=============================================================================
// CALLBACKS
//=============================================================================

void Renderer::displayCB(){
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    // tramsform camera
    glTranslatef(0, 0, -Renderer::camera_distance);
    glRotatef(camera_angle_x, 1, 0, 0);   // pitch
    glRotatef(camera_angle_y, 0, 1, 0);   // heading

    //TODO
    //Implementar codigo de renderizacao do cubo magico

    // print 2D text
    float pos[4] = {-4.0f,3.5f,0,1};
    float color[4] = {1,1,1,1};
   
    //showInfo();     // print max range of glDrawRangeElements

    glPopMatrix();

    glutSwapBuffers();
}


void Renderer::reshapeCB(int w, int h){
    Renderer::screen_width = w;
    Renderer::screen_height = h;
    Renderer::toPerspective();
}


void Renderer::timerCB(int millisec){
    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}

 void Renderer::set_camera_angle_x(int angle){
   Renderer::camera_angle_x+=angle;
 }

 void Renderer::set_camera_angle_y(int angle){
    Renderer::camera_angle_y+=angle;
 }
 
 void Renderer::set_camera_distance(float distance){
    Renderer::camera_distance-=distance;
 }