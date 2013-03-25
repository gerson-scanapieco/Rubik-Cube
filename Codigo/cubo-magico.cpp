#include "cubo-magico.hpp"

 //inicializa variavel estatica
 CuboMagico* CuboMagico::currentInstance = NULL;
 float CuboMagico::espacamento = 2.5;

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


static void CuboMagico::drawCallback(){
	CuboMagico::currentInstance->draw();
}

void CuboMagico::setupDrawCallback(){
	CuboMagico::currentInstance = this;
  //::glutDisplayFunc(CuboMagico::drawCallback);
}


void CuboMagico::set_groups(){
	int i,j,k,pos=0;

	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			for(k=1; k<=3; k++){
				cubos[pos].grp_x = i;
				cubos[pos].grp_y = j;
				cubos[pos].grp_z = k;
				pos++;
			}
		}
	}
}

CuboMagico::CuboMagico(){
	for(int i=0; i<27;i++){
		this->cubos[i].init();
	}
}

void CuboMagico::draw(){

  for(int j=0; j < 27; j++){
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glEnableClientState(GL_COLOR_ARRAY);
	  glEnableClientState(GL_VERTEX_ARRAY);

	  glNormalPointer(GL_FLOAT, 0, currentInstance->cubos[j].normals);
	  glColorPointer(3, GL_FLOAT, 0, currentInstance->cubos[j].colors);
	  glVertexPointer(3, GL_FLOAT, 0, currentInstance->cubos[j].vertices);

	  glPushMatrix();
	  glTranslatef(currentInstance->cubos[j].grp_x*espacamento, currentInstance->cubos[j].grp_y*espacamento, 
	  						 currentInstance->cubos[j].grp_z*espacamento); 
	  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, currentInstance->cubos[j].indices);
	  glPopMatrix();

	  glDisableClientState(GL_VERTEX_ARRAY);
	  glDisableClientState(GL_COLOR_ARRAY);
	  glDisableClientState(GL_NORMAL_ARRAY);
	}
}

Cubo::Cubo(){
}

void Cubo::init(){
	memcpy(this->indices, default_indices, sizeof(default_indices));
	memcpy(this->vertices, default_vertices, sizeof(default_vertices));
	memcpy(this->colors, default_colors, sizeof(default_colors));
	memcpy(this->normals, default_normals, sizeof(default_normals));
}
