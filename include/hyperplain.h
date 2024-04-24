
#ifndef HYPERPLAIN_H
#define HYPERPLAIN_H

#include <vector>
#include "segment.h"

class CHyperPlain
{
public:
  CHyperPlain(const CPoint &p1 = CPoint(), const CPoint &p2 = CPoint(), const CPoint &n_CPoint = CPoint())
  {
    first_point = p1;
    last_point = p2;
    normal_vector = (n_CPoint - p1) - (n_CPoint - p1).dot((p2 - p1).normalized()) * (p2 - p1).normalized();
    normal_vector = normal_vector.normalized();
  }

  CHyperPlain(const CSegment& seg, const CPoint &n_CPoint = CPoint())
  {
    *this=CHyperPlain(seg.first_point, seg.last_point, n_CPoint);
  }

  bool SideCheck(const CPoint &p)
  {
    return (p - first_point).dot(normal_vector) >= 0;
  }

  CPoint first_point;
  CPoint last_point;
  CPoint normal_vector;
};

#endif