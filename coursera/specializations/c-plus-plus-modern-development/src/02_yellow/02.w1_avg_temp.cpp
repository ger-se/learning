#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int64_t n;
    cin >> n;
    vector<int64_t> v(n);
    int64_t v_min = 0;
    for(int index = 0; index < n; ++index){
        int value;
        cin >> value;
        v[index] = value;
        if(value <= v_min){
            v_min = value;
        }
    }

    int64_t avg = 0;
    for(auto i:v){
        avg += (i - v_min);
    }

    avg = v_min + avg/n;
    vector<int> indexes;
    for(int index = 0; index < v.size(); index++){
        if(v[index] > avg){
            indexes.push_back(index);
        }
    }

    cout << indexes.size() << endl;
    if(indexes.size() > 0){
        for(auto index:indexes){
            cout << index << " "; 
        }
    }

    cout << endl;
    return 0;
}