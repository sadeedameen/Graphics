/*
	TITLE : KRUSKAL MST
	AUTHOR: SADEED AMEEN PO
	ROLL NO : 267

	Input : No. of Nodes
*/
#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include<GL/gl.h>
#define NILL 999

using namespace std;

int nodei, nodej, nodesDrawn = 0, pointsDrawn = 0, radius = 20, mouseX, mouseY, mouseLX, mouseLY, row, col, edgeCount=0, weight, k = 0, slope = 2, nodeCount;
int nodes[10], xc[100], yc[100],xLine[100], yLine[100], color[3], parent[10];
int adjMatrix[10][10],adjMatrixCopy[10][10];
bool wait = false;


int sign(int x)                                           //to determine the sign, used in bressenham's function
{
	return((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void setPixelLine(float x, float y, int col)                      //function to plot the points obtained from bressenham's algorithm
{ 	
	glPointSize(1.5);
	if(col == 0)
		glColor3f(1.0, 0.0, 0.0 );
	else
		glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void circlePlotPoints( int x, int y )                      //Plots the circle points obtained from the mid-point algorithm
{
	glPointSize( 1.0 );
	for ( int i = 0; i < nodesDrawn; i++ )
	{
		if ( color[i] == 0 )
			glColor3f(0.0, 0.0, 0.0);               //assigns rgb values to the color array
		else if ( color[i] == 2 )
			glColor3f( 0, 1, 0 );
		glBegin(GL_LINES);
			glVertex2i(xc[i] + x, yc[i] + y );
			glVertex2i((xc[i] + x), (-y + yc[i] ));
		glEnd();
	}
}

void midPointCircle()
{
	float p, x, y;
	p = 1 - radius;                          // p is the decision parameter
	x = 0;
	y = radius;
	circlePlotPoints(x, y); 
	circlePlotPoints(-x, y);
	circlePlotPoints(-y, x);
	circlePlotPoints(y, x);                 //plots the points (x, y)
	while(x <= y)
	{	
		x = x + 1;
		if(p < 0)
		{
			p = p + 2*x + 1;
		}
		else
		{
			y = y - 1;
			p = p + 2*x + 1 - 2*y;
		}
		circlePlotPoints(x, y);
		circlePlotPoints(-x, y);
		circlePlotPoints(-y, x);
		circlePlotPoints(y, x);
		glFlush();
	}
}

void displayDistance()
{
	for (int i = 0; i < nodesDrawn; i++)
	{
		glRasterPos2i( xc[i], yc[i] );
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, i );
	}
}

void drawString(float x, float y, char *str)
{
	glPointSize(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(x, y);
	for( str; *str != '\0'; str++ )
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *str);
}

void printAdjMatrix()
{
	adjMatrix[row][col] = weight;
	adjMatrix[col][row] = weight;		            
}

void bressenham(int x2, int y2, int x3, int y3, int slope, int col)   //Bressenham's line drawing algorithm
{
	int dx, dy, dx2, dy2, x, y, s1, s2, p;
	if(slope == 2)                                       //if slope is negative, exchange x and y for both endpoints
	{
		int temp = x2;
		x2 = y2;
		y2 = temp;
		temp = x3;
		x3 = y3;
		y3 = temp; 
	}
	dx = abs(x3 - x2);
	dx2 = 2 * dx;
	dy = abs(y3 - y2);
	dy2 = 2 * dy;
	s1 = sign(x3 - x2);               //s1 and s2 denote the sign of dx and dy respectively                
	s2 = sign(y3 - y2);	
	if(dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;	
	}
	p = dy2 - dx;
	x = x2;
	y = y2;
	for(int i = 0; i <= dx; i++)
	{
		if( slope == 1)
			setPixelLine(x, y, col);
		else
			setPixelLine(y, x, col);
		x = x + s1;
		if(p >= 0)
		{
			y = y + s2;
			p = p + 2 * (dy - dx);
		}
		else
			p = p + dy2;
	}
	glFlush();			
}

void getWeight()
{
	if(wait == true)
	{
		cout << "\nEnter the weight : ";
		cin >> weight;	
		edgeCount++;
		wait = false;
	}
}

void drawCircleLine()
{
	for(int i = 0; i+1 < pointsDrawn && pointsDrawn > 1; i+=2)
	{
		if(abs(xLine[i+1] - xLine[i]) > abs(yLine[i+1] - yLine[i]))      //to determine the sign of slope
			slope = 1;
		else
			slope = 2;
		if(pointsDrawn % 2 == 0)
		{                      		// to determine the number of times clicked to draw an edge
			printAdjMatrix();
		}	
		bressenham(xLine[i], yLine[i], xLine[i+1], yLine[i+1], slope, 0);
	}
	midPointCircle();
}


void adjCopyMatrix()
{
	for(int i = 0; i < nodeCount; i++)
		for(int j = 0; j < nodeCount; j++)
			adjMatrixCopy[i][j] = adjMatrix[i][j];
}

int findMin()
{
	int min = NILL;
	for(int i = 0; i < nodeCount; i++)
	{
		for(int j = 0; j < nodeCount; j++)
		{
			if(adjMatrixCopy[i][j] == 0)
				continue;
			else if(adjMatrixCopy[i][j] <= min)		
			{
				if(adjMatrixCopy[i][j] == min && i == nodej && j == nodei)
					continue;
				else
				{
					min = adjMatrix[i][j];
					nodei = i;
					nodej = j;
				}
			}
		}
	}
	adjMatrixCopy[nodei][nodej] = 0;
	adjMatrixCopy[nodej][nodei] = 0;
	return min;
}

int findParent(int a)
{
	while(parent[a] != NILL)
	{
		a = parent[a];
		if(parent[a] != a)
			continue;
		else
			break;
	}
	return a;
}

int findDuplicates(int nodei, int nodej)
{
	int flag = 0;	
	for(int i = 0; i < nodeCount; i++)
	{
		if(nodes[i] == nodei)
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		nodes[k++] = nodei;
	flag = 0;
	for(int i = 0; i < nodeCount; i++)
	{
		if(nodes[i] == nodej)
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		nodes[k++] = nodej;
}

void findCenter(int nodei, int nodej, int weight)
{
	float x, y;
	char ch[5];
	x = (xc[nodei] + xc[nodej])/(2.0);
	y = (yc[nodei] + yc[nodej])/(2.0);
	sprintf(ch, "%d", weight);
	drawString(x+3, y+3, ch);
}

void drawEdge(int nodei, int nodej)
{
	color[nodei] = 2;
	color[nodej] = 2;	
	int slope;
	if(abs(xc[nodej] - xc[nodei]) > abs(yc[nodej] - yc[nodei]))      //to determine the sign of slope
		slope = 1;
	else
		slope = 2;
	bressenham(xc[nodei], yc[nodei], xc[nodej], yc[nodej], slope, 1);
}

void kruskal()
{
	int x = 0, u, v, minimumCost = 0, k = 0, weight[edgeCount];
	adjCopyMatrix();
	while(x < nodeCount - 1) 
	{
		int w = findMin();
		u = nodei; v = nodej;
		u = findParent(u);
		v = findParent(v);		
		if(u != v)
		{
			if(nodei != nodej)
			{
				parent[nodej] = nodei;
				findDuplicates(nodei, nodej);
			}
			weight[k++] = w;
			findCenter(nodei, nodej, w);
			drawEdge(nodei, nodej);
			minimumCost = minimumCost + w;
			x++;
		}
		sleep(1.0);
	}
	cout << "\n";
	for(int i = 0; i < nodeCount; i++)
		cout << nodes[i] << " ";
	cout << "\nThe Weights in order of edges traversed are : ";
	for(int i = 0; i < nodeCount - 1; i++)
		cout << weight[i] << " ";
	cout << "\nMinimum cost : " << minimumCost;
}			

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)              //if a left-click occured
	{
		if(nodesDrawn < nodeCount)                                //if the number of nodes already drawn is less than the max number of nodes
		{
			xc[nodesDrawn] = mouseX = x;                     //draw another node
			yc[nodesDrawn] = mouseY = 500 - y;
			nodesDrawn++;
		}
		else                                               //if the number of nodes already drawn is greater than the max number of nodes         
		{
			cout << endl;
			cout << "\nAdjacency Matrix : \n";
			for(int i = 0; i < nodeCount; i++)                //print the adjacency matrix
			{
				for(int j = 0; j < nodeCount; j++)
					cout << adjMatrix[i][j] << " ";
				cout << endl;
			}
		}
	}
	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)                //if a right-click occured
	{
		int i = 0;
		for(i = 0; i < nodesDrawn; i++)
		{
			int circleParam = ((pow(x - xc[i], 2) + (pow(500 - y - yc[i], 2) - (pow(radius, 2)))));  //calculate the circle equation x2+y2-r2
			if(circleParam < 0)
			{
				if(pointsDrawn % 2 == 0)     //to determine the number of times click occured
					row = i;
				else
					col = i;
				break;
			}	
		}
		if(i != nodesDrawn)
		{
			xLine[pointsDrawn] = mouseLX = xc[i];
			yLine[pointsDrawn] = mouseLY = yc[i];
			pointsDrawn++;
		}
		if(pointsDrawn % 2 == 0)
		{
			wait = true;
			edgeCount++;                       //if wait = true, then the click has occured twice and user inputs the weight
			getWeight();
		}
	}
	drawCircleLine();
}


void keyboardPress(unsigned char key, int x, int y)
{
	cout << "\nTraversal Order : \n";
	switch(key)
	{
		case  'k' : kruskal();                //if 'k' character id pressed, krukal is called
			break;
		default : cout <<"Invalid Key !!!"<< endl;
	}
}
 
void initAdjMatrix()                                   //initialize adjacency matrix
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			adjMatrix[i][j] = 0;
			adjMatrixCopy[i][j] = 0;
		}
		nodes[i] = NILL;	
	}
		
}

void initializeSingleSource()
{
	for( int i=0; i < nodeCount; i++ )                         
	{
		parent[i] = NILL;                       //for all nodes, assign the parent as NULL,
		color[i] = 0;                           //color as white
	}
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("MST - Kruskal");
	glClearColor(0.000, 0.749, 1.000, 0);
	glClear(GL_COLOR_BUFFER_BIT);	
	gluOrtho2D(0, 800, 0, 500);
}

int main(int argc, char *argv[])
{
	cout<<"Enter the number of nodes in the graph : \n";
	cin>>nodeCount;
	initAdjMatrix();
	initializeSingleSource();
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPress); 
	glutDisplayFunc(drawCircleLine);
	glutMainLoop();
	return 0;
}
/*END OF THE PROGRAM*/
