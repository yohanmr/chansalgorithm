#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

///A class for points
class Point
{
public:
	double x;
	double y;
	Point (double px = 0, double py = 0){
		x=px;
		y=py;
	}

	///check for equality between 2 objects of class Point

	friend bool operator== (const Point& p1,const Point& p2){
		return (p1.x==p2.x && p1.y==p2.y);
	}

	///check for non-equality between 2 objects of class Point

	friend bool operator!= (const Point& p1,const Point& p2){
		return (!(p1.x==p2.x && p1.y==p2.y));
	}

	///to check for print object of class Point to STDOUT

	friend ostream& operator<<(ostream& output,const Point& p){
		output<<"("<<p.x<<","<<p.y<<")";
		return output;
	}
};

#endif
