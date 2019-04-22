#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

/*
Class for points
*/
class point
{
public:
	double x;
	double y;
	point (double px = 0, double py = 0){
		x=px;
		y=py;
	}

	//check for equality between 2 objects of class point

	friend bool operator== (const point& p1,const point& p2){
		return (p1.x==p2.x && p1.y==p2.y);
	}

	//check for non-equality between 2 objects of class point

	friend bool operator!= (const point& p1,const point& p2){
		return (!(p1.x==p2.x && p1.y==p2.y));
	}

		//to check for print object of class point to STDOUT

	friend ostream& operator<<(ostream& output,const point& p){
		output<<"("<<p.x<<","<<p.y<<")";
		return output;
	}
};

#endif