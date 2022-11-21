#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

void elimDups(vector<string> &s) {
    sort(s.begin(), s.end());
    auto endUnique = unique(s.begin(), s.end());
    s.erase(endUnique, s.end());
}

void printBigger(vector<string> &s, int len) {
    elimDups(s);
    stable_sort(s.begin(), s.end(),
     [](const string &str1, const string &str2) -> bool {return str1.size() < str2.size();});
    auto firLarIt = find_if(s.begin(), s.end(), [len](string &str) -> bool {return str.size() > len;});
    for_each(firLarIt, s.end(), [](const string &str){cout<<str<<" ";});
}

int main() {
    vector<string> s = {"prog3", "proge", "proga", "vsc", "std", "notThis"};
    printBigger(s, 2);
    return 0;
}