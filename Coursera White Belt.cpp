#include <iostream>
#include <exception>
#include <string>

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
    return (lhs - rhs).GetYear() < 0;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);

    /* ??? */ Find(const Date& date) const;

    void Print() const;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        // �������� ������� � ������ ����� � ����������� ������
    }

    return 0;
}
