#include <iostream>
#include <exception>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
    Date() {
    
}

    Date(int Year, int Month, int Day) {
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
    int year;
    int month;
    int day;
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
        stream >> y >> c >> m >> c >> d;
        date = Date(y, m, d);
        return stream;
    }
}

ostream& operator <<(ostream& stream, const Date& date) {
    return stream << date.GetYear() << "-" << date.GetMonth() << "-" << date.GetDay();
}

Date ParseDate(const string& s) {
    int year, month, day;
    Date date;
    stringstream stream;
    stream.str(s);

    stream >> year;

    if (stream.peek() == '-') {
        stream.ignore(1);
    }
    else {
        string e = "Wrong date format: " + s;
        throw runtime_error(e);
    }

    stream >> month;
    if (stream.peek() == '-') {
        stream.ignore(1);
    }
    else {
        string e = "Wrong date format: " + s;
        throw runtime_error(e);
    }
    if (month < 1 || month > 12) {
        string e = "Month value is invalid: " + to_string(month);
        throw runtime_error(e);
    }

    stream >> day;
    if (stream.peek() != EOF) {
        string e = "Wrong date format: " + s;
        throw runtime_error(e);
    }
    if (day < 1 || day > 31) {
        string e = "Day value is invalid: " + to_string(day);
        throw runtime_error(e);
    }

    return { year, month, day };
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        date_events[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (date_events[date].count(event) != 0) {
            date_events[date].erase(event);
            return true;
        }
        else {
            return false;
        }
    }

    int  DeleteDate(const Date& date) {
        if (date_events.count(date) > 0) {
            int d = date_events.at(date).size();
            date_events.erase(date);

            return d;
        }
        else {
            return 0;
        }
    }

    void Find(const Date& date) const {
        for (const auto& a : date_events.at(date)) {
            cout << a << endl;
        }
    }

    void Print() const {
        for (const auto& a : date_events) {
            for (const auto& i : date_events.at(a.first)) {
                cout << setw(4) << setfill('0') << a.first.GetYear()  << '-'
                     << setw(2) << setfill('0') << a.first.GetMonth() << '-'
                     << setw(2) << setfill('0') << a.first.GetDay()   << ' ' 
                     << i << endl;
            }
        }
    }

private:
    map <Date, set <string>> date_events; 
};

int main() {
    Database db;
    Date date;

    string command;
    while (getline(cin, command)) {
        if (command == " " || command == "" || command == "/n")
        {
            continue;
        }
        
        istringstream stream(command);
        string in_date, in_event, operation_word;
        stream >> operation_word >> in_date >> in_event;

        if (operation_word == "Add") {
            try {
                if (in_event != "") {
                    db.AddEvent(ParseDate(in_date), in_event);
                }
            }
            catch (runtime_error& er) {
                cout << er.what() << endl;
            }
            
        }
        else if (operation_word == "Del") {
            try {
                if (in_event.empty()) {
                    int d = db.DeleteDate(ParseDate(in_date));
                    cout << "Deleted " << d << " events" << endl;
                }
                else {
                    if (db.DeleteEvent(ParseDate(in_date), in_event)) {
                        cout << "Deleted successfully" << endl;
                    }
                    else {
                        cout << "Event not found" << endl;
                    }
                }
            }
            catch (runtime_error& er) {
                cout << er.what() << endl;
            }
        } 
        else if (operation_word == "Find") {
            db.Find(ParseDate(in_date));
        }
        else if (operation_word == "Print") {
            db.Print();
        }
        else {
            cout << "Unknown command:" << operation_word << endl;
        }
        // —читайте команды с потока ввода и обработайте каждую
    }

    return 0;
}
