#include <iostream>
#include <algorithm>
#include "point.h"
#include "segment.h"
using namespace std;

int main()
{
  Point p1(1,2);
  Point p2(3,4);
  Segment seg1(Point(1,2),Point(4,0.0));
  Segment seg2(Point(0,0),Point(3,0));
  cout<<seg1.trueDistanceTo(seg2)<<endl;
}