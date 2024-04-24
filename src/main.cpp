#include <iostream>
#include <algorithm>
#include "point.h"
#include <eigen3/Eigen/Eigen>
#include "segment.h"
#include "hyperplain.h"
#include "corridor.h"
#include "circle.h"
#include "fitting.h"
using namespace std;
int main()
{
  // Point p1(1,2);
  // Point p2(3,4);
  // Segment seg1(Point(1,2),Point(4,0.0));
  // Segment seg2(Point(0,0),Point(3,0));
  // cout<<seg1.trueDistanceTo(seg2)<<endl;

  /*Intersection check*/
  // srand((unsigned)time(NULL));
  // double error_sum = 0;
  // for (int i = 0; i < 10000; i++)
  // {

  //   Eigen::Vector4d vec1 = Eigen::Vector4d::Random();
  //   Eigen::Vector4d vec2 = Eigen::Vector4d::Random();
  //   vec1 = (vec1.array() * 10).matrix();
  //   vec2 = (vec2.array() * 10).matrix();
  //   CSegment seg1(CPoint(vec1(0), vec1(1)), CPoint(vec1(2), vec1(3)));
  //   CSegment seg2(CPoint(vec2(0), vec2(1)), CPoint(vec2(2), vec2(3)));
  //   CPoint Intersection = seg1.IntersectionWith(seg2);
  //   error_sum += abs((Intersection - seg1.first_point).cross(Intersection - seg1.last_point));
  //   error_sum += abs((Intersection - seg2.first_point).cross(Intersection - seg2.last_point));
  // }
  // cout << "error_sum: " << error_sum << endl;

  /*Corridor check*/
  // std::vector<CPoint> vPoint;
  // vPoint.push_back(CPoint(-1,0));
  // vPoint.push_back(CPoint(0,1));
  // vPoint.push_back(CPoint(1,0));
  // CCorridor ICorridor(vPoint);
  // ICorridor.Expand(1);
  // for(CHyperPlain& iPlan:ICorridor.vHyperPlain)
  // {
  //   cout<<"Plan "<<iPlan.first_point<<" "<<iPlan.last_point<<endl;
  // }

  /*CircleFitting check*/
  srand((unsigned)time(NULL));
  double error_sum = 0;
  std::vector<CPoint> point_set;
  for (int i = 0; i < 1; i++)
  {

    Eigen::Vector3d vec = Eigen::Vector3d::Random();
    vec = (vec.array() * 10).matrix();
    printf("circle x=%lf, y=%lf, r=%lf \n", vec[0], vec[1], vec[2]);
    for (int j = 0; j < 50; j++)
    {
      Eigen::Vector3d vec2 = Eigen::Vector3d::Random();

      point_set.push_back(CPoint(vec[2] * cos(vec2[2]) + vec[0]+vec2[0]*0.8, vec[2] * sin(vec2[2]) + vec[1]+vec2[1]*0.8));
    }
  }

  CCircle fittingCircle = fitCircle(point_set);
  printf("fitting circle x=%lf, y=%lf, r=%lf \n", fittingCircle.center.x, fittingCircle.center.y, fittingCircle.radius);
}