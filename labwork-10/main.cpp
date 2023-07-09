#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ControllerClass.h"
#include "ViewClass.h"
#include "cpr/cpr.h"
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include <windows.h>

int main() {
    ControllerClass model;
    std::string city = "w.json";
    std::ifstream file(city);

    model.Run(city);
    /*nlohmann::json json = nlohmann::json::parse(std::ifstream("w.json"));
    std::cout<<json["city"];*/
}
