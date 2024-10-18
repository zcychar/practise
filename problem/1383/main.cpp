#include <iostream>
#include<string>
#include<map>
#include<set>
#include<vector>

struct Activity {
    std::string str;
    int avg,level;
}activity;

std::map<std::string, std::vector<int>> m;
std::set<activity> s;
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
