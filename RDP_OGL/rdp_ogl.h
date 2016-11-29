//
//  rdp_ogl.h
//  RDP_OGL
//
//  Created by Vandana Kannan on 11/12/16.
//  Copyright © 2016 Vandana Kannan. All rights reserved.
//

#ifndef rdp_ogl_h
#define rdp_ogl_h

class Point{
public:
    double x, y;
    bool visited, deleted;
    Point() {
    }
    ~Point() {
    }
    Point(double v1, double v2, bool v) {
        x = v1; y=v2;visited=v;deleted = false;
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
    
    bool getDeleted() {
        return deleted;
    }
    
    void setDeleted() {
        deleted = true;
    }
    
    double operator*(Point rhs)const{
        return (this->x * rhs.y - rhs.x * this->y);
    }

    /*bool operator< (Point const& rhs)
    {
        return this->x < rhs.x;
    }*/
    
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




#endif /* rdp_ogl_h */
