#ifndef SEGMENT_H
#define SEGMENT_H

#include <algorithm>

#include "point.h"

class CSegment
{
    static constexpr double EPSILON = 1e-2;
    static constexpr double EPSILON_ANGLE_DIFF = 1e-1;

  public:
    CSegment(const CPoint& iPoint1 = CPoint(), const CPoint& iPoint2 = CPoint())
    {
        // Swap if not counter-clockwise
        if (iPoint1.cross(iPoint2) > 0.0)
        {
            m_iSeg_first_point = iPoint1;
            m_iSeg_last_point = iPoint2;
        }
        else
        {
            m_iSeg_first_point = iPoint2;
            m_iSeg_last_point = iPoint1;
        }
    }

    double length() const { return (m_iSeg_last_point - m_iSeg_first_point).length(); }

    double lengthSquared() const { return (m_iSeg_last_point - m_iSeg_first_point).lengthSquared(); }

    CPoint normal() const { return (m_iSeg_last_point - m_iSeg_first_point).perpendicular().normalized(); }

    /**
     * @brief 计算点到线段的投影点
     *
     * @param iPoint_p
     * @return CPoint
     */
    CPoint projection(const CPoint& iPoint_p) const
    {
        CPoint iPoint_a = m_iSeg_last_point - m_iSeg_first_point;
        CPoint iPoint_b = iPoint_p - m_iSeg_first_point;
        return m_iSeg_first_point + iPoint_a.dot(iPoint_b) * iPoint_a / iPoint_a.lengthSquared();
    }

    /**
     * @brief 计算点到线段的最近的点
     *
     * @param iPoint_p 点
     * @return CPoint 最近的点
     */
    CPoint trueProjection(const CPoint& iPoint_p) const
    {
        CPoint iPoint_a = m_iSeg_last_point - m_iSeg_first_point;
        CPoint iPoint_b = iPoint_p - m_iSeg_first_point;

        double dProjectLength = iPoint_a.dot(iPoint_b) / iPoint_a.lengthSquared();

        if (dProjectLength < 0.0)
        {
            return (m_iSeg_first_point);
        }
        else if (dProjectLength > 1.0)
        {
            return (m_iSeg_last_point);
        }
        else
        {
            return m_iSeg_first_point + iPoint_a.dot(iPoint_b) * iPoint_a / iPoint_a.lengthSquared();
        }
    }

    /**
     * @brief 计算点到线段的垂直距离
     *
     * @param iPoint_p 点
     * @return double
     */
    double distanceTo(const CPoint& iPoint_p) const { return (iPoint_p - projection(iPoint_p)).length(); }

    /**
     * @brief 判断两条线段是否平行
     *
     * @param iSeg 除自身外的另外一条线段
     * @return true
     * @return false
     */
    bool IsParallel(const CSegment& iSeg) const
    {
        CPoint iDir1 = m_iSeg_last_point - m_iSeg_first_point;
        CPoint iDir2 = iSeg.m_iSeg_last_point - iSeg.m_iSeg_first_point;
        return (fabs(iDir1.cross(iDir2) / iDir1.length() / iDir2.length()) < EPSILON_ANGLE_DIFF);
    }

    /**
     * @brief 计算线段和线段的距离
     *
     * @param iSeg 除自身外的另外一条线段
     * @return double 线段和线段距离
     */
    double trueDistanceTo(const CSegment& iSeg) const
    {
        CPoint p1 = this->m_iSeg_first_point;
        CPoint p2 = this->m_iSeg_last_point;
        CPoint q1 = iSeg.m_iSeg_first_point;
        CPoint q2 = iSeg.m_iSeg_last_point;
        CPoint s1 = p2 - p1;
        CPoint s2 = q2 - q1;
        double dDenominator = (s1.lengthSquared() * s2.lengthSquared() - pow(s1.dot(s2), 2.0));
        double k1 = (s1.dot(s2) * ((p1 - q1).dot(s2)) - s2.lengthSquared() * (p1 - q1).dot(s1)) / dDenominator;
        double k2 = -(s1.dot(s2) * ((p1 - q1).dot(s1)) - s1.lengthSquared() * (p1 - q1).dot(s2)) / dDenominator;
        if ((fabs(dDenominator) > EPSILON) && (k1 >= 0) && (k1 <= 1) && (k2 >= 0) && (k2 <= 1))
        {
            return (p1 + k1 * s1 - q1 - k2 * s2).length();
        }
        else
        {
            return std::min(
                {this->trueDistanceTo(iSeg.m_iSeg_first_point), this->trueDistanceTo(iSeg.m_iSeg_last_point),
                 iSeg.trueDistanceTo(this->m_iSeg_first_point), iSeg.trueDistanceTo(this->m_iSeg_last_point)});
        }
    }

