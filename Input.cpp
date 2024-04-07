#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
#define RESET   "\033[0m"
#define MAGENTA "\033[35m"  //MEGENTA color
#define CYAN    "\033[36m"  //CYAN color
#define BLUE    "\033[34m"  //BLUE color
#define GREEN   "\033[32m"  //GREEN color
#define BOLD_RED     "\033[1;31m"
#include "CompareTimeSlot.cpp" //Compares Two time slots
using namespace std;
int String_to_int(const string &str) // String_to_int function converts a string to the integer
{
    int result = 0;
    int sign = 1;
    int i = 0;
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
    Data()
    {
        Size = CalculateRow();
        IndexNumber = new int[Size];
        UserName = new string[Size];
        ans1 = new int[Size];
        ans2 = new int[Size];
        fill(ans1, ans1 + Size, 0); // To set all the elements of the vector as 0
        fill(ans2, ans2 + Size, 0);
    }
    int *ans1 = 0; // Total Free Time of each user of a week
    int *ans2 = 0; // Total Show Time of each user of a week
    int Size;
    int TotalShowMiss = 0;
    int *IndexNumber;
    vector<string> Line;
    string *UserName;
    vector<vector<string>> ShowName;
    vector<vector<vector<tuple<int, int, int, int>>>> SlotTime;
    vector<vector<vector<tuple<int, int, int, int>>>> ShowTime;
    vector<vector<vector<tuple<int, int, int, int>>>> RecordTime;
    vector<vector<vector<tuple<int, int, int, int>>>> WatchTime;
    int CalculateRow();                                                // CalculateRow function gives total number of the family members
    tuple<int, int, int, int> ConvertTimeSlot(const string &TimeSlot); // ConvertTimeSlot converts a time string into the tuple
    void ReadCSV();                                                    // ReadCSV function to read the csv file
    void HandleConflict();                                             // HandleConflict function that handles conflict according to priority of the user when there is conflict between two users it allows to watch the user who has the highest priority
                           // This(HandleConflict) Function also handles the case when multiple user likes same shows at the same time
    void MakeFunction(); // MakeFunction function is used to record and watch all the necessary time of the user
    void DisplayInput();
    void Print_line(char symbol,int number);
    void DisplayRecord();
      
};

void Data :: Print_line(char symbol,int number){
    
    for(int i=0;i<number;i++)
    {
        cout<<symbol;
    }
    cout<<endl;

}
int Data ::CalculateRow()
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
    return max(0, result); // To avoid negative value
}
void Data ::ReadCSV()
{
    int i = 0;
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
        getline(ss, IndexNumberRow, ','); // Reads data columnwise
        IndexNumber[i] = String_to_int(IndexNumberRow);
        getline(ss, UserName[i], ',');

        string Time;
        getline(ss, Time, ','); // Reads the data of whole weeks Free Time

        vector<vector<tuple<int, int, int, int>>> EachMemberTime;
        stringstream sEachMember(Time);
        string TimeEachDay;
        while (getline(sEachMember, TimeEachDay, '/')) // Reads data of each day
        {
            vector<tuple<int, int, int, int>> EachDay;
            stringstream sSlot(TimeEachDay);
            string Slot;

            while (getline(sSlot, Slot, ';')) // Reads data when multiple free time in one day
            {

                tuple<int, int, int, int> temp = ConvertTimeSlot(Slot);
                ans1[i] += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp))); // Calculates free time of the user per week
                EachDay.push_back(ConvertTimeSlot(Slot));
            }

            EachMemberTime.push_back(EachDay);
        }

        SlotTime.push_back(EachMemberTime);

        string Show;
        getline(ss, Show, ',');
        vector<string> EachMemberShow;
        stringstream sshow(Show);
        string ShowN;
        while (getline(sshow, ShowN, ';')) // Reads data for user having multiple fav shows
        {
            EachMemberShow.push_back(ShowN);
        }
        ShowName.push_back(EachMemberShow);

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
                tuple<int, int, int, int> temp = ConvertTimeSlot(ShowNum);
                ans2[i] += ((get<2>(temp) * 60 + get<3>(temp)) - (get<0>(temp) * 60 + get<1>(temp))); // Calcuates the show time of the user per week
                ShowNumber.push_back(ConvertTimeSlot(ShowNum));
            }
            Member.push_back(ShowNumber);
        }
        ShowTime.push_back(Member);
        i++;
    }
    InputFile.close();
}


tuple<int, int, int, int> Data ::ConvertTimeSlot(const string &TimeSlot)
{
    int minute1, minute2, hour1, hour2;
    sscanf(TimeSlot.c_str(), "%d:%d-%d:%d", &hour1, &minute1, &hour2, &minute2);
    return make_tuple(hour1, minute1, hour2, minute2);
}

