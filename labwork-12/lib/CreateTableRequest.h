#pragma once

#include "AbstractValueType.h"
#include "WhereParser.h"
#include "Table.h"
#include "GlobalFunctions.h"

#include <iostream>
#include <vector>
#include <regex>

class CreateTableRequest {
private:
    bool mistake_ = false;

    std::vector<std::string> ParseValue(std::string request); // парсит значения
    void ParseValueByType(std::string& value_for_type_checking, Table* table, int j); // парсит значения по типу
    void CheckType(std::string& column_type, std::string& column_name, Table* table); // проверяет тип данных
    void CheckPrimaryAndForeignKey(std::string& request,
                                   Table* table,
                                   std::string& column_name); // проверяет наличие первичного и внешнего ключа
    void CheckNotNull(std::string& request, Table* table, std::string& column_name);

public:
    Table* ParserCreateRequest(std::string request); // должна разбирать запрос и возвращать указатель на таблицу

    void AddElementToTable(Table* table, const std::string& request); // добавляет новую строку в таблицу

    void DeleteLineOfTheTable(std::string& request, Table* table); // удаляет строку из таблицы

    void UpdateInformationInTable(std::string& request, Table* table); // изменяет информацию в таблице

    void SelectInformationFromTable(std::string& request, Table* table); // выбирает информацию из таблицы

    void JoinTable(std::string& request, Table* left_table, Table* right_table); // объединяет таблицы

    CreateTableRequest() = default;
    ~CreateTableRequest() = default;

};