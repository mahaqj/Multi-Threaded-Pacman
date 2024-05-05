#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <cstdio>
#include "pacman_t1.h"

#define COLUMNS 19
#define ROWS 22
char currentmove = ' ';

void init() //m
{
	glClearColor(0.0, 0.0, 0.2, 1.0); //sets the background colour
	initGrid(COLUMNS, ROWS);
}

void display_callback() //m
{
	glClear(GL_COLOR_BUFFER_BIT); //clears buffer specified by the argument
	drawGrid();
	
	//printing score:
	glColor3f(1.0, 1.0, 1.0);
    	glRasterPos2f(20, 5); 
    	char scoreText[20];
    	snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    	int len = strlen(scoreText);
    	for (int i = 0; i < len; i++) 
    	{
        	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);
    	}
    	
    	//printing lives:
    	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(20, 4);
	char livesText[20];
	snprintf(livesText, sizeof(livesText), "Lives: %d", lives);
	len = strlen(livesText);
	for (int i = 0; i < len; i++) 
	{
    		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, livesText[i]);
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

void movement() //m
{
    switch (currentmove)
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
    glutPostRedisplay(); //request redisplay to update the screen
}


void keyboard_callback(unsigned char key, int x, int y) //m
{
    currentmove = key;
}

void update(int dummy) //m
{
    movement();
    glutTimerFunc(200, update, 0); // set the next update after 100ms
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
	
	glutTimerFunc(200, update, 0);
	
	glutMainLoop(); //window will be displayed + processing will start
	
	return 0;
}
