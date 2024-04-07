#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
using namespace std;

bool IsIncluded(tuple<int, int, int, int> Slot, tuple<int, int, int, int> Show)
{
    if (get<0>(Slot) < get<0>(Show) || (get<0>(Slot) == get<0>(Show) && get<1>(Slot) < get<1>(Show)))
    {
        if (get<2>(Slot) > get<2>(Show) || (get<2>(Slot) == get<2>(Show) && get<3>(Slot) > get<3>(Show)))
        {
            return true;
        }
        else
        {
            return false; // Add this line
        }
    }
    else
    {
        return false; // Add this line
    }
}

int Compare(tuple<int, int, int, int> Slot, tuple<int, int, int, int> Show)
{
    if ((get<2>(Slot) < get<2>(Show)) || (get<2>(Slot) == get<2>(Show) && get<3>(Slot) < get<3>(Show)))
        return 1;
    if ((get<0>(Slot) > get<0>(Show)) || (get<0>(Slot) == get<0>(Show) && get<1>(Slot) > get<1>(Show)))
        return -1;
    if (IsIncluded(Slot, Show)) // Corrected this line
        return 0;
}