#include<iostream>
#include<string>
#include<cstring>
using namespace std;

bool time_matching(string free,string slot)     //function to check whether free time and the slot matches or not.
{
    return free==slot;
}

int main()
{
    cout<<boolalpha<< time_matching("10:30","10:30")<<endl;   
    return 0;
}