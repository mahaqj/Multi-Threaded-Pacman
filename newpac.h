#ifndef NEWPAC_H_INCLUDED
#define NEWPAC_H_INCLUDED
#include <math.h>
#include <cmath>
#include <cstdlib> 

struct Ghost
{
   int x = 0;
   int y = 0;
   bool isFrightened = 0;
   bool isFast = 0;
   bool speedBoosted = 0;
};

int pacmanX = 9, pacmanY = 1;
int gridX = 19, gridY = 22;
int score = 0, lives = 3;
int ROWS = 22, COLUMNS = 19;
char currentmove = 'w';
int pelletmoves = 0;
int pellet_consumed_x = 0, pellet_consumed_y = 0;

Ghost g1, g2, g3, g4;
	
void init()
{
	
	g1.x = 9;
	g1.y = 12;
	g2.x = 8;
	g2.y = 11;
	g3.x = 9;
	g3.y = 11;
	g4.x = 10;
	g4.y = 11;
	g1.isFrightened = 0;
	g2.isFrightened = 0;
	g3.isFrightened = 0;
	g4.isFrightened = 0;
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

void drawTriangle(float x, float y, float size) 
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + size); // Top vertex
    glVertex2f(x - size, y - size); // Bottom left vertex
    glVertex2f(x + size, y - size); // Bottom right vertex
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
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1}, //middle
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
    	if (score == 186) //for now
    	{
    		glColor3f(0.0, 1.0, 0.0); // Set color to red
        	glRasterPos2f(20, 10);
        	const char* gameWonMsg = "Game Won!";
        	len = strlen(gameWonMsg);
        	for (int i = 0; i < len; i++) 
        	{
            		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameWonMsg[i]);
        	}
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

void drawGhost() 
{
    // Red ghost
    glColor3f(1.0f, 0.0f, 0.0f);
    if (g1.isFrightened == 1)
    {
    	glColor3f(0.0f, 0.0f, 1.0f); //blue
    }
    if (g1.x == 9 && g1.y == 1)
    {
    	glColor3f(1.0f, 0.0f, 0.0f);
    }
    drawTriangle(g1.x + 0.5, g1.y + 0.5, 0.4);
    //drawSemiCircle(g1.x + 0.5, g1.y + 0.5, 0.4, 20);

    // Pink ghost
    glColor3f(1.0f, 0.4f, 0.7f);
    if (g2.isFrightened == 1)
    {
    	glColor3f(0.0f, 0.0f, 1.0f); //blue
    }
    if (g2.x == 8 && g2.y == 11)
    {
    	glColor3f(1.0f, 0.4f, 0.7f);
    }
    drawTriangle(g2.x + 0.5, g2.y + 0.5, 0.4);
    //drawSemiCircle(g2.x + 0.5, g2.y + 0.5, 0.4, 20);

    // Inky ghost
    glColor3f(0.0f, 0.9f, 0.9f);
    if (g3.isFrightened == 1)
    {
    	glColor3f(0.0f, 0.0f, 1.0f); //blue
    }
    if (g3.x == 9 && g3.y == 11)
    {
    	 glColor3f(0.0f, 0.9f, 0.9f);
    }
    drawTriangle(g3.x + 0.5, g3.y + 0.5, 0.4);
    //drawSemiCircle(g3.x + 0.5, g3.y + 0.5, 0.4, 20);

    // Clyde ghost
    glColor3f(1.0f, 0.5f, 0.0f);
    if (g4.isFrightened == 1)
    {
    	glColor3f(0.0f, 0.0f, 1.0f); //blue
    }
    if (g4.x == 10 && g4.y == 11)
    {
    	glColor3f(1.0f, 0.5f, 0.0f);
    }
    drawTriangle(g4.x + 0.5, g4.y + 0.5, 0.4);
    //drawSemiCircle(g4.x + 0.5, g4.y + 0.5, 0.4, 20);
}

void drawPacman() //m
{
	glColor3f(1.0f, 1.0f, 0.0f);
	drawCircle(pacmanX + 0.5, pacmanY + 0.5, 0.4, 20); 
}

