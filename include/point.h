#ifndef POINT_H
#define POINT_H


#include <cmath>
#include <iostream>


class CPoint
{
public:
  CPoint(double x = 0.0, double y = 0.0) : x(x), y(y) {}
  CPoint(const CPoint& p) : x(p.x), y(p.y) {}
  static CPoint fromPoolarCoords(const double r, const double phi) { return CPoint(r * cos(phi), r * sin(phi)); }

  double length()        const { return sqrt(pow(x, 2.0) + pow(y, 2.0)); }
  double lengthSquared() const { return pow(x, 2.0) + pow(y, 2.0); }
  double angle()         const { return atan2(y, x); }
  double angleDeg()      const { return 180.0 * atan2(y, x) / M_PI; }
  double dot(const CPoint& p)   const { return x * p.x + y * p.y; }
  double cross(const CPoint& p) const { return x * p.y - y * p.x; }

  CPoint normalized() { return (length() > 0.0) ? *this / length() : *this; }
  CPoint reflected(const CPoint& normal) const { return *this - 2.0 * normal * (normal.dot(*this)); }
  CPoint perpendicular() const { return CPoint(-y, x); }

  friend CPoint operator+ (const CPoint& p1, const CPoint& p2) { return CPoint(p1.x + p2.x, p1.y + p2.y); }
  friend CPoint operator- (const CPoint& p1, const CPoint& p2) { return CPoint(p1.x - p2.x, p1.y - p2.y); }
  friend CPoint operator* (const double f, const CPoint& p)  { return CPoint(f * p.x, f * p.y); }
  friend CPoint operator* (const CPoint& p, const double f)  { return CPoint(f * p.x, f * p.y); }
  friend CPoint operator/ (const CPoint& p, const double f)  { return (f != 0.0) ? CPoint(p.x / f, p.y / f) : CPoint(); }

  CPoint operator- () { return CPoint(-x, -y); }
  CPoint operator+ () { return CPoint( x,  y); }

  CPoint& operator=  (const CPoint& p) { if (this != &p) { x = p.x; y = p.y; } return *this; }
  CPoint& operator+= (const CPoint& p) { x += p.x; y += p.y; return *this; }
  CPoint& operator-= (const CPoint& p) { x -= p.x; y -= p.y; return *this; }

  friend bool operator== (const CPoint& p1, const CPoint& p2) { return (p1.x == p2.x && p1.y == p2.y); }
  friend bool operator!= (const CPoint& p1, const CPoint& p2) { return !(p1 == p2); }
  friend bool operator<  (const CPoint& p1, const CPoint& p2) { return (p1.lengthSquared() < p2.lengthSquared()); }
  friend bool operator<= (const CPoint& p1, const CPoint& p2) { return (p1.lengthSquared() <= p2.lengthSquared()); }
  friend bool operator>  (const CPoint& p1, const CPoint& p2) { return (p1.lengthSquared() > p2.lengthSquared()); }
  friend bool operator>= (const CPoint& p1, const CPoint& p2) { return (p1.lengthSquared() >= p2.lengthSquared()); }
  friend bool operator!  (const CPoint& p1) { return (p1.x == 0.0 && p1.y == 0.0); }

  friend std::ostream& operator<<(std::ostream& out, const CPoint& p)
  { out << "(" << p.x << ", " << p.y << ")"; return out; }

  double x;
  double y;
};


#endif


