#include <GL/glut.h>
#include <iostream>
#include <list>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
#include<stdio.h>
//#include <tchar.h>
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
	void Sprint(int,int,int);
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
	Sprint(xCenter,yCenter,count);
	xnode.x=xCenter;
	xnode.y=yCenter;
	xnode.data=count++;
	nodeList.push_back(xnode);
}
void drawLine( int xStart, int yStart, int xEnd, int yEnd )
{
	int x1,y1,x2,y2,dx,dy,step,i,xinc,yinc;
	x1=xStart;
	x2=xEnd;
	y1=yStart;
	y2=yEnd;
	dx=abs(x1-x2);
	dy=abs(y1-y2);
	if(dx>dy){
		step=dx;
		}
	else{
		step=dy;
		}
	xinc=(float)dx/step;
	yinc=dy/(float)step;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	printf("step=%d,xinc=%d,yinc=%d",dx,xinc,yinc);
	for(i=0;i<=step;i++)
	{
		glVertex2i(x1,y1);
		glVertex2i(xEnd, yEnd);
		x1+=(int)xinc;
		y1+=(int)yinc;
	}
glEnd();	
}

void Sprint( int x, int y, int num)
{
	int l,i;
	char *st,stx[3];
	stx[0]=48+num;
	stx[2]='\0';
	st=stx;
	glRasterPos2i( x-7, y-7); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[0]); 

}

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
			//drawLine(x+20,500-y, x+40,y+40);
		for (list<node>::iterator it=nodeList.begin(); it != nodeList.end(); ++it)
			{
				node xnode=*it;
				cout<<xnode.data;
			}
    			//cout << ' ' << *it;
		}
	}
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
	{
		drawLine( x, 500-y, x+30, 500-y+40 );	
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




