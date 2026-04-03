#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>

class CPoint
{
  public:
    CPoint(double dX = 0.0, double dY = 0.0) : m_dX(dX), m_dY(dY) {}
    CPoint(const CPoint& iPoint) : m_dX(iPoint.m_dX), m_dY(iPoint.m_dY) {}
    static CPoint fromPoolarCoords(const double dR, const double dPhi)
    {
        return CPoint(dR * cos(dPhi), dR * sin(dPhi));
    }

    double length() const { return sqrt(pow(m_dX, 2.0) + pow(m_dY, 2.0)); }
    double lengthSquared() const { return pow(m_dX, 2.0) + pow(m_dY, 2.0); }
    double angle() const { return atan2(m_dY, m_dX); }
    double angleDeg() const { return 180.0 * atan2(m_dY, m_dX) / M_PI; }
    double dot(const CPoint& iPoint) const { return m_dX * iPoint.m_dX + m_dY * iPoint.m_dY; }
    double cross(const CPoint& iPoint) const { return m_dX * iPoint.m_dY - m_dY * iPoint.m_dX; }

    CPoint normalized() { return (length() > 0.0) ? *this / length() : *this; }
    CPoint reflected(const CPoint& iNormal) const { return *this - 2.0 * iNormal * (iNormal.dot(*this)); }
    CPoint perpendicular() const { return CPoint(-m_dY, m_dX); }

    friend CPoint operator+(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return CPoint(iPoint1.m_dX + iPoint2.m_dX, iPoint1.m_dY + iPoint2.m_dY);
    }
    friend CPoint operator-(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return CPoint(iPoint1.m_dX - iPoint2.m_dX, iPoint1.m_dY - iPoint2.m_dY);
    }
    friend CPoint operator*(const double dF, const CPoint& iPoint)
    {
        return CPoint(dF * iPoint.m_dX, dF * iPoint.m_dY);
    }
    friend CPoint operator*(const CPoint& iPoint, const double dF)
    {
        return CPoint(dF * iPoint.m_dX, dF * iPoint.m_dY);
    }
    friend CPoint operator/(const CPoint& iPoint, const double dF)
    {
        return (dF != 0.0) ? CPoint(iPoint.m_dX / dF, iPoint.m_dY / dF) : CPoint();
    }

    CPoint operator-() { return CPoint(-m_dX, -m_dY); }
    CPoint operator+() { return CPoint(m_dX, m_dY); }

    CPoint& operator=(const CPoint& iPoint)
    {
        if (this != &iPoint)
        {
            m_dX = iPoint.m_dX;
            m_dY = iPoint.m_dY;
        }
        return *this;
    }
    CPoint& operator+=(const CPoint& iPoint)
    {
        m_dX += iPoint.m_dX;
        m_dY += iPoint.m_dY;
        return *this;
    }
    CPoint& operator-=(const CPoint& iPoint)
    {
        m_dX -= iPoint.m_dX;
        m_dY -= iPoint.m_dY;
        return *this;
    }

    friend bool operator==(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return (iPoint1.m_dX == iPoint2.m_dX && iPoint1.m_dY == iPoint2.m_dY);
    }
    friend bool operator!=(const CPoint& iPoint1, const CPoint& iPoint2) { return !(iPoint1 == iPoint2); }
    friend bool operator<(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return (iPoint1.lengthSquared() < iPoint2.lengthSquared());
    }
    friend bool operator<=(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return (iPoint1.lengthSquared() <= iPoint2.lengthSquared());
    }
    friend bool operator>(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return (iPoint1.lengthSquared() > iPoint2.lengthSquared());
    }
    friend bool operator>=(const CPoint& iPoint1, const CPoint& iPoint2)
    {
        return (iPoint1.lengthSquared() >= iPoint2.lengthSquared());
    }
    friend bool operator!(const CPoint& iPoint1) { return (iPoint1.m_dX == 0.0 && iPoint1.m_dY == 0.0); }

    friend std::ostream& operator<<(std::ostream& out, const CPoint& iPoint)
    {
        out << "(" << iPoint.m_dX << ", " << iPoint.m_dY << ")";
        return out;
    }

    double m_dX;
    double m_dY;
};

#endif
