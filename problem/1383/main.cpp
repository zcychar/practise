#include <iostream>
#include<string>
#include<map>
#include<set>
#include<vector>

struct Activity {
    std::string str;
    int avg, level;
    bool operator<(const Activity& other)const {
        if(this->avg!=other.avg)return this->avg>other.avg;
        if(this->level!=other.level)return this->level<other.level;
        return this->str<other.str;
    }
} activity;

std::map<std::string, std::vector<int> > m;
std::set<Activity> s;

std::string str;

void Mapopt() {
    std::string opt;
    std::cin >> opt;
    switch (opt[0]) {
        case 's': {
            std::cout << m.size() << "\n";
            break;
        }
        case 'i': {
            std::string name;
            if (m.find(name) != m.end()) {
                std::cout << "Error\n";
                return;
            }
            int num, tmp;
            std::vector<int> arg;
            std::cin >> name >> num;
            for (int i = 1; i <= num; ++i) {
                std::cin >> tmp;
                arg.push_back(tmp);
            }
            m.insert(std::pair<std::string, std::vector<int> >(name, arg));
            break;
        }
        case 'e': {
            std::string name;
            std::cin >> name;
            if (m.find(name) == m.end()) {
                std::cout << "Error\n";
                return;
            }
            m.erase(name);
            break;
        }
        case 'c': {
            std::string name;
            std::cin >> name;
            auto it = m.find(name);
            if (it == m.end()) {
                std::cout << "0\n";
            } else {
                std::cout << m.count(name)<< "\n";
            }
            break;
        }
        case 't': {
            for (auto it = m.begin(); it != m.end(); it++) {
                std::cout << it->first << " ";
                for (auto sig: it->second) {
                    std::cout << sig << " ";
                }
                std::cout << "\n";
            }
            break;
        }
        case 'a': {
            std::string name;
            int element;
            std::cin >> name >> element;
            auto it = m.find(name);
            if (it == m.end()) {
                std::cout << "Error\n";
                return;
            }
            it->second.push_back(element);
            break;
        }
        default: {
            if (opt[5] == 'V') {
                std::string name;
                int index;
                std::cin >> name >> index;
                auto it = m.find(name);
                if (it == m.end()) {
                    std::cout << "Error\n";
                    return;
                }
                if (index > it->second.size()) {
                    std::cout << "Error\n";
                    return;
                }
                std::cout << it->second[index] << "\n";
            } else {
                std::string name;
                std::cin >> name;
                auto it = m.find(name);
                if (it == m.end()) {
                    std::cout << "Error\n";
                    return;
                }
                std::cout << it->second.size() << " ";
                for (auto sig: it->second) {
                    std::cout << sig << " ";
                }
                std::cout << "\n";
            }
            break;
        }
    }
}

void Setopt() {
    std::string opt;
    std::cin >> opt;
    switch (opt[0]) {
        case 's': {
            std::cout << s.size() << "\n";
            break;
        }
        case 'i': {
            std::string name;
            int avg, level;
            std::cin >> avg >> level >> name;
            if (!s.insert(Activity(name, avg, level)).second) {
                std::cout << "Error\n";
            }
            break;
        }
        case 'e': {
            std::string name;
            int avg, level;
            std::cin >> avg >> level >> name;
            auto it=s.find(Activity(name,avg,level));
            if(it==s.end()) {
                std::cout<<"Error\n";
                return;
            }
            s.erase(it);
            break;
        }
        case 'c': {
            std::string name;
            int avg, level;
            std::cin >> avg >> level >> name;
            std::cout<<s.count(Activity(name,avg,level))<<"\n";
            break;
        }
        case 't': {
            for(auto it:s) {
                std::cout<<it.avg<<" "<<it.level<<" "<<it.str<<"\n";
            }
            break;
        }
        default: {
            break;
        }
    }
};

int main() {
    while (std::cin >> str) {
        switch (str[0]) {
            case 'm': {
                Mapopt();
                break;
            }
            case 's': {
                Setopt();
                break;
            }
            default: {
                return 0;
            }
        }
    }
    return 0;
}
