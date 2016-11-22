#include "RDP.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

#define PT_MAX 30

vector<Point> point;
vector<Point> backup;
double epsilon;
int c;

void RDP(vector<Point>& p, int first, int last) {

	double dist =0, cmp = 0, dmax = 0;
	int index = 0;
	for (int j = first+1; j<last;j++)
	{
		if (p[j].getVisited())
			continue;
		cout<<p[j].getX()<<","<<p[j].getY()<<"\n";
		dist = (p[first]-p[last]).x2y2();
		cmp = (fabs(((p[last].getX()-p[first].getX())*(p[first].getY()-p[j].getY())) - ((p[first].getX()-p[j].getX())*(p[last].getY()-p[first].getY()))))/dist;
		c++;
		if (cmp > dmax) {
			//cout<<"finding greatest "<<p[j].getX()<<","<<p[j].getY()<<"\n";
			index = j;
			dmax = cmp;
		}
	}
	if (dmax > epsilon) {
		cout<<"greatest "<<p[index].getX()<<","<<p[index].getY()<<"\n";
		RDP(p,first, index-1);
		RDP(p,index, last);
	}
	if (!p[index].getVisited() && dmax<epsilon)
		p.erase(p.begin()+index);
}

int main()
{
	int start_index=0;

	srand(time(NULL));
	for (int i=0;i<PT_MAX;i++)
	{
		//point.push_back(Point(rand()%PT_MAX, rand()%PT_MAX, false));
		point.push_back(Point(20+(rand()%(129)), 50+(rand()%(80)), false));
	}
	sort(point.begin(), point.end(), [](const Point& lhs, const Point& rhs){ return lhs.x < rhs.x; });
	backup=point;

	epsilon = 5;
	point[start_index].setVisited();
	point[PT_MAX-1].setVisited();
	cout<<"Original algorithm\n";
	cout<<"Before RDP\n\n";
	for (int i=0;i<PT_MAX;i++)
	{
		cout<<"("<<point[i].getX()<<","<<point[i].getY()<<"), ";
	}

	cout<<"\n\nUsing epsilon "<<epsilon<<"\n";

	point[start_index].setVisited();
	point[PT_MAX-1].setVisited();
	auto start = std::chrono::high_resolution_clock::now();
	RDP(point,start_index, PT_MAX);
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"\n\nTime taken = "<<microseconds<<"\n";
	cout<<"\nAfter RDP\n\n";
	for (int i=0;i<point.size();i++)
	{
		cout<<"("<<point[i].getX()<<","<<point[i].getY()<<"), ";
	}
cout<<"\nnormal count= "<<c;
c=0;
	cout<<"\n\nRandomized algorithm\n";

	//start_index = rand()%(1+((PT_MAX/20)+1));
	start_index = rand()%(PT_MAX-1);
	epsilon = fmod(rand(),((PT_MAX/20)+1))+((PT_MAX/20)*2);
	backup[0].setVisited();
	backup[start_index].setVisited();
	backup[PT_MAX-1].setVisited();
	cout<<"Before RDP\n\n";
	for (int i=0;i<PT_MAX;i++)
	{
		cout<<"("<<backup[i].getX()<<","<<backup[i].getY()<<"), ";
	}

	cout<<"\n\nUsing epsilon "<<epsilon<<"\n";

	start = std::chrono::high_resolution_clock::now();
	RDP(backup,start_index, PT_MAX);
	elapsed = std::chrono::high_resolution_clock::now() - start;
	microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"\n\nTime taken = "<<microseconds<<"\n";

	cout<<"\nAfter RDP\n\n";
	for (int i=0;i<backup.size();i++)
	{
		cout<<"("<<backup[i].getX()<<","<<backup[i].getY()<<"), ";
	}

cout<<"\n\n"<<point.size()<<" "<<backup.size();
cout<<"\nrandom count= "<<c;
	return 0;
}
