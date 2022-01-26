#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    int n, m;
    input >> n;
    input.ignore(1);
    input >> m;
    input.ignore(1);

    for(int row = 0; row < n; ++row){
        for(int col = 0; col < m; ++col){
            int value;
            input >> value;
            input.ignore(1);

            cout << right;
            cout << setw(10);
            // cout << setfill(' ');

            cout << value;
            if(col < (m-1))
            {
                cout << ' ';
            }
        }

        if(row < (n-1)){
            cout << endl;
        }
    }

    return 0;
}