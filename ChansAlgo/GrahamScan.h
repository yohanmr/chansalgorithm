#ifndef GRAHAMSCAN
#define GRAHAMSCAN

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>
#include "point.h"

Point p0;
using namespace std;

class GrahamScan{
  private:
    /*
    	Function used while sorting the Points using qsort() inbuilt function in C
    */
    static double distsquare(Point p1, Point p2)
    {
      return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    }
    static int orientation(Point p, Point q, Point r)
    {
    	double orient = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    	if (orient == 0.0) return 0;  // Collinear
    	return (orient > 0)? -1: 1; // CW: -1 or CCW: 1
    }
    static int compare(const void *vp1, const void *vp2)
    {
    	Point *p1 = (Point *)vp1;
    	Point *p2 = (Point *)vp2;
    	int orient = orientation(p0, *p1, *p2);
    	if (orient == 0)
    		return (distsquare(p0, *p2) >= distsquare(p0, *p1))? -1 : 1;
    	return (orient == 1)? -1: 1;
    }
    vector<Point> left(vector<Point>& v,Point p)
    {
    	while(v.size()>1 && orientation(v[v.size()-2],v[v.size()-1],p) != 1)
    		v.pop_back();
    	if(!v.size() || v[v.size()-1] != p)
    		v.push_back(p);
    	return v;
    }


    public:

    /*
    	Graham Scan algorithm to find convex hull from the given set of Points
    	Returns the Hull Points from a vector of Points
    */
    vector<Point> runGrahamScan(vector<Point> &Points)
    {
      	if(Points.size()<=1)
      		return Points;
      	qsort(&Points[0], Points.size(), sizeof(Point), compare);
      	vector<Point> lower_hull;
        for(unsigned int i=0; i<Points.size(); ++i)
      		lower_hull = left(lower_hull,Points[i]);
      	reverse(Points.begin(),Points.end());
      	vector<Point> upper_hull;
        for(unsigned int i=0; i<Points.size(); ++i)
      		upper_hull = left(upper_hull,Points[i]);
        for(unsigned int i=1;i<upper_hull.size();++i)
      		lower_hull.push_back(upper_hull[i]);
      	return lower_hull;
    }

};

#endif
