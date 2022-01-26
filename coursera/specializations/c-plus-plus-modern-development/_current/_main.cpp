#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input_1("input.txt");
    if(input_1.is_open()){
        string line;
        while (getline(input_1, line))
        {
            cout << line << endl;
        }
    }

    ifstream

    double a;

    cout << fixed << setprecision(3);

    while (input >> a) {
        cout << a << endl;
    }

    return 0;
}