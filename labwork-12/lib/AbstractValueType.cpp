#include "AbstractValueType.h"

VarcharValue::VarcharValue(std::string value)
        : value_(value) {}

AbstractValueType::TypeValue VarcharValue::Type() {
    return AbstractValueType::VARCHAR;
}

void VarcharValue::PutInColumn(std::string& output) {
    output += " " + value_;
}

bool VarcharValue::Accept(class Visitor* visitor, std::string string_value) {
    return visitor->Compare(string_value, this);
}

bool VarcharValue::AcceptLess(struct Visitor* visitor, std::string string_value) {
    return visitor->CompareLess(string_value, this);
}

bool VarcharValue::AcceptMore(struct Visitor* visitor, std::string string_value) {
  return  visitor->CompareMore(string_value, this);
}

void VarcharValue::UpdateValue(struct Visitor* visitor, std::string string_value) {
    visitor->Update(string_value, this);
}

IntegerValue::IntegerValue(int value) : value_(value) {}

AbstractValueType::TypeValue IntegerValue::Type() {
    return AbstractValueType::INTEGER;
}

void IntegerValue::PutInColumn(std::string& output) {
    output += " " + std::to_string(value_);
}

bool IntegerValue::Accept(class Visitor* visitor, std::string string_value) {
    return visitor->Compare(string_value, this);
}

bool IntegerValue::AcceptLess(struct Visitor* visitor, std::string string_value) {
    return visitor->CompareLess(string_value, this);
}

bool IntegerValue::AcceptMore(struct Visitor* visitor, std::string string_value) {
    return visitor->CompareMore(string_value, this);
}

void IntegerValue::UpdateValue(struct Visitor* visitor, std::string string_value) {
    visitor->Update(string_value, this);
}

DoubleValue::DoubleValue(double value) : value_(value) {}

AbstractValueType::TypeValue DoubleValue::Type() {
    return AbstractValueType::DOUBLE;
}

void DoubleValue::PutInColumn(std::string& output) {
    std::string temp = std::to_string(value_);
    temp = temp.substr(0, temp.find('.') + 2);
    output += " " + temp;
}

bool DoubleValue::Accept(struct Visitor* visitor, std::string string_value) {
    visitor->Compare(string_value, this);
}

bool DoubleValue::AcceptLess(struct Visitor* visitor, std::string string_value) {
    visitor->CompareLess(string_value, this);
}

bool DoubleValue::AcceptMore(struct Visitor* visitor, std::string string_value) {
    visitor->CompareMore(string_value, this);
}

void DoubleValue::UpdateValue(struct Visitor* visitor, std::string string_value) {
    visitor->Update(string_value, this);
}

FloatValue::FloatValue(float value) : value_(value) {}

AbstractValueType::TypeValue FloatValue::Type() {
    return AbstractValueType::FLOAT;
}

void FloatValue::PutInColumn(std::string& output) {
    std::string temp = std::to_string(value_);
    temp = temp.substr(0, temp.find('.') + 2);
    output += " " + temp;
}

bool FloatValue::Accept(struct Visitor* visitor, std::string string_value) {
    visitor->Compare(string_value, this);
}

bool FloatValue::AcceptLess(struct Visitor* visitor, std::string string_value) {
    visitor->CompareLess(string_value, this);
}

bool FloatValue::AcceptMore(struct Visitor* visitor, std::string string_value) {
    visitor->CompareMore(string_value, this);
}

void FloatValue::UpdateValue(struct Visitor* visitor, std::string string_value) {
    visitor->Update(string_value, this);
}

BooleanValue::BooleanValue(bool value) {
    value_ = value;
}

AbstractValueType::TypeValue BooleanValue::Type() {
    return AbstractValueType::BOOLEAN;
}

void BooleanValue::PutInColumn(std::string& output) {
    output += " " + std::to_string(value_);
}

bool BooleanValue::Accept(struct Visitor* visitor, std::string string_value) {
    visitor->Compare(string_value, this);
}

bool BooleanValue::AcceptLess(struct Visitor* visitor, std::string string_value) {
    visitor->CompareLess(string_value, this);
}

bool BooleanValue::AcceptMore(struct Visitor* visitor, std::string string_value) {
    visitor->CompareMore(string_value, this);
}

void BooleanValue::UpdateValue(struct Visitor* visitor, std::string string_value) {
    visitor->Update(string_value, this);
}

AbstractValueType::TypeValue NullValue::Type() {
    return AbstractValueType::NULL_;
}

void NullValue::PutInColumn(std::string& output) {
    output += " " + value;
}

NullValue::NullValue() {
    is_null_ = true;
}

bool VisitorInteger::Compare(std::string& string_value, const IntegerValue* value) {
    return std::stoi(string_value) == value->value_;
}

bool VisitorInteger::CompareLess(std::string& string_value, const IntegerValue* value) {
    return std::stoi(string_value) < value->value_;
}

bool VisitorInteger::CompareMore(std::string& string_value, const IntegerValue* value) {
    return std::stoi(string_value) > value->value_;
}

void VisitorInteger::Update(std::string& string_value, IntegerValue* value) {
    value->value_ = std::stoi(string_value);
}

bool VisitorDouble::CompareLess(std::string& string_value, const DoubleValue* value) {
    return std::stod(string_value.substr(0, string_value.find('.') + 2)) < value->value_;
}

bool VisitorDouble::Compare(std::string& string_value, const DoubleValue* value) {
    return std::stod(string_value.substr(0, string_value.find('.') + 2)) == value->value_;
}

bool VisitorDouble::CompareMore(std::string& string_value, const DoubleValue* value) {
    return std::stod(string_value.substr(0, string_value.find('.') + 2)) > value->value_;
}

void VisitorDouble::Update(std::string& string_value, DoubleValue* value) {
    value->value_ = std::stod(string_value.substr(0, string_value.find('.') + 2));
}

bool VisitorFloat::CompareMore(std::string& string_value, const FloatValue* value) {
    return std::stof(string_value.substr(0, string_value.find('.') + 2)) > value->value_;
}

bool VisitorFloat::CompareLess(std::string& string_value, const FloatValue* value) {
    return std::stof(string_value.substr(0, string_value.find('.') + 2)) < value->value_;
}

bool VisitorFloat::Compare(std::string& string_value, const FloatValue* value) {
    return std::stof(string_value.substr(0, string_value.find('.') + 2)) == value->value_;
}

void VisitorFloat::Update(std::string& string_value, FloatValue* value) {
    value->value_ = std::stof(string_value.substr(0, string_value.find('.') + 2));
}

bool VisitorBoolean::Compare(std::string& string_value, const BooleanValue* value) {
    if (string_value == "true" && value->value_) {
        return true;
    }
    if (string_value == "false" && !value->value_) {
        return true;
    }
    return false;
}

void VisitorBoolean::Update(std::string& string_value, BooleanValue* value) {
    if (string_value == "true") {
        value->value_ = true;
    } else {
        value->value_ = false;
    }
}

bool VisitorVarchar::Compare(std::string& string_value, const VarcharValue* value) {
    return string_value == value->value_;
}

void VisitorVarchar::Update(std::string& string_value, VarcharValue* value) {
    value->value_ = string_value;
}
