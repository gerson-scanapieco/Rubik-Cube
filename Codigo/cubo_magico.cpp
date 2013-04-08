#include "cubo_magico.hpp"

  //vertices array
 GLfloat default_vertices[] = {1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
                        1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
                        1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
                       -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)
//normals array
GLfloat default_normals[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
                      1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
                      0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
                     -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
                      0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
                      0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

// color array
GLfloat default_colors[]   = { 1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,   // v0,v1,v2,v3 (front)
                      0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v3,v4,v5 (right)
                      1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v5,v6,v1 (top)
                      0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v1,v6,v7,v2 (left)
                      1, 0, 1,   1, 0, 1,   1, 0, 1,   1, 0, 1,   // v7,v4,v3,v2 (bottom)
                      0, 1, 1,   0, 1, 1,   0, 1, 1,   0, 1, 1 }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() 
GLubyte default_indices[]  = { 0, 1, 2,   2, 3, 0,      // front
                     4, 5, 6,   6, 7, 4,      // right
                     8, 9,10,  10,11, 8,      // top
                    12,13,14,  14,15,12,      // left
                    16,17,18,  18,19,16,      // bottom
                    20,21,22,  22,23,20 };    // back


  void CuboMagico::reaction_to_keyboard(unsigned char key, int x, int y){
    //TODO funcao q implementa a transformacao do cubo em caso de teclado
    switch(key)
    {
    case 43: // tecla +
      gap+=0.15;
    break;
    case 45: //tecla -
      if(gap > 1.2)
        gap -= 0.15;
    break;
    default:
        ;
    }
    glutPostRedisplay();
  }

  void CuboMagico::reaction_to_mouse_motion(int button, int stat, int x, int y){
    //TODO funcao q implementa a transformacao do cubo em caso de mouse motion

  }

  void CuboMagico::reaction_to_click(int x, int y){
    //TODO funcao q implementa a transformacao do cubo em caso de mouse

  }

void CuboMagico::set_initial_translation(){
	int i,j,k,pos=0;

	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			for(k=1; k<=3; k++){
				cubos[pos].matriz_de_transformacao[12] = i ;
				cubos[pos].matriz_de_transformacao[13] = j ;
				cubos[pos].matriz_de_transformacao[14] = k ;
				pos++;
			}
		}
	}
}

void CuboMagico::draw(){

  for(int j=0; j < 27; j++){
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glEnableClientState(GL_COLOR_ARRAY);
	  glEnableClientState(GL_VERTEX_ARRAY);

	  glNormalPointer(GL_FLOAT, 0, cubos[j].normals);
	  glColorPointer(3, GL_FLOAT, 0, cubos[j].colors);
	  glVertexPointer(3, GL_FLOAT, 0, cubos[j].vertices);

	  glPushMatrix();
		 glMatrixMode(GL_MODELVIEW);
     glTranslatef(cubos[j].matriz_de_transformacao[12] *gap, cubos[j].matriz_de_transformacao[13] *gap, 
                  cubos[j].matriz_de_transformacao[14] *gap);
		 glMultMatrixf(cubos[j].matriz_de_transformacao);   
	   glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubos[j].indices);
	  glPopMatrix();

	  glDisableClientState(GL_VERTEX_ARRAY);
	  glDisableClientState(GL_COLOR_ARRAY);
	  glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void CuboMagico::lower_gap(){
    if(this->gap >= 2.5)
        this-> gap -= 0.15;
}

void CuboMagico::raise_gap(){
    this->gap+=0.15;
}

void Cubo::init(){
	memcpy(this->indices, default_indices, sizeof(default_indices));
	memcpy(this->vertices, default_vertices, sizeof(default_vertices));
	memcpy(this->colors, default_colors, sizeof(default_colors));
	memcpy(this->normals, default_normals, sizeof(default_normals));
}
