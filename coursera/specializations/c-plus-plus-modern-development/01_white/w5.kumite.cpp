#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>
#include <vector>
#include <exception>

using namespace std;

class Date {
private:
    int _year, _month, _day;

public:
    explicit Date(){
        _year = 0, _month = 1, _day = 1;
    }

    explicit Date(int year, int month, int day){
        if(month < 1 || month > 12){
            string err = "Month value is invalid: " + std::to_string(month);
            throw std::invalid_argument(err);
        }
        else if(day < 1 || day > 31){
            string err = "Day value is invalid: " + std::to_string(day);
            throw std::invalid_argument(err);
        }

        _year = year, _month = month, _day = day;
    }

    int GetYear() const{
        return _year;
    }

    int GetMonth() const{
        return _month;
    }

    int GetDay() const{
        return _day;
    }
};

bool operator<(const Date& lhs, const Date& rhs){
    return (lhs.GetDay() + 31*(lhs.GetMonth()-1)+31*12*lhs.GetYear()) < (rhs.GetDay() + 31*(rhs.GetMonth()-1)+31*12*rhs.GetYear());
}

ostream& operator<<(ostream& stream, const Date& date){
    int year = date.GetYear(), month = date.GetMonth(), day = date.GetDay();
    if(year < 0){
        stream << "-";
    }

    stream << setfill('0') << setw(4) << year;
    stream << "-";
    stream << setfill('0') << setw(2) << month;
    stream << "-";
    stream << setfill('0') << setw(2) << day;
    return stream;
}

bool Skip(istream& stream, char symbol){
    if(!stream || stream.eof()){
        return false;
    }

    bool skipped = stream.peek() == symbol;
    if(skipped){
        stream.ignore(1);
    }
    return skipped;
}

bool TryParseDateSegment(istream& stream, int& segment){
    if(!stream || stream.eof()){
        return false;
    }

    int sign = 1;
    if(stream.peek() == '-'){
        sign = -1;
        stream.ignore(1);
    }
    else if(stream.peek() == '+'){
        stream.ignore(1);
    }

    set<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    stringstream s;
    while (stream && !stream.eof())
    {
        char c = stream.peek();
        if(digits.count(c)){
            c = stream.get();
            s << c;
        }
        else{
            break;
        }
    }
    
    s >> segment;
    segment = segment * sign;
    return (bool)s;
}

istream& operator>>(istream& stream, Date& date){
    string input;
    stream >> input;
    stringstream s(input);
    char d;
    int year, month, day;
    if(TryParseDateSegment(s, year)
        && Skip(s, '-')
        && TryParseDateSegment(s,month)
        && Skip(s, '-')
        && TryParseDateSegment(s,day)
        && s.eof()){
        date = Date(year, month, day);
        return stream;
    }

    string err = "Wrong date format: " + input;
    throw std::invalid_argument(err);
}

class Database {
private:
    map<Date,set<string>> data;

public:
    void AddEvent(const Date& date, const string& event){
        data[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event){
        return data.count(date) > 0 && data[date].erase(event) > 0;
    }

    int DeleteDate(const Date& date){
        if(data.count(date)){
            auto events = data[date];
            data.erase(date);
            return events.size();
        }

        return 0;
    }

    set<string> Find(const Date& date) const{
        set<string> result;
        if(data.count(date)){
            result = data.at(date);
        }

        return result;
    }
  
    void Print(ostream& stream) const{
        for(auto dated: data){
            auto date = dated.first;
            for(auto event: dated.second){
                stream << date << " " << event << endl;
            }
        }
    }
};

int main() {
    Database db;
    
    string input;
    while (getline(cin, input)) {
        try
        {
            if(input == ""){
                continue;
            }

            stringstream stream(input);
            string command, event;
            Date date;
            
            stream >> command;
            // if(command == ""){
            //     continue;
            // }
            if(command == "Add"){
                stream >> date >> event;
                db.AddEvent(date, event);
            }
            else if(command == "Del"){
                stream >> date;
                if(stream.eof())
                {
                    auto deleted = db.DeleteDate(date);
                    cout << "Deleted "<< deleted <<" events"<< endl;
                }
                else{
                    stream >> event;
                    auto deleted = db.DeleteEvent(date, event);
                    if(deleted > 0){
                        cout << "Deleted successfully" << endl;
                    }
                    else {
                        cout << "Event not found" << endl;
                    }
                }
            }
            else if(command == "Find"){
                stream >> date;
                auto events = db.Find(date);
                for(auto event: events){
                    cout << event << endl;
                }
            }
            else if(command == "Print"){
                db.Print(cout);
            }
            else{
                cout << "Unknown command: " << command << endl;
                //break;
            }
        }
        catch(const std::invalid_argument& exception)
        {
            cout << exception.what() << endl;
            break;
        }
    }

    return 0;
}