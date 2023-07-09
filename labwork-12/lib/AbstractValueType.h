#pragma once

#include <iostream>
#include <vector>
#include <cmath>

class AbstractValueType {
protected:
    enum TypeValue {
        INTEGER,
        DOUBLE,
        FLOAT,
        BOOLEAN,
        NULL_,
        VARCHAR
    };
public:
    bool is_null_ = false;

    virtual TypeValue Type() = 0;

    virtual void PutInColumn(std::string& output) = 0;

    virtual bool Accept(class Visitor* visitor, std::string string_value) = 0;

    virtual bool AcceptLess(class Visitor* visitor, std::string string_value) = 0;

    virtual bool AcceptMore(class Visitor* visitor, std::string string_value) = 0;

    virtual void UpdateValue(class Visitor* visitor, std::string string_value) = 0;

    ~AbstractValueType() = default;

    AbstractValueType() = default;
};

class VarcharValue : public AbstractValueType {
public:
    TypeValue Type() override;

    void PutInColumn(std::string& output) override;

    std::string value_;

    bool Accept(class Visitor* visitor, std::string string_value) override;

    bool AcceptLess(class Visitor* visitor, std::string string_value) override;

    bool AcceptMore(class Visitor* visitor, std::string string_value) override;

    void UpdateValue(class Visitor* visitor, std::string string_value) override;

    explicit VarcharValue(std::string value);

    ~VarcharValue() = default;
};

class IntegerValue : public AbstractValueType {
public:
    int value_;

    void PutInColumn(std::string& output) override;

    bool Accept(class Visitor* visitor, std::string string_value) override;

    bool AcceptLess(class Visitor* visitor, std::string string_value) override;

    bool AcceptMore(class Visitor* visitor, std::string string_value) override;

    void UpdateValue(class Visitor* visitor, std::string string_value) override;

    TypeValue Type() override;

    explicit IntegerValue(int value);

    ~IntegerValue() = default;
};

class DoubleValue : public AbstractValueType {
public:
    double value_;

    void PutInColumn(std::string& output) override;

    bool Accept(class Visitor* visitor, std::string string_value) override;

    bool AcceptLess(class Visitor* visitor, std::string string_value) override;

    bool AcceptMore(class Visitor* visitor, std::string string_value) override;

    void UpdateValue(class Visitor* visitor, std::string string_value) override;

    explicit DoubleValue(double value);

    TypeValue Type() override;

    ~DoubleValue() = default;
};

class FloatValue : public AbstractValueType {
public:
    void PutInColumn(std::string& output) override;

    bool Accept(class Visitor* visitor, std::string string_value) override;

    bool AcceptLess(class Visitor* visitor, std::string string_value) override;

    bool AcceptMore(class Visitor* visitor, std::string string_value) override;

    void UpdateValue(class Visitor* visitor, std::string string_value) override;

    float value_;

    TypeValue Type() override;


    explicit FloatValue(float value);

    FloatValue() = default;

    ~FloatValue() = default;
};

class BooleanValue : public AbstractValueType {
public:
    bool value_;

    void PutInColumn(std::string& output) override;

    bool Accept(class Visitor* visitor, std::string string_value) override;

    bool AcceptLess(class Visitor* visitor, std::string string_value) override;

    bool AcceptMore(class Visitor* visitor, std::string string_value) override;

    void UpdateValue(class Visitor* visitor, std::string string_value) override;

    TypeValue Type() override;

    explicit BooleanValue(bool value);

    ~BooleanValue() = default;
};

class NullValue : public AbstractValueType {
public:
    std::string value = "null";

    void PutInColumn(std::string& output) override;

    bool Accept(class Visitor* visitor, std::string string_value) override { return false; }

    bool AcceptLess(class Visitor* visitor, std::string string_value) override { return false; }

    bool AcceptMore(class Visitor* visitor, std::string string_value) override { return false; }

    void UpdateValue(class Visitor* visitor, std::string string_value) override { return; }


    TypeValue Type() override;

    NullValue();

    ~NullValue() = default;
};


class Visitor {
public:
    virtual bool Compare(std::string& string_value, const IntegerValue* value) { return false; }

    virtual bool Compare(std::string& string_value, const DoubleValue* value) { return false; }

    virtual bool Compare(std::string& string_value, const VarcharValue* value) { return false; }

    virtual bool Compare(std::string& string_value, const BooleanValue* value) { return false; }

    virtual bool Compare(std::string& string_value, const FloatValue* value) { return false; }

    virtual bool CompareLess(std::string& string_value, const IntegerValue* value) { return false; }

    virtual bool CompareLess(std::string& string_value, const DoubleValue* value) { return false; }

    virtual bool CompareLess(std::string& string_value, const VarcharValue* value) { return false; }

    virtual bool CompareLess(std::string& string_value, const BooleanValue* value) { return false; }

    virtual bool CompareLess(std::string& string_value, const FloatValue* value) { return false; }

    virtual bool CompareMore(std::string& string_value, const IntegerValue* value) { return false; }

    virtual bool CompareMore(std::string& string_value, const DoubleValue* value) { return false; }

    virtual bool CompareMore(std::string& string_value, const VarcharValue* value) { return false; }

    virtual bool CompareMore(std::string& string_value, const BooleanValue* value) { return false; }

    virtual bool CompareMore(std::string& string_value, const FloatValue* value) { return false; }

   virtual void Update(std::string& string_value, IntegerValue* value) { return; }

   virtual void Update(std::string& string_value, DoubleValue* value) { return; }

   virtual void Update(std::string& string_value, VarcharValue* value) { return; }

   virtual void Update(std::string& string_value, BooleanValue* value) { return; }

    virtual void Update(std::string& string_value, FloatValue* value) { return; }

    Visitor() = default;
};


class VisitorInteger : public Visitor {
public:
    bool Compare(std::string& string_value, const IntegerValue* value) override;

    bool CompareLess(std::string& string_value, const IntegerValue* value) override;

    bool CompareMore(std::string& string_value, const IntegerValue* value) override;

    void Update(std::string& string_value, IntegerValue* value) override;

    VisitorInteger() = default;
};

class VisitorDouble : public Visitor {
public:


    bool Compare(std::string& string_value, const DoubleValue* value) override;

    bool CompareLess(std::string& string_value, const DoubleValue* value) override;

    bool CompareMore(std::string& string_value, const DoubleValue* value) override;

    void Update(std::string& string_value, DoubleValue* value) override;
};

class VisitorVarchar : public Visitor {
public:

    bool Compare(std::string& string_value, const VarcharValue* value) override;

   void Update(std::string& string_value, VarcharValue* value) override;

};

class VisitorBoolean : public Visitor {
protected:


    bool Compare(std::string& string_value, const BooleanValue* value) override;

    void Update(std::string& string_value, BooleanValue* value) override;


};

class VisitorFloat : public Visitor {
protected:

    bool Compare(std::string& string_value, const FloatValue* value) override;

    bool CompareLess(std::string& string_value, const FloatValue* value) override;

    bool CompareMore(std::string& string_value, const FloatValue* value) override;

    void Update(std::string& string_value, FloatValue* value) override;
};
