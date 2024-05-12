#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <cstdio>
#include "pacman_t1.h"

#define COLUMNS 19
#define ROWS 22

void display_callback() //m
{
	glClear(GL_COLOR_BUFFER_BIT); //clears buffer specified by the argument
	drawGrid();
	
	//printing score:
	glColor3f(1.0, 1.0, 1.0);
    	glRasterPos2f(20, 12); 
    	char scoreText[20];
    	snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    	int len = strlen(scoreText);
    	for (int i = 0; i < len; i++) 
    	{
        	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
    	}
    	
    	//printing string:
    	glColor3f(1.0, 1.0, 0.8);
    	glRasterPos2f(28, 16); 
    	const char* str = "By Maha Qaiser & Nabeeha Shafiq";
    	len = strlen(str);
    	for (int i = 0; i < len; i++) 
    	{
        	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    	}
	
    	//printing lives:
    	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(20, 11);
	char livesText[20];
	snprintf(livesText, sizeof(livesText), "Lives: %d", lives);
	len = strlen(livesText);
	for (int i = 0; i < len; i++) 
	{
    		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, livesText[i]);
	}
    	
    	if (lives <= 0) 
    	{
        	glColor3f(1.0, 0.0, 0.0); // Set color to red
        	glRasterPos2f(20, 10);
        	const char* gameOverMsg = "Game Over!";
        	len = strlen(gameOverMsg);
        	for (int i = 0; i < len; i++) 
        	{
            		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOverMsg[i]);
        	}
    	}
    	
	glutSwapBuffers(); //next frame is displayed on the screen
}

void reshape_callback(int w, int h) //m
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); //set up the coordinate system
    glLoadIdentity();
    
    // adjust projection to match the window dimensions
    if (w <= h) 
    {
        glOrtho(0.0, COLUMNS, 0.0, COLUMNS * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    } else 
    {
        glOrtho(0.0, ROWS * (GLfloat)w / (GLfloat)h, 0.0, ROWS, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard_callback(unsigned char key, int x, int y) //m
{
    currentmove = key;
}

void updatePacman(int dummy) 
{
    movement(); 
    glutTimerFunc(200, updatePacman, 0);
}

void updateGhosts(int dummy) 
{
    moveGhost1(g1);  
    moveGhost2(g2);
    moveGhost3(g3);
    moveGhost4(g4);
    glutTimerFunc(800, updateGhosts, 0); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	//initialise glut when program called
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("Pacman");
	glutDisplayFunc(display_callback); 
	glutReshapeFunc(reshape_callback);
	glutKeyboardFunc(keyboard_callback);
	init();
	
	//glutTimerFunc(100, update, 0); // start the movement update loop
	//^ too fast. sorta can maybe be used for ghost boost?
	
	glutTimerFunc(200, updatePacman, 0);
    	glutTimerFunc(800, updateGhosts, 0);  
	
	glutMainLoop(); //window will be displayed + processing will start
	
	return 0;
}
