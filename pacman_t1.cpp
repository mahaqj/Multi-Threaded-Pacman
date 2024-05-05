#include <GL/glut.h>
#include "pacman_t1.h"

#define COLUMNS 19
#define ROWS 23

void init();
void display_callback();
void reshape_callback(int, int);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700, 750);
	glutCreateWindow("Pacman");
	glutDisplayFunc(display_callback); 
	glutReshapeFunc(reshape_callback);
	init();
	
	glutMainLoop(); 
	
	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.2, 1.0); //sets background colour
	initGrid(COLUMNS, ROWS);
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	drawGrid();
	glutSwapBuffers(); 
}

void reshape_callback(int w, int h)
{
    float aspect_ratio = (float)COLUMNS / ROWS; 

    if (w > h) 
    {
        glViewport((w - h) / 2, 0, h * aspect_ratio, h);
    } else 
    {
        glViewport(0, (h - w) / 2, w, w / aspect_ratio);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}
