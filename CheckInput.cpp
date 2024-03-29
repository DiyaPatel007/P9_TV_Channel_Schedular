#include <bits/stdc++.h>
#include"Input.cpp"
int main()
{
    Data D;
    D.ReadCSV();
    for (int i = 0; i < D.Size; i++)
    {
        cout << "Priority: " << D.Priority[i] << endl;
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
        cout << endl;
        cout << "Show Name:" << endl;
        for (int j = 0; j < D.ShowName[i].size(); j++)
        {
            cout << "Show " << j + 1 << " : " << D.ShowName[i][j] << endl;
        }
        cout << endl;
        cout << "Show Time: " << endl;
        for (int j = 0; j < D.ShowTime[i].size(); j++)
        {
            cout << "Day " << j + 1 << endl;
            for (int k = 0; k < D.ShowTime[i][j].size(); k++)
            {
                cout << "Slot " << k + 1 << " : " << setw(2) << get<0>(D.ShowTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<1>(D.ShowTime[i][j][k]) << " - " << setw(2) << get<2>(D.ShowTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<3>(D.ShowTime[i][j][k]) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}