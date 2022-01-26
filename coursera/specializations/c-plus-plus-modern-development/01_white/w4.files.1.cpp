#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    if(input.is_open()){
        string line;
        while (getline(input, line))
        {
            cout << line << endl;
        }
    }

    return 0;
}