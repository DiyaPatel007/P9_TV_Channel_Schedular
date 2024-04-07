#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "Input.cpp"
int main()
{
    Data D;
    D.ReadCSV();
    cout<<BLUE; Print_line('-',80);cout<<RESET;
    cout<<GREEN"=> INPUT FILE"<<RESET<<endl;
    D.DisplayInput();
    return 0;
}