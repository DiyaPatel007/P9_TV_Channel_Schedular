
#include <bits/stdc++.h>
using namespace std;
char ch1;
class Time{
    int hour1;
    int hour2;
    int minute1;
    int minute2;
    Time(int h1 , int m1, int h2, int m2){
        if(h1<h2 || (h1==h2 && m1<m2))  
        {
            hour1 = h1;
            hour2 = h2;
            minute1 = m1;
            minute2 = m2;
        }
    }
};
class Data
{
public:
    int size;
    int *Priority;
    string *UserName;
    string *ShowName;

    // string TVShows[];

    int CalculateRow(void)
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
    Data()
    {
        size = CalculateRow();
        Priority = new int[size];
        UserName = new string[size];
        ShowName = new string[size];
    }
};

int main()
{
    Data D;
    ifstream InputFile;
    InputFile.open("TV_P9.csv");
    string temp1, temp2;
    int i = 0;
    getline(InputFile, temp1, '\n');
    getline(InputFile, temp2, '\n');

    // while(InputFile && i<D.size)
    // {
    //     while()
    //     InputFile>>D.Priority[i];
    //     getline(InputFile , D.UserName[i] , ',' );
    //     i++;
    // }
    for (int i = 0; i < D.size; i++)
    {
        InputFile >> D.Priority[i];
        InputFile >> ch1;
        getline(InputFile, D.UserName[i], ',');
    }
    InputFile.close();
    return 0;
}
