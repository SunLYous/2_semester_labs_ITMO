#include "ControllerClass.h"

void ControllerClass::Run(const std::string& file_name) noexcept {
    config = file_name;
    nlohmann::json json = nlohmann::json::parse(std::ifstream(file_name));
    if (user_day_ == 0)
        user_day_ = json["day"];
    update_ = json["update"];
    for (const auto& i : json["city"]) {
        SearchCoordinatesCity(i);
    }
    UpdateWeatherInformation();
}

void ControllerClass::SearchCoordinatesCity(const std::string& city) noexcept {
    cpr::Response information = cpr::Get(
            cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + city},
            cpr::Header{{"X-api-key", "8nXOjukAgLCpu7xr4P/+oQ==3EPmWxxId9mAe9EB"}});
    City coordinates;
    if (information.status_code == 0 || information.status_code == 400) {
        coordinates.latitude_ = 0;
        coordinates.longitude_ = 0;
        coordinates.name_ = city;
        coordinates.status_code_ = 400;
    } else {
        nlohmann::json json = nlohmann::json::parse(information.text);
        coordinates.latitude_ = json[0]["latitude"];
        coordinates.longitude_ = json[0]["longitude"];
        coordinates.name_ = city;
        coordinates.status_code_ = information.status_code;
    }
    SearchCity(coordinates);
}

void ControllerClass::SearchCity(const City& coordinates) noexcept {
    if (coordinates.status_code_ == 200) {
        cpr::Response weather_information = cpr::Get(cpr::Url{
                "https://api.open-meteo.com/v1/forecast?latitude=" +
                        std::to_string(coordinates.latitude_) +
                        "&longitude=" + std::to_string(coordinates.longitude_) +
                        "&hourly=temperature_2m,apparent_temperature,precipitation,weathercode,"
                        "windspeed_10m,winddirection_10m&forecast_days=16"
        });
        nlohmann::json json = nlohmann::json::parse(weather_information.text);
        ParseWeatherInformation(json);
    }
    auto* meteo_information = new ModelClass(coordinates, days_information);
    days_information.clear();
    meteo_information->SetUserDays(user_day_);
    cities.push_back(meteo_information);
}

void ControllerClass::ParseWeatherInformation(
        const nlohmann::json& json) noexcept {
    std::vector<Hour> hours;
    int count = 0;
    for (int i = 2; i < days_ * hours_; i = i + 6) {
        Hour hour;
        hour.hour_ = json["hourly"]["time"][i];
        hour.temperature_ = json["hourly"]["temperature_2m"][i];
        hour.weather_code_ = json["hourly"]["weathercode"][i];
        hour.weather_description_ = weather_codes[hour.weather_code_];
        hour.wind_speed_ = json["hourly"]["windspeed_10m"][i];
        hour.precipitation_amount_ = json["hourly"]["precipitation"][i];
        hour.apparent_temperature_ = json["hourly"]["apparent_temperature"][i];
        hours.push_back(hour);
        count++;
        if (count == 4) {
            Day day;
            day.day_ = json["hourly"]["time"][i];
            day.hours_ = hours;
            days_information.push_back(day);
            hours.clear();
            count = 0;
        }
    }
}

ControllerClass::~ControllerClass() {
    for (auto& citie : cities) {
        delete citie;
    }
}

[[maybe_unused]] void ControllerClass::PrintWeatherInformation() {
    for (auto& citie : cities) {
        std::cout << citie->GetCoordinates().name_ << "\n";
        for (int j = 0; j < citie->GetDaysSize(); j++) {

            for (auto& hour : citie->GetDay(j).hours_) {
                std::cout << hour.hour_ << " ";
                std::cout << hour.temperature_ << " ";
                std::cout << hour.weather_code_ << "\n";
            }
        }
    }
}

void ControllerClass::CheckKey(ViewClass& view, int& city) noexcept {
    const int key = getch();
    if (key == 'q') {
        exit(0);
    }
    if (key == '=') {
        if (user_day_ < 16) {
            user_day_++;
            std::cout << user_day_ << std::endl;
            for (auto& town : cities) {
                town->SetUserDays(user_day_);
            }
            system("cls");
            view.PrintWeatherInformation(cities[city]);
        }
    }
    if (key == '-') {
        if (user_day_ > 1) {
            user_day_--;
            for (auto& town : cities) {
                town->SetUserDays(user_day_);
            }
            system("cls");
            view.PrintWeatherInformation(cities[city]);
        }
    }
    if (key == 'n') {
        if (city < cities.size() - 1) {
            city++;
            system("cls");
            view.PrintWeatherInformation(cities[city]);
        }
    }
    if (key == 'p') {
        if (city > 0) {
            city--;
            system("cls");
            view.PrintWeatherInformation(cities[city]);
        }
    }
}

void ControllerClass::UpdateWeatherInformation() noexcept {
    ViewClass view;
    auto start = std::chrono::system_clock::now();
    view.PrintWeatherInformation(cities[last_city_]);
    while (true) {
        auto end = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() >=
                update_) {
            system("cls");
            Run(config);
        }
        CheckKey(view, last_city_);
    }
}