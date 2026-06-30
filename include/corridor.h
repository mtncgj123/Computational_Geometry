#ifndef CORRIDOR_H
#define CORRIDOR_H

#include <vector>

#include "hyperplain.h"

class CCorridor
{
  public:
    CCorridor() {}
    CCorridor(const std::vector<CPoint>& viPointSet)
    {
        CPoint iCenter = (viPointSet[0] + viPointSet[1] + viPointSet[2]) / 3;
        for (size_t i = 0; i < viPointSet.size() - 1; ++i)
        {
            this->addHyperPlain(CHyperPlain(viPointSet[i], viPointSet[i + 1], iCenter));
        }
        this->addHyperPlain(CHyperPlain(viPointSet.back(), viPointSet[0], iCenter));
    }
    void addHyperPlain(const CHyperPlain& iPlain) { m_viHyperPlain.push_back(iPlain); }

    bool isinCorridor(CPoint iPoint)
    {
        for (CHyperPlain iPlain : m_viHyperPlain)
        {
            if (!iPlain.SideCheck(iPoint))
            {
                return false;
            }
        }
        return true;
    }

    void Expand(const double dExpand_distance)
    {
        for (CHyperPlain& iPlain : m_viHyperPlain)
        {
            iPlain.m_iHP_first_point -= iPlain.m_iNormal_vector * dExpand_distance;
            iPlain.m_iHP_last_point -= iPlain.m_iNormal_vector * dExpand_distance;
        }
        for (size_t i = 0; i < m_viHyperPlain.size() - 1; ++i)
        {
            CPoint iIntersectionPoint;
            bool bIsIntersection = CSegment(m_viHyperPlain[i].m_iHP_first_point, m_viHyperPlain[i].m_iHP_last_point)
                                       .IntersectionWith(CSegment(m_viHyperPlain[i + 1].m_iHP_first_point,
                                                                  m_viHyperPlain[i + 1].m_iHP_last_point),
                                                         iIntersectionPoint);
            m_viHyperPlain[i].m_iHP_last_point = iIntersectionPoint;
            m_viHyperPlain[i + 1].m_iHP_first_point = m_viHyperPlain[i].m_iHP_last_point;
        }
        CPoint iIntersectionPoint;
        bool bIsIntersection =
            CSegment(m_viHyperPlain.back().m_iHP_first_point, m_viHyperPlain.back().m_iHP_last_point)
                .IntersectionWith(CSegment(m_viHyperPlain[0].m_iHP_first_point, m_viHyperPlain[0].m_iHP_last_point),
                                  iIntersectionPoint);
        m_viHyperPlain.back().m_iHP_last_point = iIntersectionPoint;
        m_viHyperPlain[0].m_iHP_first_point = m_viHyperPlain.back().m_iHP_last_point;
    }

    std::vector<CHyperPlain> m_viHyperPlain;
};

#endif
