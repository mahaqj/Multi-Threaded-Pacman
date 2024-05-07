#ifndef NEWPAC_H_INCLUDED
#define NEWPAC_H_INCLUDED
#include <math.h>
#include <cmath>
#include <cstdlib> 

int gridX = 19, gridY = 22;
int score = 0, lives = 3;
int ROWS = 22, COLUMNS = 19;

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

void drawSquare(int x, int y) //m
{
    glColor3f(26.0f / 255.0f, 133.0f / 255.0f, 163.0f / 255.0f); // Outline color
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set polygon mode to draw outlines only
    glBegin(GL_QUADS); 
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset polygon mode to draw filled shapes
}


void drawCircle(float cx, float cy, float r, int num_segments) //m
{
    glBegin(GL_POLYGON); //polygon: to fill in
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

int maze[19][22] = 
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1}, //middle
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
};

void drawGrid() //m
{
	for (int x = 0; x < gridX; x++)
	{
		for (int y = 0; y < gridY; y++)
		{
			if (maze[x][y] == 1)
			{
				glColor3f(26.0f / 255.0f, 133.0f / 255.0f, 163.0f / 255.0f);
				drawSquare(x, y);
			}
		}
	}
	//drawPacdots(); // 2 in array for big pellets jissay ghost blue hojata hai
	//drawPacman();
	//drawTitle();
	//drawGhost();
	//drawHomescreenghost();
}

int title[5][35] = {
	{1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,1},
	{1,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1}
};

void drawTitle() //m
{
    glColor3f(1.0, 1.0, 0.5); 

    float x = 20.0; //start at these coordinates
    float y = 20.0;

    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 35; j++) 
        {
            if (title[i][j] == 1) 
            {
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.5, y - i * 0.5); //0.5 == square size
                glVertex2f(x + (j + 1) * 0.5, y - i * 0.5);
                glVertex2f(x + (j + 1) * 0.5, y - (i + 1) * 0.5);
                glVertex2f(x + j * 0.5, y - (i + 1) * 0.5);
                glEnd();
            }
        }
    }
}

int ghost_[14][14] = {
	{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,1,2,2,1,1,1,1,2,2,1,1,1,0},
	{0,2,2,2,2,1,1,2,2,2,2,1,1,0},
	{0,3,3,2,2,1,1,3,3,2,2,1,1,0},
	{1,3,3,2,2,1,1,3,3,2,2,1,1,1},
	{1,1,2,2,1,1,1,1,2,2,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,1,1,1,0,0,1,1,1,0,1,1},
	{1,0,0,0,1,1,0,0,1,1,0,0,0,1}
};

void drawHomescreenghost()
{
    float x = 20.5; // Start at these coordinates
    float y = 5.0;

    // Draw the first ghost
    for (int i = 0; i < 14; i++) 
    {
        for (int j = 0; j < 14; j++) 
        {
            if (ghost_[i][j] == 1) 
            {
                glColor3f(0.0f, 0.8f, 0.8f);
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
            else if (ghost_[i][j] == 2)
            {
                glColor3f(1.0f, 1.0f, 1.0f); 
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
        }
    }
    
    x += 4.5;

    for (int i = 0; i < 14; i++) 
    {
        for (int j = 0; j < 14; j++) 
        {
            if (ghost_[i][j] == 1) 
            {
                glColor3f(1.0f, 0.4f, 0.7f); 
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
            else if (ghost_[i][j] == 2)
            {
                glColor3f(1.0f, 1.0f, 1.0f); 
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
        }
    }
    
    x += 4.5;

    for (int i = 0; i < 14; i++) 
    {
        for (int j = 0; j < 14; j++) 
        {
            if (ghost_[i][j] == 1) 
            {
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
            else if (ghost_[i][j] == 2)
            {
                glColor3f(1.0f, 1.0f, 1.0f); 
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
        }
    }
    
    x += 4.5;

    for (int i = 0; i < 14; i++) 
    {
        for (int j = 0; j < 14; j++) 
        {
            if (ghost_[i][j] == 1) 
            {
                glColor3f(1.0f, 0.5f, 0.0f);
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();
            }
            else if (ghost_[i][j] == 2)
            {
                glColor3f(1.0f, 1.0f, 1.0f); 
                glBegin(GL_QUADS);
                glVertex2f(x + j * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - i * 0.23);
                glVertex2f(x + (j + 1) * 0.23, y - (i + 1) * 0.23);
                glVertex2f(x + j * 0.23, y - (i + 1) * 0.23);
                glEnd();   
            }
        }
    }
}

void otherui()
{
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
}

int pacdots[19][22] = 
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 2, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 2, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, //middle
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 2, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 2, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void drawPacdots() //m
{
    glColor3f(1.0, 1.0, 0.8);
    
    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            if (pacdots[x][y] == 1)
            {
                drawCircle(x + 0.5, y + 0.5, 0.075, 20); 
            }
            if (pacdots[x][y] == 2)
            {
            	 drawCircle(x + 0.5, y + 0.5, 0.25, 20);
            }
        }
    }
}

#endif
