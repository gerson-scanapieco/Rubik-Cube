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
      //raise_gap();
    break;
    case 45: //tecla -
      //lower_gap();
    break;
    case 'x':
      this->animation();
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
				cubos[i-1][j-1][k-1]->matriz_de_transformacao[12] = i * 2.2;
				cubos[i-1][j-1][k-1]->matriz_de_transformacao[13] = j * 2.2;
				cubos[i-1][j-1][k-1]->matriz_de_transformacao[14] = k * 2.2;
			}
		}
	}
}

void CuboMagico::draw(){

  check_rotation();

  for(int i=0; i < 3; i++){
    for(int j=0; j<3; j++){
      for(int k=0; k<3;k++){
    	  glEnableClientState(GL_NORMAL_ARRAY);
    	  glEnableClientState(GL_COLOR_ARRAY);
    	  glEnableClientState(GL_VERTEX_ARRAY);

    	  glNormalPointer(GL_FLOAT, 0, cubos[i][j][k]->normals);
    	  glColorPointer(3, GL_FLOAT, 0, cubos[i][j][k]->colors);
    	  glVertexPointer(3, GL_FLOAT, 0, cubos[i][j][k]->vertices);

    	  glPushMatrix();
    		 glMatrixMode(GL_MODELVIEW);
         if(cubos[i][j][k]->is_rotating == 1){
          glTranslatef(0,4.4,4.4);
          glRotatef(angle,1,0,0);
          glTranslatef(0,-4.4,-4.4);
        }
        glTranslatef(cubos[i][j][k]->matriz_de_transformacao[12],cubos[i][j][k]->matriz_de_transformacao[13],
          cubos[i][j][k]->matriz_de_transformacao[14]);
    		 //glMultMatrixf(cubos[i][j][k]->matriz_de_transformacao);   
    	   glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubos[i][j][k]->indices);
    	  glPopMatrix();

    	  glDisableClientState(GL_VERTEX_ARRAY);
    	  glDisableClientState(GL_COLOR_ARRAY);
    	  glDisableClientState(GL_NORMAL_ARRAY);
      }
	  }
  }
}

//Rotaciona a matriz de forma a simular uma rotacao numa face do cubo
void CuboMagico::rotate_face(int face, int orientation){
          //matriz2[j][2-i] = matriz1[i][j];
  int k,l;

  if(face >=0 && face <= 2){

  Cubo* temp [3][3][3];
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      cubos[face][i][j]->is_rotating = 1;
      temp[face][j][2-i] = cubos[face][i][j];
    }
  }
  //memcpy(cubos,temp,9*sizeof(Cubo*));
  }
  else if (face >=3 && face <=4){
    Cubo* temp [3][3][3];
    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
       cubos[i][face%3][j]->is_rotating = 1;
       temp[j][face%3][2-i] = cubos[i][face%3][j];
      }
    }
  }
  else if (face >=5 && face <=8){
    Cubo* temp [3][3][3];
    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
        cubos[i][j][face%3]->is_rotating = 1;
        temp[j][2-i][face%3] = cubos[i][j][face%3];
      }
    }
  }
  ///draw_rotation(face,orientation);

}

void CuboMagico::draw_rotation(int face, int orientation){
  float angle;

  if (face >=0 && face <=3){



  }


}

void CuboMagico::animation(){
  this->rotate_face(3,0);
}


/*
void CuboMagico::raise_gap(){
  gap+=0.15;
  for(int j=0; j<27;j++){
      //M3DMatrix44f matriz;
      //m3dTranslationMatrix44(matriz, cubos[j].matriz_de_transformacao[12] *gap, cubos[j].matriz_de_transformacao[13] *gap, 
      //            cubos[j].matriz_de_transformacao[14] *gap); 
      //m3dMatrixMultiply44(cubos[j].matriz_de_transformacao,cubos[j].matriz_de_transformacao,matriz);
    cubos[j].matriz_de_transformacao[12]+=gap;
    cubos[j].matriz_de_transformacao[13]+=gap;
    cubos[j].matriz_de_transformacao[14]+=gap;
    }
    glutPostRedisplay();
}


void CuboMagico::lower_gap(){
  if(gap > 1.2)
    gap -= 0.15;
  for(int j=0; j<27;j++){
      M3DMatrix44f matriz;
      m3dTranslationMatrix44(matriz, cubos[j].matriz_de_transformacao[12] *gap, cubos[j].matriz_de_transformacao[13] *gap, 
                  cubos[j].matriz_de_transformacao[14] *gap); 
      m3dMatrixMultiply44(cubos[j].matriz_de_transformacao,cubos[j].matriz_de_transformacao,matriz);
    }
    glutPostRedisplay();
}
*/
void Cubo::init(){
	memcpy(this->indices, default_indices, sizeof(default_indices));
	memcpy(this->vertices, default_vertices, sizeof(default_vertices));
	memcpy(this->colors, default_colors, sizeof(default_colors));
	memcpy(this->normals, default_normals, sizeof(default_normals));
}

void CuboMagico::check_rotation(){

  if(angle > 90){
    angle = 0;

    for(int i=0; i < 3; i++){
      for(int j=0; j<3; j++){
        for(int k=0; k<3;k++){
          cubos[i][j][k]->is_rotating = 0;
        }
      }
    }

  }
  else
    angle+=2;
}