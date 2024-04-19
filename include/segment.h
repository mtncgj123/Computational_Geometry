
#pragma once

#include <vector>
// #include <algorithm>
#include "point.h"

using namespace std;

class Segment
{
public:
  Segment(const Point& p1 = Point(), const Point& p2 = Point()) {
    // Swap if not counter-clockwise
    if (p1.cross(p2) > 0.0)
      first_point = p1, last_point = p2;
    else
      first_point = p2, last_point = p1;
  }

  double length() const {
    return (last_point - first_point).length();
  }

  double lengthSquared() const {
    return (last_point - first_point).lengthSquared();
  }

  Point normal() const {
    return (last_point - first_point).perpendicular().normalized();
  }

  Point projection(const Point& p) const {
    Point a = last_point - first_point;
    Point b = p - first_point;
    return first_point + a.dot(b) * a / a.lengthSquared();
  }

  Point trueProjection(const Point& p) const {
    Point a = last_point - first_point;
    Point b = p - first_point;
    Point c = p - last_point;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return (first_point);
    else if (t > 1.0)
      return (last_point);
    else
      return first_point + a.dot(b) * a / a.lengthSquared();
  }

  double distanceTo(const Point& p) const {
    return (p - projection(p)).length();
  }

  double trueDistanceTo(const Segment& seg)
  {
    Point p1=this->first_point;
    Point p2=this->last_point;
    Point q1=seg.first_point;
    Point q2=seg.last_point;
    Point s1=p2-p1;
    Point s2=q2-q1;
    double k1=(s1.dot(s2)*((p1-q1).dot(s2))-s2.lengthSquared()*(p1-q1).dot(s1))/(s1.lengthSquared()*s2.lengthSquared()-pow(s1.dot(s2),2.0));
    double k2=-(s1.dot(s2)*((p1-q1).dot(s1))-s1.lengthSquared()*(p1-q1).dot(s2))/(s1.lengthSquared()*s2.lengthSquared()-pow(s1.dot(s2),2.0));
    if(k1>=0&&k1<=1&&k2>=0&&k2<=1)
    {
        return (p1+k1*s1-q1-k2*s2).length();
    }
    else
    {
        return min({this->trueDistanceTo(seg.first_point),this->trueDistanceTo(seg.last_point),seg.trueDistanceTo(this->first_point),seg.trueDistanceTo(this->last_point)});
    }
  }

  double trueDistanceTo(const Point& p) const {
    Point a = last_point - first_point;
    Point b = p - first_point;
    Point c = p - last_point;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return b.length();
    else if (t > 1.0)
      return c.length();

    Point projection = first_point + t * a;
    return (p - projection).length();
  }


  friend std::ostream& operator<<(std::ostream& out, const Segment& s) {
    out << "p1: " << s.first_point << ", p2: " << s.last_point;
    return out;
  }

  Point first_point;
  Point last_point;
};

