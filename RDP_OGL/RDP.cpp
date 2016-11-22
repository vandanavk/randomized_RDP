//
//  RDP.cpp
//  RDP_OGL
//
//  Created by Vandana Kannan on 11/12/16.
//  Copyright © 2016 Vandana Kannan. All rights reserved.
//

#include <iostream>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <random>
#include "rdp_ogl.h"
using namespace std;

#ifdef __APPLE__
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif

#define PT_MAX 30

vector<Point> point;
vector<Point> backup;
double epsilon;
int start_index = 0;

void InitGL()
{
	glClearColor(255.0f,255.0f,255.0f,0.0f);//what color to use when the buffer is cleared
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void initialize()
{
	int i = 0;
	
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> disX(0, 149);
	std::uniform_int_distribution<> disY(0, PT_MAX-1);
	for (i =0; i<PT_MAX; i++)
	{
		point.push_back(Point(20+(disX(gen)), 50+(disY(gen)), false));
	}
	sort(point.begin(), point.end(), [](const Point& lhs, const Point& rhs){ return lhs.x < rhs.x; });
	backup=point;
}

void worst_case()
{
	int i = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> disX(0, 149);
	std::uniform_int_distribution<> disY(0, 1);
	for (i =0; i<PT_MAX; i++)
	{
		point.push_back(Point(20+(disX(gen)), 50+((disY(gen))?30:-30), false));
	}
	sort(point.begin(), point.end(), [](const Point& lhs, const Point& rhs){ return lhs.x < rhs.x; });
}

void display()
{
	int i;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0.0, 0.0, 0.0);
	glPointSize(5.0);
	
	//draw two points
	glBegin(GL_POINTS);
	for(i = 0; i < PT_MAX; i++)
	{
			glVertex2i(point[i].x,point[i].y);
	}
	glEnd();
	
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	for (i=0;i+1<PT_MAX;i++)
	{
		{
			glVertex2i(point[i].x,point[i].y);
			glVertex2i(point[i+1].x,point[i+1].y);
		}
	}
	
	glEnd();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void RDP(vector<Point>& p, int first, int last) {
	
	double dist =0, dmax = 0;
	int index = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> disJ(1, last-first);
	
	glutDisplayFunc(display);
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
			glVertex2i(point[first].x,point[first].y);
			glVertex2i(point[last].x,point[last].y);
	
	glEnd();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

	int j = disJ(gen)+first;
	
	if (!p[j].getVisited()) {
		dist = (p[first]-p[last]).x2y2();
		dmax = (fabs(((p[last].getX()-p[first].getX())*(p[first].getY()-p[j].getY())) - ((p[first].getX()-p[j].getX())*(p[last].getY()-p[first].getY()))))/dist;
		index = j;
	}
	
	if (dmax > epsilon) {
		RDP(p,first, index);
		RDP(p,index, last);
	}
	if (!p[index].getVisited() && dmax < epsilon){
		p.erase(p.begin()+index);
	}
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 13: //enter key
			for (int i=0;i<5;i++) {
				point[0].setVisited();
				point[start_index].setVisited();
				point[PT_MAX-1].setVisited();
				RDP(point, start_index, PT_MAX-1);

				glutPostRedisplay ();
			}
			break;
		default:
			break;
	}
}

int main(int argc, char * argv[]) {
	int window;
	
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(1280,1024);
	glutInitWindowPosition(0,0);
	
	window=glutCreateWindow("RDP algorithm");//returns windows creation success or failure
	
	initialize();
	//worst_case();

	InitGL();
	
	glutDisplayFunc(display);
	
	epsilon = 5;
	
	glutKeyboardFunc (keyboard);

	glutMainLoop();

    return 0;
}
