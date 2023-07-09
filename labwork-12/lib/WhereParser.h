#pragma once

#include "Table.h"
#include "AbstractValueType.h"
#include "GlobalFunctions.h"

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <memory>

enum class Command {
    delete_,
    update,
    select
};

struct Operation {
    std::string column_name_;
    std::string operation_;
    std::string value_;

    Operation() = default;
};

class WhereParser {
private:
    std::vector<std::vector<std::string>> result_;

    void ParseOperation(std::string& request);

    void CheckingForSuitableLines(std::vector<int>& number_lines, Table* table);

    Operation ParseLogisticOperation(std::string& request);

    void ParseDelete(std::string& request, Table* table);

    void ParseUpdate(std::string& request, Table* table);

    void ParseSelect(std::string& request, Table* table);

    bool CheckOperation(const Operation& operation, int row, Table* table);

    bool CallAcceptType(int number_type, const Operation& operation, int row, Table* table);

    bool CallAcceptLessType(int number_type, const Operation& operation, int row, Table* table);

    bool CallAcceptMoreType(int number_type, const Operation& operation, int row, Table* table);

    void UpdateCell(int number_type, const std::string& column_name, int row, Table* table, const std::string& value);

public:
    WhereParser(std::string& request, Table* table, size_t command);

};
