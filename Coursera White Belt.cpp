#include <iostream>
#include <exception>
#include <string>
#include <set>
#include <map>

using namespace std;

class Date {
public:
    Date(const int& Year, const int& Month, const int& Day) {
        year = Year;
        month = Month;
        day = Day;
    }
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

istream& operator >>(istream& stream, Date& date) {
    int d, m, y;
    char c;

    if (stream) {
        stream >> d >> c >> m >> c >> y;
        if (stream) {
            if (c == '-') {
                date = Date(d, m, y);
            }
            else {
                stream.setstate(ios_base::failbit);
            }
        }
    }
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
        int d, m, y;
        char c;


        cin >> d >> c >> m >> c >> y;

        if (c == '-') {
            d = date.GetDay();
            m = date.GetMonth();
            y = date.GetYear();
        }
        else {

        }
    }

    /* ??? */ Find(const Date& date) const;

    void Print() const;

private:
    map <string, set <Date>> date_event;
    set <Date> new_date;
    string operation_word;
    
};

int main() {
    Database db;
    Date date {0, 0 ,0};

    string command;
    while (getline(cin, command)) {
        if (command == "Add") {
            cin >> date;
            string event;
            db.AddEvent(date, event);
        }
        else if (command == "Del") {
            cin >> date;
            string event;
            db.DeleteEvent(date, event);
        } 
        // —читайте команды с потока ввода и обработайте каждую
    }

    return 0;
}
