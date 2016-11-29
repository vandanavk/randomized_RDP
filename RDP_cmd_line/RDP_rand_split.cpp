#include "RDP.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <random>
using namespace std;

#define PT_MAX 30

vector<Point> point;
vector<Point> backup;
int c;
double epsilon;

void RDP(vector<Point>& p, int first, int last) {

	double dist =0, cmp = 0, dmax = 0;
	int alpha = 2, index = 0;
	vector<int> J;
	srand(time(NULL));

	for (int i=0;i<alpha;i++)
		J.push_back(rand()%(last-first)+first);
	
	for (int j = 0; j<J.size();j++)
	{
		int it = J[j];
		if (p[it].getVisited() || p[it].getDeleted())
			continue;
		dist = (p[first]-p[last]).x2y2();
		cmp = (fabs(((p[last].getX()-p[first].getX())*(p[first].getY()-p[it].getY())) - ((p[first].getX()-p[it].getX())*(p[last].getY()-p[first].getY()))))/dist;
		c++;
		if (cmp > dmax) {
			index = it;
			dmax = cmp;
		}
	}
	
	if (dmax > epsilon) {
		RDP(p, first, index);
		RDP(p,index, last);
	}
	if (!p[index].getVisited() && !p[index].getDeleted() && dmax < epsilon)
		for (int i=first+1;i<last;i++)
			p[i].setDeleted();
}

void normal_RDP(vector<Point>& p, int first, int last) {

	double dist =0, cmp = 0, dmax = 0;
	int index = 0;

	for (int j = first+1; j<last;j++)
	{
		if (p[j].getVisited()||p[j].getDeleted())
			continue;
		dist = (p[first]-p[last]).x2y2();
		cmp = (fabs(((p[last].getX()-p[first].getX())*(p[first].getY()-p[j].getY())) - ((p[first].getX()-p[j].getX())*(p[last].getY()-p[first].getY()))))/dist;
		c++;
		if (cmp > dmax) {
			index = j;
			dmax = cmp;
		}
	}
	if (dmax > epsilon) {
		normal_RDP(p, first, index);
		normal_RDP(p,index, last);
	}
	if (!p[index].getVisited() && dmax<epsilon)
		for (int i=first+1;i<last;i++)
			p[i].setDeleted();
}
int main()
{
	int start_index=0;
	epsilon = 5;

	srand(time(NULL));
	for (int i=0;i<PT_MAX;i++)
	{
		//point.push_back(Point(rand()%PT_MAX, rand()%PT_MAX, false));
		point.push_back(Point(20+(rand()%(129)), 50+(rand()%(80)), false));
	}
	sort(point.begin(), point.end(), [](const Point& lhs, const Point& rhs){ return lhs.x < rhs.x; });
	backup=point;

	point[start_index].setVisited();
	point[PT_MAX-1].setVisited();
	for (int i=0;i<PT_MAX;i++)
	{
		cout<<"("<<point[i].getX()<<","<<point[i].getY()<<"), ";
	}


	cout<<"\n\nOriginal algorithm\n";
	cout<<"\n\nUsing epsilon "<<epsilon<<"\n";

	point[start_index].setVisited();
	point[PT_MAX-1].setVisited();
	auto start = std::chrono::high_resolution_clock::now();
	normal_RDP(point,start_index, PT_MAX);
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"\n\nTime taken = "<<microseconds<<"\n";
	cout<<"\n\n# of distance calculations with original algorithm = "<<c;
	c=0;
	cout<<"\n\nRandomized algorithm\n";

	backup[0].setVisited();
	backup[start_index].setVisited();
	backup[PT_MAX-1].setVisited();

	cout<<"\n\nUsing epsilon "<<epsilon<<"\n";

	start = std::chrono::high_resolution_clock::now();
	//for (int i=0;i<5;i++)
		RDP(backup,start_index, PT_MAX);
	elapsed = std::chrono::high_resolution_clock::now() - start;
	microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"\n\nTime taken = "<<microseconds<<"\n\n";

	int size_ct = 0;
	for (int i=0;i<point.size();i++)
		if (!point[i].getDeleted()) {
			cout<<"("<<point[i].getX()<<","<<point[i].getY()<<"), ";
			size_ct++;
		}
	cout<<"\n\nAfter normal RDP algorithm: "<<size_ct<<" points\n\n";

	size_ct = 0;	
	for (int i=0;i<backup.size();i++)
		if (!backup[i].getDeleted()) {
			cout<<"("<<backup[i].getX()<<","<<backup[i].getY()<<"), ";
			size_ct++;
		}

	cout<<"\n\nAfter randomized RDP algorithm: "<<size_ct<<" points\n";
	cout<<"\n# of distance calculations with randomized algorithm = "<<c<<"\n";
	return 0;
}
