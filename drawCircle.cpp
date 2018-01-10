#include <GL/glut.h>
#include <iostream>
#include <list>
using namespace std;
 
struct node{
int data;
int x;
int y;
};
list<node> nodeList;
int count=0;
void circlePlotPoints(int xCenter, int yCenter, int x, int y )
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2i(xCenter + x, yCenter + y );
		glVertex2i(xCenter - x, yCenter + y );
		glVertex2i(xCenter + x, yCenter - y );
		glVertex2i(xCenter - x, yCenter - y );
		glVertex2i(xCenter + y, yCenter + x );
		glVertex2i(xCenter - y, yCenter + x );
		glVertex2i(xCenter + y, yCenter - x );
		glVertex2i(xCenter - y, yCenter - x );
	glEnd();
}

void drawCircle( int xCenter, int yCenter, int radius )
{
	int x = 0, y = radius, p = 1 - radius;
	node xnode;
	circlePlotPoints( xCenter, yCenter, x, y );
	while( x < y )
	{
		x++;
		if( p < 0 )
		{
			p += (2 * x) + 1;
		}
		else
		{
			y--;
			p += ( 2*(x-y) ) +1;
		}
		circlePlotPoints(xCenter, yCenter, x, y);
	}
	xnode.x=xCenter;
	xnode.y=yCenter;
	xnode.data=count++;
	nodeList.push_back(xnode);
}
/*void drawLine( int xStart, int yStart, int xEnd, int yEnd )
{
	int a,b,c,d;
	a=xStart;
	b=xEnd;
	c=yStart;
	d=yEnd;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	while((a<=b)&&(c<=d))
	{
	
		glVertex2i(a++, c++ );
	}
	glEnd();
}*/


void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void mouseClick( int button, int state, int x, int y )
{
	if( button == GLUT_LEFT_BUTTON )
	{
		if( state == GLUT_DOWN )
		{
			
			drawCircle(x, 500-y, 20);
			glutSwapBuffers();
		//	drawLine(x+20,500-y, x+40,y+40);
		for (list<node>::iterator it=nodeList.begin(); it != nodeList.end(); ++it)
			{
				node xnode=*it;
				cout<<xnode.data;
			}
    			//cout << ' ' << *it;
		}
	}
}

int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("BFS");
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 500);
	
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	
	glutMainLoop();
	
	return 0;
}