void checkghost()
{
    if (lives > 0)
    {
	
	if (pacmanX == g1.x && pacmanY == g1.y && g1.isFrightened != 1)
	{
		lives--;
		init();
	}
	if (pacmanX == g2.x && pacmanY == g2.y && g2.isFrightened != 1)
	{
		lives--;
		init();
	}
	if (pacmanX == g3.x && pacmanY == g3.y && g3.isFrightened != 1)
	{
		lives--;
		init();
	}
	if (pacmanX == g4.x && pacmanY == g4.y && g4.isFrightened != 1)
	{
		lives--;
		init();
	}
	if (pacmanX == g1.x && pacmanY == g1.y && g1.isFrightened == 1)
	{
		g1.x = 9;
		g1.x = 12;
    		g1.isFrightened = 0; 
    		score += 100;
	}
	if (pacmanX == g2.x && pacmanY == g2.y && g2.isFrightened == 1)
	{
		g2.x = 8;
		g2.y = 11;
    		g2.isFrightened = 0; 
    		score += 100;
	}
	if (pacmanX == g3.x && pacmanY == g3.y && g3.isFrightened == 1)
	{
		g3.x = 9;
		g3.y = 11;
    		g3.isFrightened = 0; 
    		score += 100;
	}
	if (pacmanX == g4.x && pacmanY == g4.y && g4.isFrightened == 1)
	{
		g4.x = 10;
		g4.y = 11;
    		g4.isFrightened = 0; 
    		score += 100;
	}
    }
}

int checkteleport_gh(int x, int y) //m
{
	if (x == 19 && y == 11)
	{
		return 0;
	}
	else if (x == -1 && y == 11)
	{
		return 18;
	}
	return x;
}


bool checkghost1collision(int x, int y)
{
	if ((x == g2.x && y == g2.y) || (x == g3.x && y == g3.y) || (x == g4.x && y == g4.y))
	{
		return 1;
	}
	checkghost();
	return 0;
}

bool checkghost2collision(int x, int y)
{
	if ((x == g1.x && y == g1.y) || (x == g3.x && y == g3.y) || (x == g4.x && y == g4.y))
	{
		return 1;
	}
	checkghost();
	return 0;
}

bool checkghost3collision(int x, int y)
{
	if ((x == g2.x && y == g2.y) || (x == g1.x && y == g1.y) || (x == g4.x && y == g4.y))
	{
		return 1;
	}
	checkghost();
	return 0;
}

bool checkghost4collision(int x, int y)
{
	if ((x == g2.x && y == g2.y) || (x == g3.x && y == g3.y) || (x == g1.x && y == g1.y))
	{
		return 1;
	}
	checkghost();
	return 0;
}

void moveGhost1(Ghost& ghost) 
{
    int dx = pacmanX - ghost.x;
    int dy = pacmanY - ghost.y;
    
    int x = ghost.x;
    int y = ghost.y;
    
    if (g1.isFrightened == 1 || g2.isFrightened == 1 || g3.isFrightened == 1 || g4.isFrightened == 1)
    {
        pelletmoves++;
    }
    if (pelletmoves == 40)
    {
    	pelletmoves = 0;
    	g1.isFrightened = 0;
	g2.isFrightened = 0;
	g3.isFrightened = 0;
	g4.isFrightened = 0;
    }
 if (g1.isFrightened == 0)
 {
    if (std::abs(dx) > std::abs(dy)) 
    {
        if (dx > 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost1collision(x+1,y)) 
        {
            ghost.x += 1;
        } 
        else if (dx < 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost1collision(x-1,y)) 
        {
            ghost.x -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost1collision(x,y+1)) 
            {
                ghost.y += 1;
            }
            else if (maze[ghost.x][ghost.y - 1] != 1 && !checkghost1collision(x,y-1))  
            {
                ghost.y -= 1;
            }
        }
    } 
    else 
    {
        if (dy > 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost1collision(x,y+1))  
        {
            ghost.y += 1;
        } 
        else if (dy < 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost1collision(x,y-1)) 
        {
            ghost.y -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost1collision(x+1,y)) 
            {
                ghost.x += 1;
            }
            else if (maze[ghost.x - 1][ghost.y] != 1 && !checkghost1collision(x-1,y)) 
            {
                ghost.x -= 1;
            }
        }
    }
  }
  else
  {
  	if (std::abs(dx) > std::abs(dy)) {
    if (dx > 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost1collision(x-1,y))   {
        ghost.x -= 1;
    } else if (dx < 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost1collision(x+1,y))   {
        ghost.x += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost1collision(x,y-1))   {
            ghost.y -= 1;
        } else if (maze[ghost.x][ghost.y + 1] != 1 && !checkghost1collision(x,y+1))   {
            ghost.y += 1;
        }
    }
} else {
    if (dy > 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost1collision(x,y-1))   {
        ghost.y -= 1;
    } else if (dy < 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost1collision(x,y+1))   {
        ghost.y += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost1collision(x-1,y))   {
            ghost.x -= 1;
        } else if (maze[ghost.x + 1][ghost.y] != 1 && !checkghost1collision(x+1,y))   {
            ghost.x += 1;
        }
    }
}

  }
  x = checkteleport_gh(x, y);
}

