#ifndef LABWORK_10_SUNLYOUS__MODELCLASS_H_
#define LABWORK_10_SUNLYOUS__MODELCLASS_H_

#include <iostream>
#include <string>
#include <vector>

struct Hour {
    std::string hour_;
    int temperature_;
    int apparent_temperature_;
    int weather_code_;
    std::string weather_description_;
    int wind_speed_;
    double precipitation_amount_;
};

struct Day {
    std::string day_;
    std::vector<Hour> hours_;
};

struct City {
    std::string name_;
    double latitude_;
    double longitude_;
    int status_code_;
};

class ModelClass {
private:
    City coordinates_;
    std::vector<Day> days_;
    int user_days_;

public:
    Day& GetDay(int day);

    int GetDaysSize();

    const Day& GetDay(int day) const;

    const City& GetCoordinates() const;

    const int GetUserDays() const;

    City& GetCoordinates();

    int GetUserDays();

    void SetUserDays(int user_days);

    ModelClass(const City& coordinates, const std::vector<Day>& days);

    ~ModelClass();
};

#endif // LABWORK_10_SUNLYOUS__MODELCLASS_H_