    /**
     * @brief 计算点到线段的实际距离
     * 如果点距离线段左边点近，返回距离左边端点的距离，如果点距离线段右边近，返回距离右边端点的，如果点在线段中间，返回垂直距离
     *
     * @param iPoint_p 某个点
     * @return double 点到线段的实际距离
     */
    double trueDistanceTo(const CPoint& iPoint_p) const
    {
        CPoint iPoint_a = m_iSeg_last_point - m_iSeg_first_point;
        CPoint iPoint_b = iPoint_p - m_iSeg_first_point;
        CPoint iPoint_c = iPoint_p - m_iSeg_last_point;

        double dProjectLength = iPoint_a.dot(iPoint_b) / iPoint_a.lengthSquared();

        if (dProjectLength < 0.0)
        {
            return iPoint_b.length();
        }
        else if (dProjectLength > 1.0)
        {
            return iPoint_c.length();
        }

        CPoint projection = m_iSeg_first_point + dProjectLength * iPoint_a;
        return (iPoint_p - projection).length();
    }

    /**
     * @brief 计算线段与线段的交点
     *
     * @param iSegment 除自身外的另外一个线段
     * @return CPoint 线段与线段的交点
     */
    bool IntersectionWith(const CSegment& iSegment, CPoint& iIntersectionPoint) const
    {
        CPoint iPoint_v1 = m_iSeg_last_point - m_iSeg_first_point;
        CPoint iPoint_v2 = iSegment.m_iSeg_last_point - iSegment.m_iSeg_first_point;
        CPoint iP2_minus_P1 = iSegment.m_iSeg_first_point - this->m_iSeg_first_point;
        double dCross = iPoint_v1.cross(iPoint_v2);
        if (fabs(dCross) < 1e-3)
        {
            std::cout << "Intersection with Parallel!!!" << std::endl;
            return false;
        }
        else
        {
            double dT1 = iP2_minus_P1.cross(iPoint_v2) / (dCross);
            double dT2 = iP2_minus_P1.cross(iPoint_v1) / (dCross);
            if (0 <= dT1 && dT1 <= 1 && 0 <= dT2 && dT2 <= 1)
            {
                iIntersectionPoint = m_iSeg_first_point + dT1 * iPoint_v1;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    /**
     * @brief 判断两条线段是否可以merge,并且返回合并后的线段
     * 两条线段可以merge的条件是 1.共线 2.有交点
     *
     * @param iCandidateSeg 自身之外的其他线段
     * @param iMergedSeg 合并后的线段
     * @return true
     * @return false
     */
    bool Merge(const CSegment& iCandidateSeg, CSegment& iMergedSeg) const
    {
        if ((false == IsParallel(iCandidateSeg)) || (trueDistanceTo(iCandidateSeg) > EPSILON))
        {
            return false;
        }
        else
        {
            CPoint iPoint_dir1 = m_iSeg_last_point - m_iSeg_first_point;
            CPoint iPoint_dir1_start = iCandidateSeg.m_iSeg_first_point - m_iSeg_first_point;
            CPoint iPoint_dir1_end = iCandidateSeg.m_iSeg_last_point - m_iSeg_first_point;
            double dDot1 = iPoint_dir1.dot(iPoint_dir1);
            double dDot1_start = iPoint_dir1.dot(iPoint_dir1_start);
            double dDot1_end = iPoint_dir1.dot(iPoint_dir1_end);

            if ((dDot1 >= dDot1_start) && (dDot1 >= dDot1_end))
            {
                iMergedSeg.m_iSeg_last_point = m_iSeg_last_point;
            }
            else if ((dDot1_start >= dDot1) && (dDot1_start >= dDot1_end))
            {
                iMergedSeg.m_iSeg_last_point = iCandidateSeg.m_iSeg_first_point;
            }
            else
            {
                iMergedSeg.m_iSeg_last_point = iCandidateSeg.m_iSeg_last_point;
            }

            CPoint iPoint_dir2 = -iPoint_dir1;
            CPoint iPoint_dir2_start = iCandidateSeg.m_iSeg_first_point - m_iSeg_last_point;
            CPoint iPoint_dir2_end = iCandidateSeg.m_iSeg_last_point - m_iSeg_last_point;
            double dDot2 = dDot1;
            double dDot2_start = iPoint_dir2.dot(iPoint_dir2_start);
            double dDot2_end = iPoint_dir2.dot(iPoint_dir2_end);

            if ((dDot2 >= dDot2_start) && (dDot2 >= dDot2_end))
            {
                iMergedSeg.m_iSeg_first_point = m_iSeg_first_point;
            }
            else if ((dDot2_start >= dDot2) && (dDot2_start >= dDot2_end))
            {
                iMergedSeg.m_iSeg_first_point = iCandidateSeg.m_iSeg_first_point;
            }
            else
            {
                iMergedSeg.m_iSeg_last_point = iCandidateSeg.m_iSeg_last_point;
            }
            return true;
        }
    }

    CPoint m_iSeg_first_point;
    CPoint m_iSeg_last_point;
};

#endif