void moveGhost2(Ghost& ghost) 
{
    int dx = pacmanX - ghost.x;
    int dy = pacmanY - ghost.y;
    
    int x = ghost.x;
    int y = ghost.y;

    if (g2.isFrightened == 0)
 {
    if (std::abs(dx) > std::abs(dy)) 
    {
        if (dx > 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost2collision(x+1,y)) 
        {
            ghost.x += 1;
        } 
        else if (dx < 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost2collision(x-1,y)) 
        {
            ghost.x -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost2collision(x,y+1))
            {
                ghost.y += 1;
            }
            else if (maze[ghost.x][ghost.y - 1] != 1 && !checkghost2collision(x,y-1))
            {
                ghost.y -= 1;
            }
        }
    } 
    else 
    {
        if (dy > 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost2collision(x,y+1)) 
        {
            ghost.y += 1;
        } 
        else if (dy < 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost2collision(x,y-1)) 
        {
            ghost.y -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost2collision(x+1,y))
            {
                ghost.x += 1;
            }
            else if (maze[ghost.x - 1][ghost.y] != 1 && !checkghost2collision(x-1,y))
            {
                ghost.x -= 1;
            }
        }
    }
  }
  else
  {
  	if (std::abs(dx) > std::abs(dy)) {
    if (dx > 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost2collision(x-1,y)) {
        ghost.x -= 1;
    } else if (dx < 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost2collision(x+1,y)) {
        ghost.x += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost2collision(x,y-1)) {
            ghost.y -= 1;
        } else if (maze[ghost.x][ghost.y + 1] != 1 && !checkghost2collision(x,y+1)) {
            ghost.y += 1;
        }
    }
} else {
    if (dy > 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost2collision(x,y-1)) {
        ghost.y -= 1;
    } else if (dy < 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost2collision(x,y+1)) {
        ghost.y += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost2collision(x-1,y)) {
            ghost.x -= 1;
        } else if (maze[ghost.x + 1][ghost.y] != 1 && !checkghost2collision(x+1,y)) {
            ghost.x += 1;
        }
    }
}

  }
  x = checkteleport_gh(x, y);
}

void moveGhost3(Ghost& ghost) 
{
    int dx = pacmanX - ghost.x;
    int dy = pacmanY - ghost.y;
    
    int x = ghost.x;
    int y = ghost.y;


    if (g3.isFrightened == 0)
 {
    if (std::abs(dx) > std::abs(dy)) 
    {
        if (dx > 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost3collision(x+1,y)) 
        {
            ghost.x += 1;
        } 
        else if (dx < 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost3collision(x-1,y)) 
        {
            ghost.x -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost3collision(x,y+1))
            {
                ghost.y += 1;
            }
            else if (maze[ghost.x][ghost.y - 1] != 1 && !checkghost3collision(x,y-1))
            {
                ghost.y -= 1;
            }
        }
    } 
    else 
    {
        if (dy > 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost3collision(x,y+1)) 
        {
            ghost.y += 1;
        } 
        else if (dy < 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost3collision(x,y-1)) 
        {
            ghost.y -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost3collision(x+1,y))
            {
                ghost.x += 1;
            }
            else if (maze[ghost.x - 1][ghost.y] != 1 && !checkghost3collision(x-1,y))
            {
                ghost.x -= 1;
            }
        }
    }
  }
  else
  {
  	if (std::abs(dx) > std::abs(dy)) {
    if (dx > 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost3collision(x-1,y)) {
        ghost.x -= 1;
    } else if (dx < 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost3collision(x+1,y)) {
        ghost.x += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost3collision(x,y-1)) {
            ghost.y -= 1;
        } else if (maze[ghost.x][ghost.y + 1] != 1 && !checkghost3collision(x,y+1)) {
            ghost.y += 1;
        }
    }
} else {
    if (dy > 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost3collision(x,y-1)) {
        ghost.y -= 1;
    } else if (dy < 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost3collision(x,y+1)) {
        ghost.y += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost3collision(x-1,y)) {
            ghost.x -= 1;
        } else if (maze[ghost.x + 1][ghost.y] != 1 && !checkghost3collision(x+1,y)) {
            ghost.x += 1;
        }
    }
}

  }
  
  x = checkteleport_gh(x, y);
  
}

