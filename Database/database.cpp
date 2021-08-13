#include <iostream>
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#define iss istringstream

using namespace std;

class Date {
public:
    long long GetYear() const;
    long long GetMonth() const;
    long long GetDay() const;
    Date(const long long &y, const long long &m, const long long &d);
private:
    long long year, month, day;
};

long long Date::GetYear() const {
    return year;
}

long long Date::GetMonth() const {
    return month;
}

long long Date::GetDay() const {
    return day;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if(rhs.GetYear() ==  lhs.GetYear()) {
        if(rhs.GetMonth() == lhs.GetMonth()) {
            return rhs.GetDay() > lhs.GetDay();
        }
        return rhs.GetMonth() > lhs.GetMonth();
    }
    return rhs.GetYear() > lhs.GetYear();
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setw(4) << setfill('0') << to_string(date.GetYear()) << '-';
    stream << setw(2) << setfill('0') << to_string(date.GetMonth()) << '-';
    stream << setw(2) << setfill('0') << to_string(date.GetDay()) ;
    return stream;
}

Date::Date(const long long &y, const long long &m, const long long &d) {
    string error_message_month = "Month value is invalid: " + to_string(m);
    string error_message_day = "Day value is invalid: " + to_string(d);
    if(m < 1 || m > 12) throw invalid_argument(error_message_month);
    else if(d < 1 || d > 31) throw invalid_argument(error_message_day);
    year = y; month = m; day = d;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    unsigned long  DeleteDate(const Date& date);

    set<string> Find(const Date& date) const;

    void Print() const;
private:
    map<Date, set<string>> database;
};

void Database::AddEvent(const Date &date, const string &event) {
    database[date].insert(event);
}

bool Database::DeleteEvent(const Date &date, const string &event) {
    auto it = database.find(date);
    if(it != database.end() && it->second.count(event)) {
        it->second.erase(event);
        return true;
    } return false;
}

unsigned long Database::DeleteDate(const Date &date) {
    unsigned long size_out = 0;
    if(database.count(date)) {
        size_out = database[date].size();
        database.erase(date);
    }
    return size_out;
}

set<string> Database::Find(const Date &date) const {
    set<string> temp;
    if(database.count(date)) {
        temp = database.at(date);
    }
    return temp;
}

void Database::Print() const {
    for(const auto &item : database) {
        for(const auto &event : item.second) {
            cout << item.first << " " << event << endl;
        }
    }
}

Date getDateFromString(const string &dateString) {
    iss streamDate(dateString); bool stringCheck = true;
    long long year,month, day;
    stringCheck = (stringCheck && streamDate >> year); stringCheck = (stringCheck && (streamDate.peek() == '-'));
    streamDate.ignore(1);
    stringCheck = (stringCheck && streamDate >> month); stringCheck = (stringCheck && streamDate.peek() == '-');
    streamDate.ignore(1);
    stringCheck = (stringCheck && streamDate >> day); stringCheck = (stringCheck && streamDate.eof());
    if(!stringCheck) throw logic_error("Wrong date format: " + dateString);
    return {year, month, day};
}

string command;

int main() {
    Database main_project_database;
    map<string, long long> demand_to_signal = {{"Add", 1}, {"Del", 2}, // 1 : Add | 2 : Delete | 3 : Find
                                      {"Find", 3}, {"Print", 4}}; //4 : Print
    try {
        while (getline(cin, command)) {
            if(command.empty()) continue;
            stringstream stream(command);
            string userDemand;
            stream >> userDemand;
            long long command_signal = demand_to_signal[userDemand];
            switch(command_signal) {
                case 1: { // 1 : Add
                    string current_date, event_to_add;
                    stream >> current_date >> event_to_add;
                    const Date date_to_add = getDateFromString(current_date);
                    bool flag1 = !(event_to_add.empty()); bool flag2 = (event_to_add != " ");
                    if(flag1 || flag2) {
                        main_project_database.AddEvent(date_to_add, event_to_add);
                    }
                    break;
                }
                case 2: { // 2 : Delete
                    string current_date, event_to_delete;
                    stream >> current_date;
                    if(!stream.eof()) {
                        stream >> event_to_delete;
                    }
                    const Date date_to_delete = getDateFromString(current_date);

                    if (event_to_delete.empty())  {
                        unsigned long count_deleted_events = main_project_database.DeleteDate(date_to_delete);
                        cout << "Deleted " << count_deleted_events << " events" << endl;
                    } else {
                        bool flag = main_project_database.DeleteEvent(date_to_delete, event_to_delete);
                        cout << ((flag) ? "Deleted successfully" : "Event not found") << endl;
                    }
                    break;
                }
                case 3: { // 3 : Find
                    string current_date, event_nill;
                    stream >> current_date >> event_nill;
                    const Date date_to_find = getDateFromString(current_date);
                    set<string> events_on_date = main_project_database.Find(date_to_find);
                    for(const string &ev : events_on_date) cout << ev << endl;
                    break;
                }
                case 4: { // 4 : Print
                    main_project_database.Print();
                    break;
                }
                default: { // Everything other user command (not included in our database)
                    cout << "Unknown command: " << userDemand << endl;
                }
            }
        }
    } catch(const exception &exp) {
        cout << exp.what() << endl;
        return 0;
    }
    return 0;
}
