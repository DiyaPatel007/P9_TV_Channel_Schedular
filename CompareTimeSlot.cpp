#include <bits/stdc++.h>
using namespace std;

bool CompareShowAndFreeTime(tuple<int, int, int, int> Free, tuple<int, int, int, int> Show)
{ 
    if ((get<0>(Free) <= get<0>(Show) || (get<0>(Free) == get<0>(Show)) && get<1>(Free) <= get<1>(Show)) && (get<2>(Free) >= get<2>(Show) || (get<2>(Free) == get<2>(Show)) && get<3>(Free) <= get<3>(Show))){
        return true;
    }
    else{
        return false;
    }
}

// bool CompareShowTime(tuple<int, int, int, int> Show1, tuple<int, int, int, int> Show2)
// {
//     if (get<0>(Show1) == get<0>(Show2) && get<1>(Show1) >= get<1>(Show2) && get<2>(Show1) == get<2>(Show2) && get<3>(Show1) == get<3>(Show2))
//     {
//         return 0;
//     }

// }
