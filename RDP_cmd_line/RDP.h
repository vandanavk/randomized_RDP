#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;
class Point{
public:
    double x, y;
    bool visited;
    Point() {
    }
    ~Point() {
    }
    Point(double v1, double v2, bool v) {
	x = v1; y=v2;visited=v;
    }
    double getX() {
	return x;
    }

    double getY() {
	return y;
    }

    bool getVisited() {
	return visited;
    }

    void setVisited() {
	visited = true;
    }

    double operator*(Point rhs)const{
        return (this->x * rhs.y - rhs.x * this->y);
    }
    
    Point operator-(Point rhs)const{
        Point p;
        p.x=fabs(this->x-rhs.x);
        p.y=fabs(this->y-rhs.y);
        return p;
    }
 
    bool operator<(Point rhs)const{
        return ((this->x<rhs.x) && (this->y<rhs.y));
    }
 
    bool operator>(Point rhs)const{
        return ((this->x>rhs.x) && (this->y>rhs.y));
    }
    
    double x2y2()const{
        return sqrt(this->x * this->x + this->y * this->y);
    }
};
