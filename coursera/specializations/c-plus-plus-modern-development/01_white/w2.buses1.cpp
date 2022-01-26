#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void do_it(){
    vector<string> result;
    map<string,vector<string>> stops_by_bus;
    map<string,vector<string>> buses_by_stop;

    int commands_count;
    cin >> commands_count;
    for(int command_index = 0; command_index < commands_count; ++command_index){
        string command;
        cin >> command;
        if(command == "NEW_BUS"){
            string bus;
            int stops_count;
            cin >> bus >> stops_count;
            vector<string>& stops = stops_by_bus[bus];
            for(int stop_index = 0; stop_index < stops_count; stop_index++){
                string stop;
                cin >> stop;
                stops.push_back(stop);
                buses_by_stop[stop].push_back(bus);
            }
        }
        else if(command == "BUSES_FOR_STOP"){
            string stop;
            cin >> stop;
            if(buses_by_stop.count(stop) == 0){
                result.push_back("No stop");
            }
            else{
                vector<string>& buses = buses_by_stop[stop];
                string r="";
                for(string& bus: buses){
                    if(r.size() != 0){
                        r+=" ";
                    }

                    r+=bus;
                }
                result.push_back(r);
            }
        }
        else if(command == "STOPS_FOR_BUS"){
            string b;
            cin >> b;
            if(stops_by_bus.count(b) == 0){
                result.push_back("No bus");
            }
            else
            {
                vector<string>& stops = stops_by_bus[b];
                for(auto& stop: stops){
                    string r = "Stop "+stop+":";
                    vector<string>& buses = buses_by_stop[stop];
                    if(buses.size() <= 1){
                        r+= " no interchange";
                    }
                    else{
                        for(string& bus: buses){
                            if(bus == b){
                                continue;
                            }

                            r+=" ";
                            r+= bus;
                        }
                    }
                    result.push_back(r);
                }
            }
        }
        else if(command == "ALL_BUSES"){
            if(stops_by_bus.size() == 0){
                result.push_back("No buses");
            }
            else{
                for(auto& item: stops_by_bus){
                    string bus = item.first;
                    string r = "Bus "+bus+":";
                    vector<string> stops = item.second;
                    for(auto& stop: stops){
                        r+=" ";
                        r+= stop;
                    }

                    result.push_back(r);
                }
            }
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