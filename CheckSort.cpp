#include <bits/stdc++.h>
#include "Input.cpp"

using namespace std;
int main()
{
    Data D_New;
    D_New.ReadCSV();
    D_New.SortData();
    
    Data D;
    D.ReadSorted();
    for (int i = 0; i < D.Size; i++)
    {
        cout << "IndexNumber: " << D.IndexNumber[i] << endl;
        cout << "Member Name: " << D.UserName[i] << endl;
        cout << "Slot Time : " << endl;
        for (int j = 0; j < D.SlotTime[i].size(); j++)
        {
            cout << "Day " << j + 1 << endl;
            for (int k = 0; k < D.SlotTime[i][j].size(); k++)
            {
                cout << "Slot " << k + 1 << " : " << setw(2) << get<0>(D.SlotTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<1>(D.SlotTime[i][j][k]) << " - " << setw(2) << get<2>(D.SlotTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<3>(D.SlotTime[i][j][k]) << endl;
            }
        }
        for(int j = 0 ; j<D.DaywiseFreeTime[i].size(); j++){
            cout<<"Day "<<j+1<<" : "<<D.DaywiseFreeTime[i][j]<<endl;
        }
        cout << endl;
        cout << "Free min = " << D.ans1[i] << endl;
        cout << endl;
        cout << "Show Name:" << endl;
        for (int j = 0; j < D.ShowName[i].size(); j++)
        {
            cout << "Show " << j + 1 << " : " << D.ShowName[i][j] << endl;
        }
        cout << endl;
        cout << "Show Time: " << endl;
        for(int j = 0 ; j<D.DaywiseShowTime[i].size(); j++){
            cout<<"Day "<<j+1<<" : " <<D.DaywiseShowTime[i][j]<<endl;
        }
        for (int j = 0; j < D.ShowTime[i].size(); j++)
        {
            cout << "Day " << j + 1 << endl;
            for (int k = 0; k < D.ShowTime[i][j].size(); k++)
            {
                cout << "Slot " << k + 1 << " : " << setw(2) << get<0>(D.ShowTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<1>(D.ShowTime[i][j][k]) << " - " << setw(2) << get<2>(D.ShowTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<3>(D.ShowTime[i][j][k]) << endl;
            }
        }
        cout << endl;
        cout << "Show Time min = " << D.ans2[i] << endl;
        cout << endl;
    }
    return 0;
}
