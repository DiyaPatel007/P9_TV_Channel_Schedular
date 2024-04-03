#include <bits/stdc++.h>
#include "Input.cpp"
using namespace std;
int main()
{
    Data D;
    D.ReadSorted();
    D.MakeFunction();
    cout<<endl<<endl<<"RecordTime"<<endl;
    for (int i = 0; i < D.RecordTime.size(); i++)
    {
        cout<<"Day "<<i+1<<endl;
        for (int j = 0; j < D.RecordTime[i].size(); j++)
        {
            cout<<D.UserName[j]<<endl;
            for (int k = 0; k < D.RecordTime[i][j].size(); k++)
            {
                cout<<get<0>(D.RecordTime[i][j][k])<<":"<<setw(2)<<setfill('0')<<get<1>(D.RecordTime[i][j][k])<<"-"<<setw(2)<<setfill('0')<<get<2>(D.RecordTime[i][j][k])<<":"<<setw(2)<<setfill('0')<<get<3>(D.RecordTime[i][j][k])<<endl;
            }
           
        }
    }

    cout<<endl<<endl<<"FreeTimeAssigned"<<endl;
       for (int i = 0; i < D.FreeTimeAssigned.size(); i++)
    {
        cout<<"Day "<<i+1<<endl;
        for (int j = 0; j < D.FreeTimeAssigned[i].size(); j++)
        {
            cout<<D.UserName[j]<<endl;
            for (int k = 0; k < D.FreeTimeAssigned[i][j].size(); k++)
            {
                cout<<get<0>(D.FreeTimeAssigned[i][j][k])<<":"<<setw(2)<<setfill('0')<<get<1>(D.FreeTimeAssigned[i][j][k])<<"-"<<setw(2)<<setfill('0')<<get<2>(D.FreeTimeAssigned[i][j][k])<<":"<<setw(2)<<setfill('0')<<get<3>(D.FreeTimeAssigned[i][j][k])<<endl;
                
            }
           
        }
    }
    return 0 ;
}
