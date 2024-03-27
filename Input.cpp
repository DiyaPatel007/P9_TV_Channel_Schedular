
#include <bits/stdc++.h>
#define Max_Show 100 
using namespace std;

class Data
{
public:
    int Size;
    int *Priority;
    string *UserName;
    string *ShowName;
    int CalculateRow();
    Data()
    {
        Size = CalculateRow();
        Priority = new int[Size];
        UserName = new string[Size];
        ShowName = new string[Max_Show];
    }
    tuple<int, int, int, int> ConvertTimeSlot(const string &TimeSlot);
};
int Data ::CalculateRow(void)
{
    int count = 0;
    ifstream input;
    string S;
    input.open("TV_P9.csv");
    while (input)
    {
        getline(input, S, '\n');
        count++;
    }
    return (count - 5);
    input.close();
}

tuple<int, int, int, int> Data ::ConvertTimeSlot(const string &TimeSlot)
{
    int minute1, minute2, hour1, hour2;
    sscanf(TimeSlot.c_str(), "%d:%d-%d:%d", &hour1, &minute1, &hour2, &minute2);
    return make_tuple(hour1, minute1, hour2, minute2);
}
int main()
{
    Data D;
    ifstream InputFile;
    InputFile.open("TV_P9.csv");
    string temp1, temp2;
    int i = 0;
    getline(InputFile, temp1, '\n');
    getline(InputFile, temp2, '\n');

    for (int i = 0; i < D.Size; i++)
    {
        InputFile >> D.Priority[i];
        getchar();
        getline(InputFile, D.UserName[i], ',');
    }
    InputFile.close();
    return 0;
}
