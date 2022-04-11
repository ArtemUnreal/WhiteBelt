#include <iostream>
#include <exception>
#include <string>
#include <set>
#include <map>

using namespace std;

class Date {
public:
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }

private:
    int year, month, day;
};


bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    
    return lhs.GetYear() < rhs.GetYear();
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        new_date.insert(date);
        date_event[event] = new_date;
    }

    bool DeleteEvent(const Date& date, const string& event) {
        cin >> operation_word;

        if (date_event[operation_word] == date_event[event]) {
            date_event.erase(event);
            cout << "Deleted successfully" << endl;
            return true;
        }
        else {
            cout <<  "Event not found" << endl;
            return false;
        }
    }

    int  DeleteDate(const Date& date) {
        cin >> date;
    }

    /* ??? */ Find(const Date& date) const;

    void Print() const;

private:
    map <string, set <Date>> date_event;
    set <Date> new_date;
    string operation_word;
    set <Date> date_for_del;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        // —читайте команды с потока ввода и обработайте каждую
    }

    return 0;
}
