#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "segment.h"

// typedef CPoint Point;
// typedef CSegment Segment;

class CCircle
{
public:
  CCircle(const CPoint& p = CPoint(), const double r = 0.0) : center(p), radius(r) { }


  double distanceTo(const CPoint& p) { return (p - center).length() - radius; }

  friend std::ostream& operator<<(std::ostream& out, const CCircle& c)
  { out << "C: " << c.center << ", R: " << c.radius; return out; }

  CPoint center;
  double radius;
};

#endif