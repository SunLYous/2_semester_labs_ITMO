#ifndef LABWORK_12_SUNLYOUS_LIB_TABLE_H_
#define LABWORK_12_SUNLYOUS_LIB_TABLE_H_

#include "AbstractValueType.h"

#include <iostream>
#include <vector>
#include "unordered_map"

struct ForeignKey {
    std::string foreign_table_name_ = " ";
    std::string column_name_ = " ";
    std::string foreign_column_name_ = " ";
    ForeignKey() = default;
};

class Table {
private:
    friend class CreateTableRequest; // ParserCreateRequest
    friend class WhereParser; // WhereParser
    std::vector<std::pair<std::string, size_t>> column_types_; // name, type
    std::string primary_key_ = " ";
    std::unordered_map<std::string, std::vector<AbstractValueType*>> table_; // name, value
    std::string table_name_; // name
    std::unordered_map<std::string, bool> null;
    bool not_null = false;
    size_t size_table_ = 0;
    ForeignKey foreign_key_ = ForeignKey();
    void DeleteTable();
public:
    void DeleteRow(size_t row);
    std::pair<std::string, size_t> GetTypeColumn(size_t column);
    size_t GetSizeTable(); // size_table
    std::string GetTableName(); // name
    void PrintTable(); // выводит таблицу
    void PrintTable(const std::vector<std::string>& column_names); // выводит таблицу
    size_t GetSizeColumn(std::string column_name); // возвращает размер столбца
    ~Table();
};

#endif //LABWORK_12_SUNLYOUS_LIB_TABLE_H_
