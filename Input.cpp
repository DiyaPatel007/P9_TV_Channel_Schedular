#include <bits/stdc++.h>
using namespace std;
class Data
{
public:
    int *ans1 = 0;
    int *ans2 = 0;
    int Size;
    int *IndexNumber;
    vector<string> Line;
    string *UserName;
    vector<vector<string>> ShowName;
    vector<vector<vector<tuple<int, int, int, int>>>> SlotTime;
    vector<vector<vector<tuple<int, int, int, int>>>> ShowTime;

    Data()
    {
        Size = CalculateRow();
        IndexNumber = new int[Size];
        UserName = new string[Size];
        ans1 = new int[Size];
        ans2 = new int[Size];
        fill(ans1, ans1 + Size, 0); // To set vector NULL
        fill(ans2, ans2 + Size, 0);
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
        return max(0, result); // to avoid negative value
    }
    int i = 0;
    tuple<int, int, int, int> ConvertFreeTimeSlot(const string &TimeSlot)
    {
        int minute1, minute2, hour1, hour2;
        sscanf(TimeSlot.c_str(), "%d:%d-%d:%d", &hour1, &minute1, &hour2, &minute2);
        ans1[i] += (hour2 * 60 + minute2) - (hour1 * 60 + minute1);
        return make_tuple(hour1, minute1, hour2, minute2);
    }

    tuple<int, int, int, int> ConvertShowTimeSlot(const string &TimeSlot)
    {
        int minute1, minute2, hour1, hour2;
        sscanf(TimeSlot.c_str(), "%d:%d-%d:%d", &hour1, &minute1, &hour2, &minute2);
        ans2[i] += (hour2 * 60 + minute2) - (hour1 * 60 + minute1);
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
        while (getline(InputFile, Row) && i < Size)
        {
            stringstream ss(Row);
            string IndexNumberRow;
            getline(ss, IndexNumberRow, ',');
            IndexNumber[i] = stoi(IndexNumberRow);
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
                    EachDay.push_back(ConvertFreeTimeSlot(Slot));
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
                    ShowNumber.push_back(ConvertShowTimeSlot(ShowNum));
                }
                Member.push_back(ShowNumber);
            }
            ShowTime.push_back(Member);

            i++;
        }
        InputFile.close();
    }
    void SortData()
    {
        ifstream Input;
        Input.open("TV_P9.csv", ios::in | ios::out); // Open in read/write mode
        if (!Input.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string temp;
        getline(Input, temp);
        temp += ",TotalShowTime,TotalFreeTime";
        Line.push_back(temp);
        int i = 0;
        while (i < Size)
        {
            string L;
            getline(Input, L);
            L += ",";
            L += to_string(ans2[i]);
            L += ",";
            L += to_string(ans1[i]);
            Line.push_back(L);
            i++;
        }
        // Sort Line vector based on the ascending value of ans1
        sort(Line.begin() + 1, Line.end(), [](const string &x, const string &y)
             {
            int pos1 = x.find_last_of(",") + 1;
            int pos2 = y.find_last_of(",") + 1;
            int value1 = stoi(x.substr(pos1));
            int value2 = stoi(y.substr(pos2));
            return value1 < value2; });
        ofstream SortedFile;
        SortedFile.open("Sorted.csv");

        for (int i = 0; i < Line.size(); i++)
        {
            SortedFile << Line[i] << endl;//Writing updated data in new Sorted.cpp file
        }
        SortedFile.close();
        Input.close();
    }
};