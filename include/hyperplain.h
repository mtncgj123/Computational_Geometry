
#ifndef HYPERPLAIN_H
#define HYPERPLAIN_H

#include <vector>

#include "segment.h"

class CHyperPlain
{
  public:
    CHyperPlain(const CPoint& iPoint1 = CPoint(), const CPoint& iPoint2 = CPoint(),
                const CPoint& iNormalPoint = CPoint())
    {
        m_iHP_first_point = iPoint1;
        m_iHP_last_point = iPoint2;
        m_iNormal_vector = (iNormalPoint - iPoint1) - (iNormalPoint - iPoint1).dot((iPoint2 - iPoint1).normalized()) *
                                                          (iPoint2 - iPoint1).normalized();
        m_iNormal_vector = m_iNormal_vector.normalized();
    }

    CHyperPlain(const CSegment& iSeg, const CPoint& iNormalPoint = CPoint())
    {
        *this = CHyperPlain(iSeg.m_iSeg_first_point, iSeg.m_iSeg_last_point, iNormalPoint);
    }

    bool SideCheck(CPoint& iPoint) { return (iPoint - m_iHP_first_point).dot(m_iNormal_vector) >= 0; }

    CPoint m_iHP_first_point;
    CPoint m_iHP_last_point;
    CPoint m_iNormal_vector;
};

#endif
