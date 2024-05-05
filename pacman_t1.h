#ifndef PACMAN_T1_H_INCLUDED
#define PACMAN_T1_H_INCLUDED
#include <math.h>

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
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1}, //
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
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, //
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int gridX, gridY;
int pacmanX = 9, pacmanY = 1;
int score = 0;
struct Ghost
{
    int x;
    int y;
    float color;
    bool isScared=false;
    int moveStep;
};

void mobilizeGhost4(Ghost &ghost) {
    if (ghost.moveStep == 0) {
        ghost.y += 1;  // Initial move up by 1
    } else if (ghost.moveStep == 1) {
        ghost.x += 1;  // Move right by 1
    } else if (ghost.moveStep == 2) {
        ghost.y += 2;  // Move up by 2
    } else if (ghost.moveStep == 3) {
        ghost.x += 2;  // Move right by 2
    } else if (ghost.moveStep == 4) {
        ghost.y += 2;  // Move up by 2
    } else if (ghost.moveStep == 5) {
        ghost.x -= 2;  // Move left by 2
    } else if (ghost.moveStep == 6) {
        ghost.y += 3;  // Move up by 3
    } else if (ghost.moveStep == 7) {
        ghost.x += 7;  // Move right by 7
    } 
    ghost.moveStep++;  // Increment the step counter
    if (ghost.moveStep > 7) ghost.moveStep = 0;  // Reset the sequence if it ends
}

void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void square(int x, int y) //m
{
    glBegin(GL_QUADS); 
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd(); 
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

void drawPacdots() //m
{
    glColor3f(1.0, 1.0, 0.8);
    
    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            if (pacdots[x][y] == 1)
            {
                float centerX = x + 0.5;
                float centerY = y + 0.5;
                
                drawCircle(centerX, centerY, 0.06, 20); 
            }
        }
    }
}
Ghost ghost4;
void DrawGhosts()//n
{//spawns 4 ghosts in centre closed ghost home 
  Ghost ghost1;
  ghost1.x=9;
         ghost1.y=11;
         //ghost1=ghost1.color=
         ghost1.isScared=false;
glColor3f(1.0f, 0.5f, 0.6f);
drawCircle(ghost1.x+0.5,ghost1.y+0.5,0.4,20);
  Ghost ghost2;
  ghost2.x=10;
         ghost2.y=11;
ghost2.isScared=false;
glColor3f(0.0f, 0.0f, 1.0f);
drawCircle(ghost2.x+0.5,ghost2.y+0.5,0.4,20);

  Ghost ghost3;
  ghost3.x=8;
         ghost3.y=11;
ghost3.isScared=false;
glColor3f(1.0f, 0.0f, 0.0f);
drawCircle(ghost3.x+0.5,ghost3.y+0.5,0.4,20);

  
  ghost4.x=9;
         ghost4.y=12;
         //ghost1=ghost1.color=
         ghost4.isScared=false;
         ghost4.moveStep=0;
glColor3f(1.0f, 0.5f, 0.0f);
drawCircle(ghost4.x+0.5,ghost4.y+0.5,0.4,20);


  
}
void drawPacman() //m
{
	glColor3f(1.0f, 1.0f, 0.0f);
	drawCircle(pacmanX + 0.5, pacmanY + 0.5, 0.4, 20); 
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

				square(x, y);
			}
		}
	}
	drawPacdots(); //write 2 in array for big pellets jissay ghost blue hojata hai
	drawPacman();
   // mobilizeGhost4(ghost4);
    DrawGhosts();
}



/*void smallsquare()
{//anvdfhdbvs,jf
    glBegin(GL_QUADS); 
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}*/

#endif