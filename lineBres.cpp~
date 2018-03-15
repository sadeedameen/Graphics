#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;
double X1, Y1, X2, Y2;

int round_value(float v)
{
  return floor(v + 0.5);
}
int sign(double num)
{
	int r;
	if(num<0)
		r=-1;
	else 
		r=1;
}
void LineBresen(void)
{
  double dx=abs(X2-X1),X,Y,p;
  double dy=abs(Y2-Y1);
  int s1,s2,change;
  float a,b,p0;
  /* Find out whether to increment x or y */
  s1=sign(X2-X1);
  s2=sign(Y2-Y1);
 if(dy>dx)
 {
 	dx+=dy;
 	dy=dx-dy;
 	dx-=dy;
 	change=1;
 }
 else 
 	change=0;
  p0=2*dy-dx;
  a=2*dy;
  b=2*dy-2*dx;
  	X=X1;
	Y=Y1;

/* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2d(X,Y);
  int i;
  /* For every step, find an intermediate vertex */
  for(i=0;i<dx;i++)
  {
    if(p0<0){
    		if(change=1)
    			Y+=s2;
    		else
    		{
    			X+=s1;
    			p0=p0+a;
    		}
         }
    else{
    		Y+=s2;
    		X+=s1;
    		p=p+b;
    	}
        
    glVertex2d(round_value(X), round_value(Y));
    cout<<"x="<<round_value(X);
  }
  glEnd();

  glFlush();
}
void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}
int main(int argc, char **argv)
{
  cout<<"Enter two end points of the line to be drawn:\n";
  cout<<"\n************************************";
  cout<<"\nEnter Point1( X1 , Y1):\n";
  cin>>X1;
  cin>>Y1;
  cout<<"\n************************************";
  cout<<"\nEnter Point1( X2 , Y2):\n";
  cin>>X2;
  cin>>Y2;
  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("Line Drawing using DDA");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(LineBresen);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}

