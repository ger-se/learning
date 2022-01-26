#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void do_it(){
    vector<string> result;
    map<vector<string>, int> buses_by_stops;

    int commands_count;
    cin >> commands_count;
    for(int command_index = 0; command_index < commands_count; ++command_index){
        vector<string> stops;
        int stops_count;
        cin >> stops_count;
        for(int stop_index = 0; stop_index < stops_count; ++stop_index){
            string stop;
            cin >> stop;
            stops.push_back(stop);
        }

        if(buses_by_stops.count(stops) == 0){
            int bus = buses_by_stops.size() + 1;
            buses_by_stops[stops] = bus;
            string r = "New bus ";
            r+= std::to_string(bus);
            result.push_back(r);
        }else{
            int bus = buses_by_stops[stops];
            string r = "Already exists for ";
            r+= std::to_string(bus);
            result.push_back(r);
        }
    }

    for(auto r: result){
        cout << r << endl;
    }
}

int main()
{
    // bool is_test = false;
    //auto commands = read();
    do_it();

    return 0;
}