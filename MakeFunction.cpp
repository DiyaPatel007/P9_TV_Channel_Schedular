#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "Input.cpp"
using namespace std;
int main()
{
    Data D;
    D.MakeFunction();
     cout<<BLUE; Print_line('-',80);cout<<RESET;
    cout<<GREEN<<"=> Free Time And Show Times of the User After Week"<<RESET<<endl;
    D.DisplayInput();
     cout<<BLUE; Print_line('-',80);cout<<RESET;
     cout<<BLUE; Print_line('-',80);cout<<RESET;
    cout<<GREEN<<"=> Recorded Shows Of Week"<<RESET<<endl;
    cout<<BLUE; Print_line('-',80);cout<<RESET;
    cout<<BLUE; Print_line('-',80);cout<<RESET;
    D.DisplayRecord();
    return 0;
}