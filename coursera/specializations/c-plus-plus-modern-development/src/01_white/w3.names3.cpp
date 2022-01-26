#include <map>
#include <string>
#include <vector>

using namespace std;

class Person {
    private:
        map<int,string> _names;
        map<int,string> _families;
        int _birth_year;

    public:
        Person(const string& first_name, const string& last_name, int birth_year){
            _birth_year = birth_year;
            ChangeFirstName(birth_year, first_name);
            ChangeLastName(birth_year, last_name);
        }

        void ChangeFirstName(int year, const string& first_name) {
            if(year < _birth_year){
                return;
            }

            // добавить факт изменения имени на first_name в год year
            _names[year] = first_name;
        }
        
        void ChangeLastName(int year, const string& last_name) {
            if(year < _birth_year){
                return;
            }

            // добавить факт изменения фамилии на last_name в год year
            _families[year] = last_name;
        }

        string GetFullName(int year) const {
            if(year < _birth_year){
                return "No person";
            }

            // получить имя и фамилию по состоянию на конец года year
            string first_name = "", last_name="";
            for(auto& pair: _names){
                if(pair.first <= year){
                    first_name = pair.second;
                }
                else
                {
                    break;
                }
            }

            for(auto& pair: _families){
                if(pair.first <= year){
                    last_name = pair.second;
                }
                else
                {
                    break;
                }
            }

            if(first_name == "" && last_name == ""){
                return "Incognito";
            }
            else if(first_name == ""){
                return last_name + " with unknown first name";
            } else if(last_name == ""){
                return first_name + " with unknown last name";
            }
            else{
                return first_name + " " + last_name;
            }
        }

        string GetFullNameWithHistory(int year) const {
            if(year < _birth_year){
                return "No person";
            }
    
            vector<string> firsts, lasts;
            for(auto item:_names){
            if(item.first <= year){
                if(firsts.size() == 0 || firsts[firsts.size()-1] != item.second){
                firsts.push_back(item.second);
                }
            }
            else
            {
                break;
            }
            }
            for(auto item: _families){
            if(item.first <= year){
                if(lasts.size() == 0 || lasts[lasts.size()-1] != item.second){
                lasts.push_back(item.second);
                }
            }
            else
            {
                break;
            }
            }

            string result = "";
            if(firsts.size() == 0 && lasts.size() == 0){
            result = "Incognito";
            }
            else if(firsts.size() == 0){
            result += lasts[lasts.size()-1];
            if(lasts.size() > 1){
                result += " (";
                for(int index = lasts.size()-2; index >=0; --index){
                result += lasts[index];
                if(index > 0){
                    result+=", ";
                }
                }
                result+=")";
            }

            result+= " with unknown first name";
            }
            else if(lasts.size() == 0){
            result += firsts[firsts.size()-1];
            if(firsts.size() > 1){
                result += " (";
                for(int index = firsts.size()-2; index >=0; --index){
                result += firsts[index];
                if(index > 0){
                    result+=", ";
                }
                }
                result+=")";
            }

            result+= " with unknown last name";
            }
            else{
            result += firsts[firsts.size()-1];
            if(firsts.size() > 1){
                result += " (";
                for(int index = firsts.size()-2; index >=0; --index){
                result += firsts[index];
                if(index > 0){
                    result+=", ";
                }
                }
                result+=")";
            }
            result+=" ";
            result += lasts[lasts.size()-1];
            if(lasts.size() > 1){
                result += " (";
                for(int index = lasts.size()-2; index >=0; --index){
                result += lasts[index];
                if(index > 0){
                    result+=", ";
                }
                }
                result+=")";
            }
            }
            return result;
        }
};