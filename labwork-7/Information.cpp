#include "Information.h"

void Information::AddFrame(const std::string& frame_name, const std::string& text) {
    if(mp3.find(frame_name) == mp3.end()) {
        std::vector<std::string> frame;
        frame.push_back(text);
        mp3.insert(std::pair<std::string, std::vector<std::string>>(frame_name, frame));
    } else {
        mp3[frame_name].push_back(text);
    }

}

void Information::PrintAll() {
    std::ofstream file;
    file.open("music.txt", std::ios::app | std::ios::out);
    for (const auto& i : mp3) {
        file << i.first << ":" << "\n";
        std::cout << i.first << ":" << "\n";
        for (const auto& j : i.second) {
            file << j << std::endl;
            std::cout << j << std::endl;
        }
    }
}

void Information::CheckFrame(const std::string& name) {std::ofstream file;
    file.open("music.txt", std::ios::app | std::ios::out);
    file << name << ":" << "\n";
    std::cout << name << ":" << "\n";
    if(mp3.find(name) != mp3.end()) {
        for (const auto& i : mp3[name]) {
            file << i << std::endl;
            std::cout << i << std::endl;
        }
    } else {
        file << "Frame not found" << std::endl;
        std::cout << "Frame not found" << std::endl;
    }
}

void Information::ParseJson() {
    std::ofstream file;
    file.open("mus.json", std::ios::app | std::ios::out);
    for(const auto& i : mp3) {
        file << "\"" << i.first << "\"" << ":" << "\n";
        file << "[\n";
        for (const auto& j : i.second) {
            file << "\"" << j << "\"" << ",\n";
        }
        file << "],\n";
    }
}

std::vector<std::string> Information::getInfoFrame(const std::string& frame) {
        return mp3[frame];
}

std::vector<std::string> Information::FullNameTag() {
    std::vector<std::string> frame;
    for(const auto& i : mp3) {
        frame.push_back(i.first);
    }
    return frame;
}
