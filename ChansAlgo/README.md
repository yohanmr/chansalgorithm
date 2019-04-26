# Computing convex hull using Chan's Algorithm
Computational Geometry Project. <br>
This is a dynamic demo of Chan's Algorithm, an optimal, output-sensitive algorithm for computing the convex hull of a point set in O(nlogh) time.<br>
Where n is the number of input points and h is the number of output hull points <br>

## Step 1
Given a of m points, we find the convex hull of each group with an O(nlogn) algorithm.<br>
In this demo we use Graham Scan. <br>
Because each group has size m we can convex hull each group in O(mlogm). There are O(n/m) groups. <br>

## Step 2
We then use Gift wrapping, an O(nh) algorithm on the small convex hulls. <br>

To use gift wrapping on convex hulls rather than points we can perform a binary search to determine the tangent between an extreme point and a convex hull. A binary search on a small convex hull takes O(logm). <br>

We can compute tangents for all O(n/m) groups in O(n/m * logm) time. We use the tangent with the largest angle. <br>

By doing this we get one edge of the overall convex hull. We must do this for all h hull points. Assuming that m < h so this step is O(nlogh) like the last step. <br>
## Step 3 - Finding m
We want to increase m until it equals h. If we increase m too slowly our gift wrapping time overall will surpass O(nlogh).<br>

On the other hand, if we increase m too quickly some gift wrapping iteration will take much more than O(nlogh) on its own. <br>

To solve this problem we can utilize a double exponential. We let m = 2^2^t where t is the current iteration number. <br>

We throw away the work we do in each attempt at finding an m equal to h. Because iterations form a geometric series the total work is still O(nlogh). <br>



# Results
We have given an implementation of the Chan's Algorithm for finding Convex Hull .<br>
We randomly generated points and ran the algorithm on the points to find the convex hull.


| Number of Points | Run Time - Total CPU time(s) |
|:-----:|:-----:|
| 2 | ~0.005 |
| 10 | ~0.005 |
| 50 | 0.011 |
| 100 | 0.023 |
| 500 | 0.110 |
| 1,000 | 0.180 |
| 5,000 | 2.500 |
| 10,000 | 13.400 |
| 20,000 | 61.170 |

![Graham Scan Time Complexity](graham.jpeg "Graham Scan Time Complexity")

![Chan's algo Time Complexity](chan.jpeg "Chan's algo Time Complexity")

<br>
## Input
![Input Image](linesInput.png "Input through Qt GUI")

<br>
## Output
![Output Image](linesOutput.png "Output displyed using matplotlib")

<br>
<br>


## Instructions for running the code:
+ Install Qt5 for gui:
+ Install matplotlib for displaying results:
+ compile run.cpp
+ run code:
bash execute.sh
