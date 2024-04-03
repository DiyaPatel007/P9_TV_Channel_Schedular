#include <bits/stdc++.h>
#include "CompareTimeSlot.cpp"
using namespace std;
int Stoi(const string &str)
{
    int result = 0;
    int sign = 1;
    size_t i = 0;
    while (isspace(str[i]))
    {
        i++;
    }
    if (str[i] == '-' || str[i] == '+')
    {
        sign = (str[i++] == '-') ? -1 : 1;
    }

    while (isdigit(str[i]))
    {
        result = result * 10 + (str[i++] - '0');
    }
    return sign * result;
}
class Data
{
public:
    int *ans1 = 0;
    int *ans2 = 0;
    int Size;
    int *IndexNumber;
    vector<string> Line;
    vector<vector<int>> DaywiseFreeTime;
    vector<vector<int>> DaywiseShowTime;
    string *UserName;
    vector<vector<string>> ShowName;
    vector<vector<vector<tuple<int, int, int, int>>>> SlotTime;
    vector<vector<vector<tuple<int, int, int, int>>>> ShowTime;
    vector<vector<vector<tuple<int, int, int, int>>>> RecordTime;
    vector<vector<vector<tuple<int, int, int, int>>>> MissingTime;

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
        // ans1[i] += (hour2 * 60 + minute2) - (hour1 * 60 + minute1);
        return make_tuple(hour1, minute1, hour2, minute2);
    }

    tuple<int, int, int, int> ConvertShowTimeSlot(const string &TimeSlot)
    {
        int minute1, minute2, hour1, hour2;
        sscanf(TimeSlot.c_str(), "%d:%d-%d:%d", &hour1, &minute1, &hour2, &minute2);
        // ans2[i] += (hour2 * 60 + minute2) - (hour1 * 60 + minute1);
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
            IndexNumber[i] = Stoi(IndexNumberRow);
            getline(ss, UserName[i], ',');

            string Time;
            getline(ss, Time, ',');

            vector<vector<tuple<int, int, int, int>>> EachMEmberTime;
            stringstream sEachMember(Time);
            string TimeEachDay;
            vector<int> Diff_T;
            while (getline(sEachMember, TimeEachDay, '/'))
            {
                vector<tuple<int, int, int, int>> EachDay;
                stringstream sSlot(TimeEachDay);
                string Slot;

                int diff = 0;

                while (getline(sSlot, Slot, ';'))
                {

                    tuple<int, int, int, int> temp = ConvertFreeTimeSlot(Slot);

                    diff += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    ans1[i] += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    EachDay.push_back(ConvertFreeTimeSlot(Slot));
                }

                EachMEmberTime.push_back(EachDay);
                Diff_T.push_back(diff);
            }

            SlotTime.push_back(EachMEmberTime);
            DaywiseFreeTime.push_back(Diff_T);

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
            vector<int> Diff;
            while (getline(SMember, ShowMember, '/'))
            {
                vector<tuple<int, int, int, int>> ShowNumber;
                stringstream SNumber(ShowMember);
                string ShowNum;
                int diff = 0;
                while (getline(SNumber, ShowNum, ';'))
                {
                    tuple<int, int, int, int> temp = ConvertFreeTimeSlot(ShowNum);
                    diff += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    ans2[i] += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    ShowNumber.push_back(ConvertFreeTimeSlot(ShowNum));
                }
                Member.push_back(ShowNumber);
                Diff.push_back(diff);
            }
            ShowTime.push_back(Member);
            DaywiseShowTime.push_back(Diff);

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
            int value1 = Stoi(x.substr(pos1));
            int value2 = Stoi(y.substr(pos2));
            return value1 < value2; });
        ofstream SortedFile;
        SortedFile.open("Sorted.csv");

        for (int i = 0; i < Line.size(); i++)
        {
            SortedFile << Line[i] << endl; // Writing updated data in new Sorted.cpp file
        }
        SortedFile.close();
        Input.close();
    }
    void ReadSorted()
    {
        i = 0;
        ifstream InputFile("Sorted.csv");
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
            IndexNumber[i] = Stoi(IndexNumberRow);
            getline(ss, UserName[i], ',');

            string Time;
            getline(ss, Time, ',');

            vector<vector<tuple<int, int, int, int>>> EachMEmberTime;
            stringstream sEachMember(Time);
            string TimeEachDay;
            vector<int> Diff_T;
            while (getline(sEachMember, TimeEachDay, '/'))
            {
                vector<tuple<int, int, int, int>> EachDay;
                stringstream sSlot(TimeEachDay);
                string Slot;

                int diff = 0;

                while (getline(sSlot, Slot, ';'))
                {

                    tuple<int, int, int, int> temp = ConvertFreeTimeSlot(Slot);
                    diff += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    ans1[i] += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    EachDay.push_back(ConvertFreeTimeSlot(Slot));
                }

                EachMEmberTime.push_back(EachDay);
                Diff_T.push_back(diff);
            }

            SlotTime.push_back(EachMEmberTime);
            DaywiseFreeTime.push_back(Diff_T);

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
            vector<int> Diff;
            while (getline(SMember, ShowMember, '/'))
            {
                vector<tuple<int, int, int, int>> ShowNumber;
                stringstream SNumber(ShowMember);
                string ShowNum;
                int diff = 0;
                while (getline(SNumber, ShowNum, ';'))
                {
                    tuple<int, int, int, int> temp = ConvertFreeTimeSlot(ShowNum);
                    diff += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    ans2[i] += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp)));
                    ShowNumber.push_back(ConvertFreeTimeSlot(ShowNum));
                }
                Member.push_back(ShowNumber);
                Diff.push_back(diff);
            }
            ShowTime.push_back(Member);
            DaywiseShowTime.push_back(Diff);

            string TotalShowTime;
            getline(ss, TotalShowTime, ',');
            ans2[i] = Stoi(TotalShowTime);
            string TotalFreeTime;
            getline(ss, TotalFreeTime, '\n');
            ans1[i] = Stoi(TotalFreeTime);
            i++;
        }
        InputFile.close();
    }

    void MakeFunction();
};

void Data ::MakeFunction()
{
    ReadSorted();
    int i;
    for (i = 0; i < Size; i++)
    {
        vector<vector<tuple<int, int, int, int>>> Temp1;
        vector<vector<tuple<int, int, int, int>>> Temp2;
        for (int j = 0; j < SlotTime[i].size(); j++)
        {
            vector<tuple<int, int, int, int>> Temp3;
            vector<tuple<int, int, int, int>> Temp4;
            for (int k = 0; k < SlotTime[i][j].size(); k++)
            {

                for(int l=0;l<ShowTime[i][j].size();l++)
                {
                if (!(CompareShowAndFreeTime(SlotTime[i][j][k], ShowTime[i][j][l])))
                {
                    Temp3.push_back(ShowTime[i][j][l]);
                    Temp4.push_back(SlotTime[i][j][k]);
                    Temp1.push_back(Temp3);
                    Temp2.push_back(Temp4);
                    RecordTime.push_back(Temp1);
                    MissingTime.push_back(Temp2);
                }
                }
            }
            // Temp1.push_back(Temp3);
            // Temp2.push_back(Temp4);
        }
        // RecordTime.push_back(Temp1);
        // MissingTime.push_back(Temp2);
    }
}
