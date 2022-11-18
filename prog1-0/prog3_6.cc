#include<iostream>
#include<string>

using namespace std;

int main() {
    string a = "abcdefg";
    for (auto &charA : a) {
        charA = 'X';
    }
    cout<<a<<endl;
    return 0;
}