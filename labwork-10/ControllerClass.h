#ifndef LABWORK_10_SUNLYOUS__CONTROLLERCLASS_H_
#define LABWORK_10_SUNLYOUS__CONTROLLERCLASS_H_

#include "ModelClass.h"
#include "ViewClass.h"
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class ControllerClass {
private:
    int last_city_ = 0;
    std::string config;
    const int days_ = 16;
    const int hours_ = 24;
    int user_day_ = 0;
    int update_ = 300000000;
    std::vector<Day> days_information;
    std::vector<ModelClass*> cities;
    std::unordered_map<int, std::string> weather_codes = {
            {0, "Clear sky"},
            {1, "Mainly clear"},
            {2, "Partly cloudy"},
            {3, "Overcast"},
            {45, "Fog and depositing rime fog"},
            {51, "Drizzle: Light intensity"},
            {53, "Drizzle: Moderate intensity"},
            {55, "Drizzle: Dense intensity"},
            {56, "Freezing Drizzle: Light intensity"},
            {57, "Freezing Drizzle: Dense intensity"},
            {61, "Rain: Slight intensity"},
            {63, "Rain: Moderate intensity"},
            {65, "Rain: Heavy intensity"},
            {66, "Freezing Rain: Light intensity"},
            {67, "Freezing Rain: Heavy intensity"},
            {71, "Snow fall: Slight intensity"},
            {73, "Snow fall: Moderate intensity"},
            {75, "Snow fall: Heavy intensity"},
            {77, "Snow grains"},
            {80, "Rain showers: Slight intensity"},
            {81, "Rain showers: Moderate intensity"},
            {82, "Rain showers: Violent intensity"},
            {85, "Snow showers: Slight intensity"},
            {86, "Snow showers: Heavy intensity"},
            {95, "Thunderstorm: Slight or moderate"},
            {96, "Thunderstorm with slight hail"},
            {99, "Thunderstorm with heavy hail"}};

    void SearchCity(const City& coordinates) noexcept;

    void ParseWeatherInformation(const nlohmann::json& json) noexcept;

    [[maybe_unused]] void PrintWeatherInformation();

    void SearchCoordinatesCity(const std::string& city) noexcept;

    void CheckKey(ViewClass& view, int& city) noexcept;

    [[noreturn]] void UpdateWeatherInformation() noexcept;

public:
    ControllerClass() = default;

    ~ControllerClass();

    void Run(const std::string& file_name) noexcept;
};

#endif // LABWORK_10_SUNLYOUS__MODELCLASS_H_
