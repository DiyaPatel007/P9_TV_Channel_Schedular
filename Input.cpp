#include <bits/stdc++.h>
using namespace std;
class Data
{
public:
    int Size;
    int *Priority;
    string *UserName;
    vector<vector<string>> ShowName;
    vector<vector<vector<tuple<int, int, int, int>>>> SlotTime;
    vector<vector<vector<tuple<int, int, int, int>>>> ShowTime;

    Data()
    {
        Size = CalculateRow();
        cout << "The size is : " << Size << endl;
        Priority = new int[Size];
        UserName = new string[Size];
    }

    int CalculateRow()
    {
        int count = 0;
        ifstream input;
        string S;
        input.open("TV_P9.csv");
        while (getline(input, S, '\n'))
        {
            count++;
        }

        input.close();
        int result = (count - 1);
        return max(0, result);
    }

    tuple<int, int, int, int> ConvertTimeSlot(const string &TimeSlot)
    {
        int minute1, minute2, hour1, hour2;
        sscanf(TimeSlot.c_str(), "%d:%d-%d:%d", &hour1, &minute1, &hour2, &minute2);
        return make_tuple(hour1, minute1, hour2, minute2);
    }

    void ReadCSV()
    {
        ifstream InputFile("TV_P9.csv");
        if (!InputFile.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string temp1;
        getline(InputFile, temp1, '\n');
        string Row;
        int i = 0;
        while (getline(InputFile, Row) && i < Size)
        {
            stringstream ss(Row);
            string PriorityRow;
            getline(ss, PriorityRow, ',');
            Priority[i] = stoi(PriorityRow);
            getline(ss, UserName[i], ',');

            string Time;
            getline(ss, Time, ',');

            vector<vector<tuple<int, int, int, int>>> EachMEmberTime;
            stringstream sEachMember(Time);
            string TimeEachDay;
            while (getline(sEachMember, TimeEachDay, '/'))
            {
                vector<tuple<int, int, int, int>> EachDay;
                stringstream sSlot(TimeEachDay);
                string Slot;
                while (getline(sSlot, Slot, ';'))
                {
                    EachDay.push_back(ConvertTimeSlot(Slot));
                }
                EachMEmberTime.push_back(EachDay);
            }
            SlotTime.push_back(EachMEmberTime);

            string Show;
            getline(ss, Show, ',');
            vector<string> EAchMemberShow;
            stringstream sshow(Show);
            string ShowN;
            while (getline(sshow, ShowN, ';'))
            {
                EAchMemberShow.push_back(ShowN);
            }
            ShowName.push_back(EAchMemberShow);
            string ShowTiming;
            getline(ss, ShowTiming, ',');
            vector<vector<tuple<int, int, int, int>>> Member;
            stringstream SMember(ShowTiming);
            string ShowMember;
            while (getline(SMember, ShowMember, '/'))
            {
                vector<tuple<int, int, int, int>> ShowNumber;
                stringstream SNumber(ShowMember);
                string ShowNum;
                while (getline(SNumber, ShowNum, ';'))
                {
                    ShowNumber.push_back(ConvertTimeSlot(ShowNum));
                }
                Member.push_back(ShowNumber);
            }
            ShowTime.push_back(Member);
            i++;
        }
        InputFile.close();
    }
};


          