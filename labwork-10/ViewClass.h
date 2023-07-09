#ifndef LABWORK_10_SUNLYOUS__VIEWCLASS_H_
#define LABWORK_10_SUNLYOUS__VIEWCLASS_H_

#include "ModelClass.h"
#include "nlohmann/json.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/box.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/terminal.hpp>

#include <iostream>
#include <string>
#include <vector>

class ViewClass {
public:
    void PrintWeatherInformation(const ModelClass* model);

    ~ViewClass() = default;

private:
    static ftxui::Element VboxDayTime(std::string day_time, const ModelClass* model,
                               int day, int hour) noexcept;

    static ftxui::Element VboxPicture(int weather_code) noexcept;
};

#endif // LABWORK_10_SUNLYOUS__VIEWCLASS_H_
