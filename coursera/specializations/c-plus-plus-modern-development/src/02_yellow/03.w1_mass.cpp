#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    uint64_t n, r;
    cin >> n >> r;

    uint64_t v = 0;
    for(int index = 0; index < n; ++index){
        uint64_t w, h, d;
        cin >> w >> h >> d;
        v += w*h*d;
    }

    uint64_t m = v*r;

    cout << m << endl;
    return 0;
}