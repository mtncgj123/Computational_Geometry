#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include "point.h"

using namespace std;

class CSegment
{
public:
  CSegment(const CPoint& p1 = CPoint(), const CPoint& p2 = CPoint()) {
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

  double dot(const CSegment& seg) const 
  {
    return (last_point - first_point).dot(seg.last_point - seg.first_point);
  }

  CPoint normal() const {
    return (last_point - first_point).perpendicular().normalized();
  }

  CPoint projection(const CPoint& p) const {
    CPoint a = last_point - first_point;
    CPoint b = p - first_point;
    return first_point + a.dot(b) * a / a.lengthSquared();
  }

  CPoint trueProjection(const CPoint& p) const {
    CPoint a = last_point - first_point;
    CPoint b = p - first_point;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return (first_point);
    else if (t > 1.0)
      return (last_point);
    else
      return first_point + a.dot(b) * a / a.lengthSquared();
  }

  CPoint IntersectionWith(const CSegment& segment) const 
  {
    CPoint v1 = last_point - first_point;
    CPoint v2 = segment.last_point - segment.first_point;
    if(abs(v1.cross(v2)) < 1e-3)
    {
      std::cout<<"`Parallel"<<endl;
    }

    double t=(segment.first_point-this->first_point).cross(v2)/(v1.cross(v2));

    return first_point + t*v1;
  }

  double distanceTo(const CPoint& p) const {
    return (p - projection(p)).length();
  }

  double trueDistanceTo(const CSegment& seg)
  {
    CPoint p1=this->first_point;
    CPoint p2=this->last_point;
    CPoint q1=seg.first_point;
    CPoint q2=seg.last_point;
    CPoint s1=p2-p1;
    CPoint s2=q2-q1;
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

  double trueDistanceTo(const CPoint& p) const {
    CPoint a = last_point - first_point;
    CPoint b = p - first_point;
    CPoint c = p - last_point;

    double t = a.dot(b) / a.lengthSquared();

    if (t < 0.0)
      return b.length();
    else if (t > 1.0)
      return c.length();

    CPoint projection = first_point + t * a;
    return (p - projection).length();
  }


  friend std::ostream& operator<<(std::ostream& out, const CSegment& s) {
    out << "p1: " << s.first_point << ", p2: " << s.last_point;
    return out;
  }

  CPoint first_point;
  CPoint last_point;
};

#endif 