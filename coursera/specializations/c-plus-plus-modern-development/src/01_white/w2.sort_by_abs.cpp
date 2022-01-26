#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void do_it(){
    int size;
    cin >> size;
    vector<string> A(size);
    for(auto& a: A){
        cin >> a;
    }

    std::sort(begin(A),end(A),
        [](int first, int second){
            return tolower(first) < tolower(second);
        });

    for(auto& a: A){
        cout << a << " ";
    }

    cout << endl;
}

int main()
{
    // bool is_test = false;
    //auto commands = read();
    do_it();

    return 0;
}