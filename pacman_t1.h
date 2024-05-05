#ifndef PACMAN_T1_H_INCLUDED
#define PACMAN_T1_H_INCLUDED
#include <math.h>
#include <cmath>
#include <cstdlib> 

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
//m
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

int gridX, gridY;
int pacmanX = 9, pacmanY = 1;
int score = 0, lives = 3;

void initGrid(int x, int y) //m
{
	gridX = x;
	gridY = y;
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

struct Ghost
{
   int x = 0;
   int y = 0;
};

void moveGhost(Ghost& ghost) 
{
    int dx = pacmanX - ghost.x;
    int dy = pacmanY - ghost.y;

    if (std::abs(dx) > std::abs(dy)) 
    {
        if (dx > 0 && maze[ghost.x + 1][ghost.y] != 1) 
        {
            ghost.x += 1;
        } 
        else if (dx < 0 && maze[ghost.x - 1][ghost.y] != 1) 
        {
            ghost.x -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x][ghost.y + 1] != 1)
            {
                ghost.y += 1;
            }
            else if (maze[ghost.x][ghost.y - 1] != 1)
            {
                ghost.y -= 1;
            }
        }
    } 
    else 
    {
        if (dy > 0 && maze[ghost.x][ghost.y + 1] != 1) 
        {
            ghost.y += 1;
        } 
        else if (dy < 0 && maze[ghost.x][ghost.y - 1] != 1) 
        {
            ghost.y -= 1;
        }
        else
        {
            if (rand() % 2 == 0 && maze[ghost.x + 1][ghost.y] != 1)
            {
                ghost.x += 1;
            }
            else if (maze[ghost.x - 1][ghost.y] != 1)
            {
                ghost.x -= 1;
            }
        }
    }
}


Ghost g1, g2, g3, g4;
	
void drawGhost()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	drawCircle(g1.x + 0.5, g1.y + 0.5, 0.4, 20); 
	
	glColor3f(1.0f, 1.0f, 0.0f);
	drawCircle(g2.x + 0.5, g2.y + 0.5, 0.4, 20); 
	
	glColor3f(1.0f, 0.0f, 1.0f);
	drawCircle(g3.x + 0.5, g3.y + 0.5, 0.4, 20); 
	
	glColor3f(1.0f, 0.5f, 0.5f);
	drawCircle(g4.x + 0.5, g4.y + 0.5, 0.4, 20); 
}



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

void drawPacman() //m
{
	glColor3f(1.0f, 1.0f, 0.0f);
	drawCircle(pacmanX + 0.5, pacmanY + 0.5, 0.4, 20); 
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
	drawPacdots(); // 2 in array for big pellets jissay ghost blue hojata hai
	drawPacman();
	drawTitle();
	drawGhost();
}

#endif
