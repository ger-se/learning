#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

void do_it(){
    map<string, int> count_by_word;
    set<set<string>> synonims;
    vector<string> result;
    int commands_count;
    cin >> commands_count;
    for(int command_index = 0; command_index < commands_count; ++command_index){
        string command;
        cin >> command;
        if(command == "ADD"){
            string word1, word2;
            cin >> word1 >> word2;
            set<string> words = {word1, word2};
            if(synonims.count(words) == 0){
                synonims.insert(words);
                count_by_word[word1]++;
                count_by_word[word2]++;
            }
        }
        else if(command == "COUNT"){
            string word;
            cin >> word;
            int count = count_by_word[word];
            result.push_back(std::to_string(count));
        }
        else if(command == "CHECK"){
            string word1, word2;
            cin >> word1 >> word2;
            set<string> words = {word1, word2};
            if(synonims.count(words) == 0){
                result.push_back("NO");
            }
            else{
                result.push_back("YES");
            }
        }
    }

    for(auto s: result){
        cout << s << endl;
    }
}

int main()
{
    // bool is_test = false;
    //auto commands = read();
    do_it();

    return 0;
}