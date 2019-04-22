#include "point.h"
using namespace std;

point p0;

double distsquare(point p1, point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

/*
	Returns orientation of the line joining points p and q and line joining points q and r
*/
int orientation(point p, point q, point r)
{
	double orient = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (orient == 0.0) return 0;  // Collinear
	return (orient > 0)? -1: 1; // CW: -1 or CCW: 1
}

/*
	Function used while sorting the points using qsort() inbuilt function in C
*/
int compare(const void *vp1, const void *vp2)
{
	point *p1 = (point *)vp1;
	point *p2 = (point *)vp2;
	int orient = orientation(p0, *p1, *p2);
	if (orient == 0)
		return (distsquare(p0, *p2) >= distsquare(p0, *p1))? -1 : 1;
	return (orient == 1)? -1: 1;
}

/*
	Returns the index of the point to which the tangent is drawn from point p.

*/
int findtangent(vector<point> v,point p)
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

/*
	Returns the pair of integers representing the Hull # and the point in that Hull which is the extreme amongst all given Hull Points
*/
pair<double,double> extremept(vector<vector<point> >& hulls)
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

/*
	Returns the pair of integers representing the Hull # and the point in that Hull to which the point lpoint will be joined
*/
pair<double,double> next_hullpt(vector<vector<point> >& hulls, pair<int,int> lpoint)
{
	point p = hulls[lpoint.first][lpoint.second];
	pair<int,int> next = make_pair(lpoint.first, (lpoint.second + 1) % hulls[lpoint.first].size());
	for (int h=0; h< hulls.size(); h++)
	{
		if(h != lpoint.first){
			int s= findtangent(hulls[h],p);
			point q= hulls[next.first][next.second];
			point r= hulls[h][s];
			int t= orientation(p,q,r);
			if( t== -1 || (t==0) && distsquare(p,r)>distsquare(p,q))
				next = make_pair(h,s);
		}
	}
	return next;
}

/*
	Constraint to find the outermost boundary of the points by checking if the points lie to the left otherwise adding the given point p
	Returns the Hull Points
*/
vector<point> left(vector<point>& v,point p)
{
	while(v.size()>1 && orientation(v[v.size()-2],v[v.size()-1],p) != 1)
		v.pop_back();
	if(!v.size() || v[v.size()-1] != p)
		v.push_back(p);
	return v;
}

/*
	Graham Scan algorithm to find convex hull from the given set of points
	Returns the Hull Points from a vector of points
*/
vector<point> GrahamScan(vector<point>& points)
{
	if(points.size()<=1)
		return points;
	qsort(&points[0], points.size(), sizeof(point), compare);
	vector<point> lower_hull;
	for(int i=0; i<points.size(); ++i)
		lower_hull = left(lower_hull,points[i]);
	reverse(points.begin(),points.end());
	vector<point> upper_hull;
	for(int i=0; i<points.size(); ++i)
		upper_hull = left(upper_hull,points[i]);
	for(int i=1;i<upper_hull.size();++i)
		lower_hull.push_back(upper_hull[i]);
	return lower_hull;
}

/*
	Implementation of Chan's Algorithm to compute Convex Hull
*/
vector<point> chansalgorithm(vector<point> v)
{
	for(int t=0; t< v.size(); ++t)
	{
		for(int m=1; m< (1<<(1<<t)); ++m)
		{
			vector<vector<point> > hulls;
			for(int i=0;i<v.size();i=i+m)
			{
				vector<point> chunk;
				if(v.begin()+i+m <= v.end())
					chunk.assign(v.begin()+i,v.begin()+i+m);
				else
					chunk.assign(v.begin()+i,v.end());
				hulls.push_back(GrahamScan(chunk));
			}
			cout<<"\nM (Chunk Size): "<<m<<"\n";
			for(int i=0;i<hulls.size();++i)
			{
				cout<<"Convex Hull for Hull #"<<i+1<<endl;
				for(int j=0; j<hulls[i].size();++j)
					cout<<hulls[i][j]<<" ";
				cout<<"\n";
			}
			vector<pair<int,int> > hull;
			hull.push_back(extremept(hulls));
			for(int i=0; i<m; ++i)
			{
				pair<int,int> p= next_hullpt(hulls,hull[hull.size()-1]);
				vector<point> output;
				if(p==hull[0])
				{
					for(int j=0; j<hull.size();++j)
					{
						output.push_back(hulls[hull[j].first][hull[j].second]);
					}
					return output;
				}
				hull.push_back(p);
			}
		}
	}
}

int main()
{
	int number=0;
	double x=0,y=0;
	cin>>number;
	point points[number];
	for(int i=0;i<number;++i){
		cin>>x>>y;
		points[i].x=x;
		points[i].y=y;
	}
	vector<point> v;
	for (int i=0;i< number; i++)
	v.push_back(points[i]);
	vector<point> output = chansalgorithm(v);
	cout<<"\n***************** CONVEX HULL **********************\n";
	for(int i=0; i< output.size(); ++i)
		cout<<output[i]<<" ";
	cout<<"\n";
	return 0;
}
