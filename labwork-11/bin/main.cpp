#include <iostream>

#include <vector>
#include "../lib/StandardAlgorithm.h"
#include "../lib/XrangeClass.h"
#include "../lib/ZipClass.h"
class cat{
public:
    int age;
    std::string name;
    cat(int age_, std::string name_) {
        age = age_;
        name = name_;
    }
};
class pair{
    cat cats[2];
};
int main() {
    std::vector<cat> male;
    std::vector<cat> female;
    cat c(5,"btbtr");
    for(int i = 0; i < 10; i++) {
        male.push_back(c);
        female.push_back(c);
    }
    ZipClass x(male, female);
    std::vector<std::pair<cat,cat>> q(x.begin(),x.end());
    std::cout << q.size() << "\n";
    for(int i = 0; i < 10; i++) {
        std::cout << q[i].first.name <<" " <<  q[i].second.name << "\n";
    }
    return 0;
}
