#include<iostream>
#include<vector>

using namespace std;

int main() {
    vector<int> a = {1, 2, 3}, b = {4, 5, 6};
    auto begin = a.cbegin(), end = a.cend();
    a.swap(b);
    while (begin != end) {
        cout<<*begin++<<"\t";
    }
    cout<<endl;
    for (auto iter = a.cbegin(); iter != a.cend(); ++iter) {
        cout<<*iter<<"\t";
    }
    return 0;
}