void moveGhost4(Ghost& ghost) 
{
    int dx = pacmanX - ghost.x;
    int dy = pacmanY - ghost.y;
    
    int x = ghost.x;
    int y = ghost.y;

    if (g4.isFrightened == 0)
 {
    if (std::abs(dx) > std::abs(dy)) 
    {
        if (dx > 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost4collision(x+1,y)) 
        {
            ghost.x += 1;
        } 
        else if (dx < 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost4collision(x-1,y)) 
        {
            ghost.x -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost4collision(x,y+1))
            {
                ghost.y += 1;
            }
            else if (maze[ghost.x][ghost.y - 1] != 1 && !checkghost4collision(x,y-1))
            {
                ghost.y -= 1;
            }
        }
    } 
    else 
    {
        if (dy > 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost4collision(x,y+1)) 
        {
            ghost.y += 1;
        } 
        else if (dy < 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost4collision(x,y-1)) 
        {
            ghost.y -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost4collision(x+1,y))
            {
                ghost.x += 1;
            }
            else if (maze[ghost.x - 1][ghost.y] != 1 && !checkghost4collision(x-1,y))
            {
                ghost.x -= 1;
            }
        }
    }
  }
  else
  {
  	if (std::abs(dx) > std::abs(dy)) {
    if (dx > 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost4collision(x-1,y)) {
        ghost.x -= 1;
    } else if (dx < 0 && maze[ghost.x + 1][ghost.y] != 1 && !checkghost4collision(x+1,y)) {
        ghost.x += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost4collision(x,y-1)) {
            ghost.y -= 1;
        } else if (maze[ghost.x][ghost.y + 1] != 1 && !checkghost4collision(x,y+1)) {
            ghost.y += 1;
        }
    }
} else {
    if (dy > 0 && maze[ghost.x][ghost.y - 1] != 1 && !checkghost4collision(x,y-1)) {
        ghost.y -= 1;
    } else if (dy < 0 && maze[ghost.x][ghost.y + 1] != 1 && !checkghost4collision(x,y+1)) {
        ghost.y += 1;
    } else {
        if (rand() % 2 == 0 && maze[ghost.x - 1][ghost.y] != 1 && !checkghost4collision(x-1,y)) {
            ghost.x -= 1;
        } else if (maze[ghost.x + 1][ghost.y] != 1 && !checkghost4collision(x+1,y)) {
            ghost.x += 1;
        }
    }
}

  }
  x = checkteleport_gh(x, y);
}

void checkpacdot(int x, int y) //m
{
	if (pacdots[x][y] == 1)
	{
		score++;
		pacdots[x][y] = 0;
	}
	if (g1.isFrightened != 1)
	{
		if (pacdots[x][y] == 2 && g1.isFrightened == 0)
		{
			g1.isFrightened = 1;
			g2.isFrightened = 1;
			g3.isFrightened = 1;
			g4.isFrightened = 1;
			pacdots[x][y] = 0;
			pellet_consumed_x = x;
			pellet_consumed_y = y;
		}
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

bool checkwall(int x, int y) //m
{
	if (maze[x][y] == 1)
	{
		return 1;
	}
	return 0;
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
            	checkghost();
            }
            break;
        case 'a':
        case 'A':
            if (!checkwall(pacmanX-1, pacmanY))
            {
            	pacmanX--;
            	checkteleport();
            	checkpacdot(pacmanX, pacmanY);
            	checkghost();
            }
            break;
        case 's':
        case 'S':
            if (!checkwall(pacmanX, pacmanY-1))
            {
            	pacmanY--;
            	checkpacdot(pacmanX, pacmanY);
            	checkghost();
            }
            break;
        case 'd':
        case 'D':
            if (!checkwall(pacmanX+1, pacmanY))
            {
            	pacmanX++;
            	checkteleport();
            	checkpacdot(pacmanX, pacmanY);
            	checkghost();
            }
            break;
        default:
            break;
    }
    glutPostRedisplay(); //request redisplay to update the screen
}

void ui_function() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawPacdots();
    drawTitle();
    drawHomescreenghost();
    otherui();
    drawPacman();
    drawGhost();
    glutSwapBuffers();
}

#endif
