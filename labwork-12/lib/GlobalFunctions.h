#pragma once

#include <iostream>
#include <vector>

static void CheckQuestionMark(std::string& word) {
    if (word[0] == ' ') {
        word.erase(0, 1);
    }
    if (word[word.size() - 1] == ' ') {
        word.pop_back();
    }
    if (word.find('"') != std::string::npos) {
        word.erase(0, 1);
        word.pop_back();
    }
}

static void DeleteSpace(std::vector<std::string>& values) {
    for (int i = 0; i < values.size(); i++) {
        if (values[i][0] == ' ') {
            values[i].erase(0, 1);
        }
        if (values[i][0] == '"') {
            values[i].erase(0, 1);
            values[i].pop_back();
        }
    }
}


static void Split(std::string& request, char element, std::vector<std::string>& result) {
    std::string str = "";
    for (char c : request) {
        if (c == element) {
            if (!str.empty()) {
                result.push_back(str);
                str = "";
            }
        } else if (c == ' ' && str.empty()) {
            continue;
        } else {
            str += c;
        }
    }
    if (!str.empty()) {
        str.pop_back();
        result.push_back(str);
    }
}

static void SpaceDelete(std::string& request) {
    for (int i = 0; i < request.size(); i++) {
        if (request[i] == ' ') {
            request.erase(i, 1);
        }
    }
}

