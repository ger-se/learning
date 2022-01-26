#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
}

class TimeServer {
public:
    string GetCurrentTime() {
        try
        {
            string fetched = AskTimeServer();
            last_fetched_time = fetched;
            return fetched;   
        }
        catch(const std::system_error& e)
        {
            return last_fetched_time;
        }
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}