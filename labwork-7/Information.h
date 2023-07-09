#ifndef LABWORK_7_SUNLYOUS__INFORMATION_H_
#define LABWORK_7_SUNLYOUS__INFORMATION_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Information {
private:
    std::unordered_map<std::string, std::vector<std::string>> mp3;
public:
    std::vector<std::string> getInfoFrame(const std::string& frame);
    void CheckFrame (const std::string& name);
    ~Information() = default;
    void AddFrame(const std::string& frame_name, const std::string& text);
    void PrintAll();
    void ParseJson();
    std::vector<std::string> FullNameTag();
};

#endif //LABWORK_7_SUNLYOUS__INFORMATION_H_
