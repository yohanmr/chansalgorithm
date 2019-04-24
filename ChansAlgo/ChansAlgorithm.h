#ifndef CHANSALGO
#define CHANSALGO

#include "point.h"
#include "GrahamScan.h"
#include "mainwindow.h"
#include "unistd.h"
using namespace std;

GrahamScan GS;
/// Main class to find the convex hull of chunks using Chans Algorithm
class ChansAlgo
{
private:
	///returns square of distance
	double distsquare(Point p1, Point p2)
	{
		return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
	}

	/**
		*Returns orientation of the line joining Points p and q and line joining Points q and r
	*/
	int orientation(Point p, Point q, Point r)
	{
		double orient = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
		if (orient == 0.0) return 0;  // Collinear
		return (orient > 0)? -1: 1; // CW: -1 or CCW: 1
	}


	/**
		*Returns the index of the Point to which the tangent is drawn from Point p.

	*/
	int findtangent(vector<Point> v,Point p)
	{
		int lend=0;
		int rend= v.size();
		int l_before = orientation(p, v[0], v[v.size()-1]);
		int l_after = orientation(p, v[0], v[(lend + 1) % v.size()]);
		// A binary search based approach to find a straight line in between a left and a right turning line
		while (lend < rend)
		{
			int center = ((lend + rend)/2);
			int c_before = orientation(p, v[center], v[(center - 1) % v.size()]);
			int c_side = orientation(p, v[lend], v[center]);
			int c_after = orientation(p, v[center], v[(center + 1) % v.size()]);

			if (c_before != -1 and c_after != -1)
				return center;
			else if ((c_side == 1) and (l_after == -1 or l_before == l_after) or (c_side == -1 and c_before == -1))
				rend = center;
			else
				lend = center + 1 ;
			l_before = -c_after;
			l_after = orientation(p, v[lend], v[(lend + 1) % v.size()]);
		}
		return lend;
	}

	/**
		*Returns the pair of integers representing the Hull # and the Point in that Hull which is the extreme amongst all given Hull Points
	*/
	pair<double,double> extremept(vector<vector<Point> >& hulls)
	{
		int h= 0,p= 0;
		for (int i=0; i<hulls.size(); ++i)
		{
			int min_index=0, min_y = hulls[i][0].y;
			for(int j=1; j< hulls[i].size(); ++j)
			{
				if(hulls[i][j].y < min_y)
				{
					min_y=hulls[i][j].y;
					min_index=j;
				}
			}
			if(hulls[i][min_index].y < hulls[h][p].y)
			{
				h=i;
				p=min_index;
			}
		}
		return make_pair(h,p);
	}

	/**
		*Returns the pair of integers representing the Hull # and the Point in that Hull to which the Point lPoint will be joined
	*/
	pair<double,double> next_hullpt(vector<vector<Point> >& hulls, pair<int,int> lPoint)
	{
		Point p = hulls[lPoint.first][lPoint.second];
		pair<int,int> next = make_pair(lPoint.first, (lPoint.second + 1) % hulls[lPoint.first].size());
		for (int h=0; h< hulls.size(); h++)
		{
			if(h != lPoint.first){
				int s= findtangent(hulls[h],p);
				Point q= hulls[next.first][next.second];
				Point r= hulls[h][s];
				int t= orientation(p,q,r);
				if( t== -1 || (t==0) && distsquare(p,r)>distsquare(p,q))
					next = make_pair(h,s);
			}
		}
		return next;
	}

	/**
		*Constraint to find the outermost boundary of the Points by checking if the Points lie to the left otherwise adding the given Point p
		*Returns the Hull Points
	*/
	vector<Point> left(vector<Point>& v,Point p)
	{
		while(v.size()>1 && orientation(v[v.size()-2],v[v.size()-1],p) != 1)
			v.pop_back();
		if(!v.size() || v[v.size()-1] != p)
			v.push_back(p);
		return v;
	}



	/**
		*Main Implementation of Chan's Algorithm to compute Convex Hull
	*/
public:
	void chans(vector<Point> v, MainWindow *w)
	{
		for(int t=0; t< v.size(); ++t)
		{
			for(int m=1; m< (1<<(1<<t)); ++m)
			{
				w->clearLines();
				vector<vector<Point> > hulls;
				for(int i=0;i<v.size();i=i+m)
				{
					vector<Point> chunk;
					if(v.begin()+i+m <= v.end())
						chunk.assign(v.begin()+i,v.begin()+i+m);
					else
						chunk.assign(v.begin()+i,v.end());
					hulls.push_back(GS.runGrahamScan(chunk));
				}
				cout<<"\nM (Chunk Size): "<<m<<"\n";
				for(int i=0;i<hulls.size();++i)
				{
					cout<<"Convex Hull for Hull #"<<i+1<<endl;
					for(int j=0; j<hulls[i].size();++j)
					{
						cout<<hulls[i][j]<<" ";

					}
//					w->drawLines(hulls[i]);
//                    if(hulls[i].size() != 1)
//					sleep(1);
					cout<<"\n";
				}
				vector<pair<int,int> > hull;
				hull.push_back(extremept(hulls));
				for(int i=0; i<m; ++i)
				{
					pair<int,int> p= next_hullpt(hulls,hull[hull.size()-1]);
					vector<Point> output;
					if(p==hull[0])
					{
						for(int j=0; j<hull.size();++j)
						{
							output.push_back(hulls[hull[j].first][hull[j].second]);
						}
												w->clearLines();
                        w->drawLines(output);
                        return;
					}
					hull.push_back(p);
				}
			}
		}
	}
};

#endif

// int main()
// {
// 	int number=0;
// 	double x=0,y=0;
// 	cin>>number;
// 	Point Points[number];
// 	for(int i=0;i<number;++i){
// 		cin>>x>>y;
// 		Points[i].x=x;
// 		Points[i].y=y;
// 	}
// 	vector<Point> v;
// 	for (int i=0;i< number; i++)
// 	v.push_back(Points[i]);
// 	vector<Point> output = chans(v);
// 	cout<<"\n***************** CONVEX HULL **********************\n";
// 	for(int i=0; i< output.size(); ++i)
// 		cout<<output[i]<<" ";
// 	cout<<"\n";
// 	return 0;
// }
