#ifndef FITTING_H
#define FITTING_H

#include <eigen3/Eigen/Eigen>

#include "circle.h"
#include "point.h"
#include "segment.h"

CSegment fitSegment(const std::vector<CPoint> &point_set)
{

    int N = point_set.size();
    assert(N >= 2);

    Eigen::MatrixXd input = Eigen::MatrixXd::Zero(N, 2);  // [x_i, y_i]
    Eigen::MatrixXd output = Eigen::MatrixXd::Ones(N, 1); // [-C]
    Eigen::MatrixXd params = Eigen::MatrixXd::Zero(2, 1); // [A ; B]

    for (int i = 0; i < N; ++i)
    {
        input(i, 0) = point_set[i].x;
        input(i, 1) = point_set[i].y;
    }

    params = input.colPivHouseholderQr().solve(output);

    double A, B, C;
    A = params(0);
    B = params(1);
    C = -1.0;

    // Find end points
    CPoint p1 = point_set[0];
    CPoint p2 = point_set.back();
    CSegment iSegment;

    double D = (A * A + B * B);

    // Project end points on the line
    if (D > 0.0)
    {
        CPoint projected_p1, projected_p2;

        projected_p1.x = (B * B * p1.x - A * B * p1.y - A * C) / D;
        projected_p1.y = (-A * B * p1.x + A * A * p1.y - B * C) / D;

        projected_p2.x = (B * B * p2.x - A * B * p2.y - A * C) / D;
        projected_p2.y = (-A * B * p2.x + A * A * p2.y - B * C) / D;

        iSegment.first_point = projected_p1;
        iSegment.last_point = projected_p2;
    }

    return iSegment;
}

/*
 * Returns a total best fit approximation of
 * a circle based on given point set. The equation
 * used for fitting is given by
 *   a1 * x + a2 * y + a3 = -(x^2 + y^2)
 * where parameters a1, a2, a3 are obtained from
 * circle equation
 *   (x-x0)^2 + (y-y0)^2 = r^2.
 */
CCircle fitCircle(const std::vector<CPoint> &point_set)
{
    int N = point_set.size();
    assert(N >= 3);

    Eigen::MatrixXd input = Eigen::MatrixXd::Zero(N, 3);  // [x_i, y_i, 1]
    Eigen::MatrixXd output = Eigen::MatrixXd::Ones(N, 1); // [-(x_i^2 + y_i^2)]
    Eigen::MatrixXd params = Eigen::MatrixXd::Zero(2, 1); // [a_1 ; a_2 ; a_3]

    int i = 0;
    for (const CPoint &point : point_set)
    {
        input(i, 0) = point.x;
        input(i, 1) = point.y;
        input(i, 2) = 1.0;

        output(i) = -(pow(point.x, 2) + pow(point.y, 2));
        i++;
    }

    // Find a_1, a_2 and a_3 coefficients from linear regression
    params = input.colPivHouseholderQr().solve(output);

    CPoint center(-params(0) / 2.0, -params(1) / 2.0);
    double radius = sqrt((params(0) * params(0) + params(1) * params(1)) / 4.0 - params(2));

    return CCircle(center, radius);
}

#endif
