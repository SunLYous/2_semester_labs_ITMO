#pragma once

#include "CreateTableRequest.h"

#include <iostream>
#include <vector>

class SQLClass {
private:
    CreateTableRequest create;
    std::vector<Table*> tables_;
    std::vector<std::string> requests_; // requests

    void SearchRequest(std::string& request); // ищет запрос
    void DivisionIntoRequests(std::string& request);

    std::string DeleteSpace(std::string& request);
public:
    SQLClass() = default;

    size_t GetSizeTable(const std::string& table_name);

    void ParsingRequest(std::string& request); // начальная функция, в которую передается запрос

    ~SQLClass();
};
