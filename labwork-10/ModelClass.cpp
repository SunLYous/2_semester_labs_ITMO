#include "ModelClass.h"

ModelClass::ModelClass(const City& coordinates, const std::vector<Day>& days) {
    coordinates_ = coordinates;
    days_ = days;
}

Day& ModelClass::GetDay(int day) { return days_[day]; }

City& ModelClass::GetCoordinates() { return coordinates_; }

int ModelClass::GetUserDays() { return user_days_; }

void ModelClass::SetUserDays(int user_days) {
    if (user_days > 0 && user_days < 16)
        user_days_ = user_days;
    else
        user_days_ = 16;
}

int ModelClass::GetDaysSize() {
    return days_.size();
}

const Day& ModelClass::GetDay(int day) const {
    return days_[day];
}

const City& ModelClass::GetCoordinates() const {
    return coordinates_;
}

const int ModelClass::GetUserDays() const {
    return user_days_;
}

ModelClass::~ModelClass() = default;
