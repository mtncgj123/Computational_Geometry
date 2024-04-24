
#ifndef CORRIDOR_H
#define CORRIDOR_H

#include <vector>
#include "hyperplain.h"
#include "circle.h"

using namespace std;

class CCorridor
{
public:
    CCorridor()
    {
    }
    CCorridor(std::vector<CPoint> vPointSet)
    {
        CPoint iCenter=(vPointSet[0]+vPointSet[1]+vPointSet[2])/3;
        for(int i=0; i<(int)vPointSet.size()-1; i++)
        {
            this->addHyperPlain(CHyperPlain(vPointSet[i],vPointSet[i+1],iCenter));
        }
        this->addHyperPlain(CHyperPlain(vPointSet.back(),vPointSet[0],iCenter));

    }
    void addHyperPlain(CHyperPlain plain)
    {
        vHyperPlain.push_back(plain);
    }

    bool isinCorridor(CPoint p)
    {
        for (CHyperPlain plain : vHyperPlain)
        {
            if (!plain.SideCheck(p))
            {
                return false;
            }
        }
        return true;
    }

    void Expand(double expand_distance)
    {
        for (CHyperPlain &plain : vHyperPlain)
        {
            plain.first_point -= plain.normal_vector * expand_distance;
            plain.last_point -= plain.normal_vector * expand_distance;
        }
        for (int i = 0; i < (int)vHyperPlain.size() - 1; i++)
        {
            vHyperPlain[i].last_point = CSegment(vHyperPlain[i].first_point, vHyperPlain[i].last_point).IntersectionWith(CSegment(vHyperPlain[i + 1].first_point, vHyperPlain[i + 1].last_point));
            vHyperPlain[i + 1].first_point = vHyperPlain[i].last_point;
        }
        vHyperPlain.back().last_point = CSegment(vHyperPlain.back().first_point, vHyperPlain.back().last_point).IntersectionWith(CSegment(vHyperPlain[0].first_point, vHyperPlain[0].last_point));
        vHyperPlain[0].first_point = vHyperPlain.back().last_point;
    }

    std::vector<CHyperPlain> vHyperPlain;
};

#endif