#include <bits/stdc++.h>
using namespace std;

bool CompareShowAndFreeTime(tuple<int, int, int, int> Free, tuple<int, int, int, int> Show)
{
    if (get<0>(Free) < get<0>(Show) || (get<0>(Free) == get<0>(Show) && get<1>(Free) <= get<1>(Show)))
    {
        if (get<2>(Free) > get<2>(Show) || (get<2>(Free) == get<2>(Show) && get<3>(Free)+15 >= get<3>(Show)))
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