void Print_line(char symbol,int number)
{
    for(int i=0;i<number;i++)
    {
        cout<<symbol;
    }
    cout<<endl;
}

void Data ::HandleConflict()
{
    ReadCSV();
    cout<<BLUE;Print_line('-',80);cout<<RESET;
    cout<<GREEN<<"=> Displaying User having Same Show or Conflict"<<RESET<<endl;
    cout<<BLUE;Print_line('-',80);cout<<RESET;
    for (int day = 0; day < 7; day++)
    {
        bool flag=false;
        cout<<"=> "<<MAGENTA<<" DAY : "<<day+1<<RESET<<endl;
        for (int user_index = 0; user_index < Size; user_index++)
        {

            vector<tuple<int, int, int, int>> &current_user_showtime = ShowTime[user_index][day];
            vector<string> &current_user_showname = ShowName[user_index];
            string current_user_name = UserName[user_index];

            for (int prev_user_index = 0; prev_user_index < user_index; prev_user_index++)
            {
                int k = 0; // Declare k for current_user_showname to compare each and every shows name

                vector<tuple<int, int, int, int>> &prev_user_showtime = ShowTime[prev_user_index][day];
                vector<string> &prev_user_showname = ShowName[prev_user_index];
                string prev_user_name = UserName[prev_user_index];
                for (auto &current_slot : current_user_showtime)
                {

                    int p = 0; // Declare p for prev_user_showname to compare each and every shows name
                    for (auto &prev_slot : prev_user_showtime)
                    {
                        if(get<0>(current_slot)==25 && get<1>(current_slot)==25 && get<2>(current_slot)==25 && get<3>(current_slot)==25 && get<0>(prev_slot)==25 && get<0>(prev_slot)==25 && get<1>(prev_slot)==25 && get<2>(prev_slot)==25 && get<3>(prev_slot)==25)continue;
                        if ((Compare(current_slot, prev_slot) == 0) && (current_user_showname[k] != prev_user_showname[p]))
                        {
                            flag=true;
                            cout<<BLUE;
                            Print_line('-',80);
                            cout<<RESET;
                            cout <<" | "<<BOLD_RED<< "Conflict :: "<<RESET<<" | "<<endl;
                            cout <<" | "<< prev_user_name << " has overlapping showtime with " << current_user_name << " on Day " << day + 1 << " at " << get<0>(prev_slot) << ":" << setw(2) << setfill('0') << get<1>(prev_slot) << "-" << setw(2) << setfill('0') << get<2>(prev_slot) << ":" << setw(2) << setfill('0') << get<3>(prev_slot) <<" | "<< endl;
                            get<0>(current_slot) = 25; // assign value 25 so that this time slot is not read afterwards during the code and is marked as the missed slot
                            get<1>(current_slot) = 25;
                            get<2>(current_slot) = 25;
                            get<3>(current_slot) = 25;
                            cout<<BLUE;
                            Print_line('-',80);
                            cout<<RESET;
                            
                        }
                        else if (current_user_showname[k] == prev_user_showname[p] && Compare(current_slot, prev_slot) == 0) // if multiple user have same fav shows and their showtime is also same then this two loops will compare the free time of both the users and if the free time is also same then they willl watch the show at the same time(together)
                        {
                            for (int i = 0; i < SlotTime[user_index][day].size(); i++)
                            {
                                for (int j = 0; j < SlotTime[prev_user_index][day].size(); j++)
                                {
                                    if (Compare(SlotTime[user_index][day][i], SlotTime[prev_user_index][day][j]) == 0)
                                    {
                                        if(get<0>(current_slot)==25 && get<1>(current_slot)==25 && get<2>(current_slot)==25 && get<3>(current_slot)==25 && get<0>(prev_slot)==25 && get<0>(prev_slot)==25 && get<1>(prev_slot)==25 && get<2>(prev_slot)==25 && get<3>(prev_slot)==25)continue;
                                        flag=true;
                                        cout<<BLUE;
                                        Print_line('-',80);
                                        cout<<RESET;
                                        cout << " | "<<CYAN<<"Same Shows :: " <<RESET<<" | " <<endl;
                                        cout << " | " <<UserName[user_index] << " and " << UserName[prev_user_index] << " are watching " << ShowName[user_index][k] << " on Day " << day + 1 << " at " << get<0>(SlotTime[prev_user_index][day][j]) << ":" << setw(2) << setfill('0') << get<1>(SlotTime[user_index][day][j]) << "-" << setw(2) << setfill('0') << get<2>(SlotTime[prev_user_index][day][j]) << ":" << setw(2) << setfill('0') << get<3>(SlotTime[prev_user_index][day][j]) << " | " <<endl;
                                        auto it1 = find(SlotTime[user_index][day].begin(), SlotTime[user_index][day].end(), SlotTime[user_index][day][i]);
                                        SlotTime[user_index][day].erase(it1);
                                        if (SlotTime[user_index][day].empty())
                                        {
                                            SlotTime[user_index][day].push_back(make_tuple(0, 0, 0, 0));
                                        }
                                        auto it2 = find(SlotTime[prev_user_index][day].begin(), SlotTime[prev_user_index][day].end(), SlotTime[prev_user_index][day][j]);
                                        SlotTime[prev_user_index][day].erase(it2);
                                        if (SlotTime[prev_user_index][day].empty())
                                        {
                                            SlotTime[prev_user_index][day].push_back(make_tuple(0, 0, 0, 0));
                                        }
                                        auto it3 = find(ShowTime[user_index][day].begin(), ShowTime[user_index][day].end(), ShowTime[user_index][day][i]);
                                        ShowTime[user_index][day].erase(it3);
                                        auto it4 = find(ShowTime[prev_user_index][day].begin(), ShowTime[prev_user_index][day].end(), ShowTime[prev_user_index][day][j]); // ShowTime[prev_user_index][day].push_back(make_tuple(2,2,2,2));
                                        ShowTime[prev_user_index][day].erase(it4);
                                        cout<<BLUE;
                                        Print_line('-',80);
                                        cout<<RESET;
                                    }
                                }
                            }
                            
                        }
                        p++;
                    }
                    k++;
                }
            }
        }
        if(flag==false)
        {   cout<<BLUE;
            Print_line('-',80);
            cout<<RESET;
            cout<<" | No conflict and no same show | "<<endl;
            cout<<BLUE;
            Print_line('-',80);
            cout<<RESET;
            cout<<endl;
        }
        
    }
}
    void Data ::MakeFunction()
{
    HandleConflict();
    cout<<BLUE;
            Print_line('-',80);
            cout<<RESET;
            cout<<GREEN<<"=> User Having Same Free Time And Show Time"<<endl;
            cout<<RESET;
            cout<<BLUE;
            Print_line('-',80);
            cout<<RESET;
    
    for (int j = 0; j < 7; j++)
    {
        cout<<BLUE;
        Print_line('-',80);
        cout<<RESET;
        cout<<MAGENTA<<"=> Day : "<<j+1<<RESET<<endl;
        bool same = false;
        bool lessthan = false;
        bool greaterthan = false;
        vector<vector<tuple<int, int, int, int>>> Record2D;
        vector<vector<tuple<int, int, int, int>>> Watch2D;
        for (int i = 0; i < Size; i++)
        {
            same = false;
            lessthan = false;
            greaterthan = false;
            vector<tuple<int, int, int, int>> Record1D;
            vector<tuple<int, int, int, int>> Watch1D;
            for (int k = SlotTime[i][j].size() - 1; k >= 0; k--)
            {
                for (int l = ShowTime[i][j].size() - 1; l >= 0; l--)
                {
                    int CompareResult = Compare(SlotTime[i][j][k], ShowTime[i][j][l]);

                    if ((get<0>(ShowTime[i][j][l]) == 25) && (get<1>(ShowTime[i][j][l]) == 25) && (get<2>(ShowTime[i][j][l]) == 25) && (get<3>(ShowTime[i][j][l]) == 25))
                    {
                        TotalShowMiss++;
                    }
                    else
                    {
                        if (CompareResult == 0)
                        {
                            Watch1D.push_back(ShowTime[i][j][l]);
                            cout << UserName[i] << " is Watching " << ShowName[i][l] << " at " << get<0>(ShowTime[i][j][l]) << ":" << setw(2) << setfill('0') << get<1>(ShowTime[i][j][l]) << "-" << setw(2) << setfill('0') << get<2>(ShowTime[i][j][l]) << ":" << setw(2) << setfill('0') << get<3>(ShowTime[i][j][l]) << endl;

                            auto it = find(SlotTime[i][j].begin(), SlotTime[i][j].end(), SlotTime[i][j][k]);
                            SlotTime[i][j].erase(it);
                            same = true;
                        }
                        else if (CompareResult == 1)
                        {
                            auto it = find(Record1D.begin(), Record1D.end(), ShowTime[i][j][l]);
                            auto it1 = find(Watch1D.begin(), Watch1D.end(), ShowTime[i][j][l]);
                            if ((it == Record1D.end()) && (it1 == Watch1D.end()))
                            Record1D.push_back(ShowTime[i][j][l]);
                            greaterthan = true;
                        }

                        else if (CompareResult == -1)
                        {
                            auto it = find(Record1D.begin(), Record1D.end(), ShowTime[i][j][l]);
                            if (it == Record1D.end())
                            {
                                Record1D.push_back(ShowTime[i][j][l]);
                            }
                            lessthan = true;
                        }
                    }
                }
            }
            if (same == false)
            {
                tuple<int, int, int, int> Temp = make_tuple(0, 0, 0, 0);
                Watch1D.push_back(make_tuple(0, 0, 0, 0));
                same = true;
            }
            if (greaterthan || lessthan)
            {
                Record2D.push_back(Record1D);

            } 
            if (same)
            {
                Watch2D.push_back(Watch1D);
            }

        }
        if (greaterthan || lessthan)
        {
            RecordTime.push_back(Record2D);
        }
        if (same)
        {
            WatchTime.push_back(Watch2D);
        }
        
    }
}
    void Data :: DisplayInput(){
    for (int i = 0; i < Size; i++)
    {
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout <<MAGENTA<< "IndexNumber: " <<RESET<< IndexNumber[i] << endl;
        cout << MAGENTA <<"Member Name: " <<RESET<< UserName[i] <<RESET<< endl;
        cout <<MAGENTA<< "Slot Time : " <<RESET<< endl;
        cout<<BLUE;
        Print_line('-',80);
        cout<<RESET;
        for (int j = 0; j < SlotTime[i].size(); j++)
        {
            cout<<BLUE;
    Print_line('-',80);
    cout<<RESET;
            cout <<" | "<<CYAN<<" Day " << j + 1 <<RESET<<" | " <<endl;
            for (int k = 0; k < SlotTime[i][j].size(); k++)
            {
                cout <<" | "<< "Slot " << k + 1 << " : " << setw(2) << get<0>(SlotTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<1>(SlotTime[i][j][k]) << " - " << setw(2) << get<2>(SlotTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<3>(SlotTime[i][j][k]) << "\t  "<<" | ";
                
            }
            cout<<endl;
            
        }
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout << MAGENTA<<"Free minutes = "<<RESET << ans1[i] << endl;
        cout<<BLUE;Print_line('-',80);cout<<RESET;
     
        cout<<endl;
        cout <<MAGENTA<< "Show Name:" << endl;
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout<<endl;
        for (int j = 0; j < ShowName[i].size(); j++)
        {
            cout <<" | "<< "Show " << j + 1 << " : " << ShowName[i][j] <<"\t "<<" | ";
        }
        cout<<endl;
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout <<MAGENTA<<"Show Time:"<<endl;
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        for (int j = 0; j < ShowTime[i].size(); j++)
        {
            cout <<" | "<< CYAN<<"Day " << j + 1 <<RESET<<" | "<< endl;
            for (int k = 0; k < ShowTime[i][j].size(); k++)
            {
                cout <<" | "<<"Slot " << k + 1 << " : " << setw(2) << get<0>(ShowTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<1>(ShowTime[i][j][k]) << " - " << setw(2) << get<2>(ShowTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<3>(ShowTime[i][j][k]) << "\t"<<" | ";
            }

            cout<<endl;
            cout<<BLUE;Print_line('-',80);cout<<RESET;

        }
        
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout << MAGENTA<<"Show Time minutes = "<<RESET << ans2[i] << endl;
        cout<<BLUE;Print_line('-',80);cout<<RESET;
        cout << endl;
    }
}
void Data :: DisplayRecord(){
    for (int i = 0; i < RecordTime.size(); i++)
    {
        cout <<CYAN<<"Day " << i + 1 <<RESET<<endl;
        for (int j = 0; j < RecordTime[i].size(); j++)
        {
            cout <<MAGENTA<< UserName[j] <<RESET<< endl;
            for (int k = 0; k < RecordTime[i][j].size(); k++)
            {
                cout<<" | "<<"Slot "<<k+1<<" : ";
                cout << get<0>(RecordTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<1>(RecordTime[i][j][k]) << "-" << setw(2) << setfill('0') << get<2>(RecordTime[i][j][k]) << ":" << setw(2) << setfill('0') << get<3>(RecordTime[i][j][k]) <<"\t  "<<" | ";
            }
            cout<<endl;
            cout<<BLUE;Print_line('-',80);cout<<RESET;
        }

        cout<<BLUE;Print_line('-',80);cout<<RESET;
    }
}
