/*
Line drawing using DDA algorithm
Author:Sadeed Ameen PO
Roll No:267
*/
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;
double X1, Y1, X2, Y2;

float round_value(float v)
{
  return floor(v + 0.5);
}
void LineDDA(void)
{
  double dx=(X2-X1);
  double dy=(Y2-Y1);
  double steps;
  float xInc,yInc,x=X1,y=Y1;
  /* Find out whether to increment x or y */
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2d(x,y);
  int i;
  /* For every step, find an intermediate vertex */
  for(i=0;i<steps;i++)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(round_value(x), round_value(y));
    cout<<"x="<<round_value(x);
  }
  glEnd();

  glFlush();
}
void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  // Set fill color
  glColor3f(0.0,0.0,1.0);
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
  glutDisplayFunc(LineDDA);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
//End of program
