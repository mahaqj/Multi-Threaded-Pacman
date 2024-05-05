#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <cstdio>
#include "pacman_t1.h"
//max score can be 190 --------------
#define COLUMNS 19
#define ROWS 22

void init() //m
{
	glClearColor(0.0, 0.0, 0.2, 1.0); //sets the background colour
	initGrid(COLUMNS, ROWS);
}

void display_callback() //m
{
	glClear(GL_COLOR_BUFFER_BIT); //clears buffer specified by the argument
	drawGrid();
	
	
	
	glColor3f(1.0, 1.0, 1.0); // Set text color to white
    glRasterPos2f(20, 20); // Set position for score display
    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score); // Convert score to string
    int len = strlen(scoreText);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]); // Render each character of the score
    }
	mobilizeGhost4(ghost4);
	glutSwapBuffers(); //next frame is displayed on the screen
    glutPostRedisplay();
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

bool checkwall(int x, int y) //m
{
	if (maze[x][y] == 1)
	{
		return 1;
	}
	return 0;
}

void checkpacdot(int x, int y) //m
{
	if (pacdots[x][y] == 1)
	{
		score++;
		pacdots[x][y] = 0;
	}
}

void checkteleport() //m
{
	if (pacmanX == 19 && pacmanY == 11)
	{
		pacmanX = 0;
	}
	else if (pacmanX == -1 && pacmanY == 11)
	{
		pacmanX = 18;
	}
}

void keyboard_callback(unsigned char key, int x, int y) //m
{
    switch (key)
    {
        case 'w':
        case 'W': 
            if (!checkwall(pacmanX, pacmanY+1))
            {
            	pacmanY++;
            	checkpacdot(pacmanX, pacmanY);
            }
            break;
        case 'a':
        case 'A':
            if (!checkwall(pacmanX-1, pacmanY))
            {
            	pacmanX--;
            	checkteleport();
            	checkpacdot(pacmanX, pacmanY);
            }
            break;
        case 's':
        case 'S':
            if (!checkwall(pacmanX, pacmanY-1))
            {
            	pacmanY--;
            	checkpacdot(pacmanX, pacmanY);
            }
            break;
        case 'd':
        case 'D':
            if (!checkwall(pacmanX+1, pacmanY))
            {
            	pacmanX++;
            	checkteleport();
            	checkpacdot(pacmanX, pacmanY);
            }
            break;
        default:
            break;
    }
    //mobilizeGhost4(ghost4);
    glutPostRedisplay(); //request redisplay to update the screen
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

	glutMainLoop(); //window will be displayed + processing will start
	
	return 0;
}