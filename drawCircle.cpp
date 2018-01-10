#include <GL/glut.h>
#include <iostream>

using namespace std;
#include<iostream>
#include <list>
 
using namespace std;
 
// This class represents a directed graph using
// adjacency list representation
struct node{
	int x;
	int y;
}
class Graph
{
    int V;    // No. of vertices
 
    // Pointer to an array containing adjacency
    // lists
    list<int> *adj;   
public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int v, int w); 
 
    // prints BFS traversal from a given source s
    void BFS(int s);  
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited, 
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

 Graph g(7);
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
}
void drawLine( int xStart, int yStart, int xEnd, int yEnd )
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
			drawLine(x+20,500-y, x+40,y+40);
			count++;
			if (count<7)
			g.addEdge(0, count);
			
			if (count>7) g.BFS(0);
			
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




