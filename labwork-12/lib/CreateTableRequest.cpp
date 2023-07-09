#include "CreateTableRequest.h"

Table* CreateTableRequest::ParserCreateRequest(std::string request) {
    auto table = new Table();
    request.erase(0, 13); // delete "create table "
    table->table_name_ = std::string_view(request.data(), request.find('(') - 1);
    std::cout << table->table_name_ << std::endl;
    CheckQuestionMark(table->table_name_); // delete question mark
    std::string meta_data;
    meta_data = std::string_view(request.data() + request.find('(') + 1,
                                 request.rfind(')') - request.find('(') - 1); // delete "create table table_name ("
    std::vector<std::string> column_types; // column name + column type
    Split(meta_data, ',', column_types); // split column name + column type
    std::string column_name;
    std::string column_type_transformation;
    for (int i = 0; i < column_types.size(); i++) {
        column_type_transformation = column_types[i].substr(column_types[i].find(' ') + 1); // delete column name
        column_name = std::string_view(column_types[i].data(), column_types[i].find(' '));
        column_types[i].erase(0, column_name.size() + 1); // delete column name
        CheckQuestionMark(column_name); // delete question mark
        std::transform(column_type_transformation.begin(),
                       column_type_transformation.end(),
                       column_type_transformation.begin(), tolower);
        CheckType(column_type_transformation, column_name, table);
        column_types[i].erase(0, column_types[i].find(' ') + 1); // delete column type
        column_type_transformation.erase(0, column_type_transformation.find(' ') + 1);
        if (!column_type_transformation.empty()) {
            CheckPrimaryAndForeignKey(column_type_transformation, table, column_name); // check primary and foreign key
            CheckNotNull(column_type_transformation, table, column_name); // check not null
        }
    }
    if (mistake_) {
        mistake_ = false; //проверка внутри парса типов на ошибку
        return nullptr;
    }
    return table;
}

void CreateTableRequest::CheckType(std::string& column_type, std::string& column_name, Table* table) {
    if (column_type.find("integer") != std::string::npos) {
        table->column_types_.emplace_back(column_name, 0);
        CheckQuestionMark(table->column_types_.back().first);
    } else if (column_type.find("varchar") != std::string::npos) {
        unsigned int size = std::stoi(column_type.substr(8, column_type.find(')') - 8));
        table->column_types_.emplace_back(column_name, size);
        CheckQuestionMark(table->column_types_.back().first);
    } else if (column_type.find("float") != std::string::npos) {
        table->column_types_.emplace_back(column_name, 2);
        CheckQuestionMark(table->column_types_.back().first);
    } else if (column_type.find("double") != std::string::npos) {
        table->column_types_.emplace_back(column_name, 1);
        CheckQuestionMark(table->column_types_.back().first);
    } else if (column_type.find("bool") != std::string::npos) {
        table->column_types_.emplace_back(column_name, 3);
        CheckQuestionMark(table->column_types_.back().first);
    } else {
        std::cout << "invalid request" << '\n';
        mistake_ = true;
        return;
    }
} // проверка типов (возвращаем энам и название столбца)

void CreateTableRequest::AddElementToTable(Table* table, const std::string& request) {
    table->size_table_++;
    std::string without_registers_request = request;
    std::transform(without_registers_request.begin(), without_registers_request.end(),
                   without_registers_request.begin(), tolower);
    if (without_registers_request.find("values") != std::string::npos) {
        if (request[without_registers_request.find("values") - 2]
                == request[request.rfind(table->table_name_) + table->table_name_.size() - 1]) {
            // insert into users values ( 'Ivan', 18);
            std::vector<std::string> values =
                    ParseValue(request.substr(request.find('(') + 1, request.find(')') - request.find('(') - 1));
            DeleteSpace(values); // удаляем пробелы
            std::string check_value;
            for (int j = 0; j < values.size(); j++) {
                if (table->column_types_[j].first == table->primary_key_) {// проверка на уникальность primary key
                    for (int k = 0; k < table->table_[table->primary_key_].size(); k++) {
                        table->table_[table->primary_key_][k]->PutInColumn(check_value); // получаем значения в столбце
                        if (check_value == ' ' + values[j]) { // проверяем на уникальность
                            std::cout << "primary key is not unique" << std::endl;
                            exit(0);
                        }
                        check_value.clear();
                    }
                }
                ParseValueByType(values[j], table, j); // парсим значения по типу
            }
        } else {
            std::vector<std::string> columns =
                    ParseValue(request.substr(request.find('(') + 1, request.find(')') - request.find('(') - 1));
            DeleteSpace(columns);
            std::vector<std::string> values =
                    ParseValue(request.substr(request.rfind('(') + 1, request.rfind(')') - request.rfind('(') - 1));
            DeleteSpace(values);
            for (int i = 0; i < columns.size(); i++) {
                CheckQuestionMark(columns[i]);
            }
            std::string check_value;
            for (int k = 0; k < table->column_types_.size(); k++) { // цикл по столбцам в таблице
                for (int j = 0; j < columns.size(); j++) {// цикл по столбцам в запросе
                    if (columns[j] == table->column_types_[k].first) {
                        if (columns[j] == table->primary_key_) { // проверка на уникальность primary key
                            for (int m = 0; m < table->table_[table->primary_key_].size(); m++) { // цикл по столбцу
                                table->table_[table->primary_key_][m]->PutInColumn(check_value);
                                if (check_value == ' ' + values[j]) { // проверяем на уникальность
                                    std::cout << "primary key is not unique" << std::endl;
                                    exit(0);
                                } else {
                                    check_value.clear();
                                }
                            }
                            ParseValueByType(values[j], table, k);
                        } else {
                            check_value.clear();
                            ParseValueByType(values[j], table, k);
                        }
                    }
                }
            }
            for (int i = 0; i < table->column_types_.size(); i++) {
                if (table->table_[table->column_types_[i].first].size() < table->size_table_) {
                    if (table->null[table->column_types_[i].first]) {
                        std::cout << "not null" << std::endl;
                        exit(0);
                    } else
                        table->table_[table->column_types_[i].first].emplace_back(new NullValue);
                }
            }
        }
    } else {
        std::cout << "invalid request";
    }
}


std::vector<std::string> CreateTableRequest::ParseValue(std::string request) {
    std::vector<std::string> values;
    std::string value;
    int index = 0;
    for (int i = 0; i < request.size(); i++) {
        if (request[i] == ',') {
            value = request.substr(index, i - index);
            values.push_back(value);
            index = i + 1;
        }
    }
    value = request.substr(index, request.size() - index);
    values.push_back(value);
    return values;
}

void CreateTableRequest::ParseValueByType(std::string& value_for_type_checking, Table* table, int j) {
    if (table->column_types_[j].second == 0) {
        auto value = new IntegerValue(std::stoi(value_for_type_checking));
        table->table_[table->column_types_[j].first].push_back(value);
        value = nullptr;
    } else if (table->column_types_[j].second == 1) {
        auto value = new DoubleValue(std::stod(value_for_type_checking));
        table->table_[table->column_types_[j].first].push_back(value);
        value = nullptr;
    } else if (table->column_types_[j].second == 2) {
        auto value = new FloatValue(std::stof(value_for_type_checking));
        table->table_[table->column_types_[j].first].push_back(value);
        value = nullptr;
    } else if (table->column_types_[j].second == 3) {
        if (value_for_type_checking == "true") {
            value_for_type_checking = "1";
        } else if (value_for_type_checking == "false") {
            value_for_type_checking = "0";
        }
        auto value = new BooleanValue(std::stoi(value_for_type_checking));
        table->table_[table->column_types_[j].first].push_back(value);
        value = nullptr;
    } else if (table->column_types_[j].second > 4) {
        if (value_for_type_checking.size() > table->column_types_[j].second) {
            value_for_type_checking.erase(table->column_types_[j].second,
                                          value_for_type_checking.size() - table->column_types_[j].second);
        }
        auto value = new VarcharValue(value_for_type_checking);
        table->table_[table->column_types_[j].first].push_back(value);
        value = nullptr;
    }
}

void CreateTableRequest::CheckPrimaryAndForeignKey(std::string& request, Table* table, std::string& column_name) {
    if (request.find("primary key") != std::string::npos) {
        table->primary_key_ = column_name;
        return;
    }
    if (request.find("foreign key") != std::string::npos) {
        table->foreign_key_.column_name_ = column_name;
        request.erase(0, request.find("references") + 10);
        std::string foreign_table = request.substr(0, request.find('('));
        SpaceDelete(foreign_table);
        request.erase(0, request.find('(') + 1);
        std::string foreign_column = request.substr(0, request.find(')'));
        table->foreign_key_.foreign_table_name_ = foreign_table;
        table->foreign_key_.foreign_column_name_ = foreign_column;
        table->foreign_key_.column_name_ = column_name;
        return;
    }
}

void CreateTableRequest::CheckNotNull(std::string& request, Table* table, std::string& column_name) {
    if (request.find("not null") != std::string::npos) {
        table->null[column_name] = true;
        table->not_null = true;
    }
}


void CreateTableRequest::DeleteLineOfTheTable(std::string& request, Table* table) {
    std::string transform_request = request;
    std::transform(transform_request.begin(), transform_request.end(),
                   transform_request.begin(), tolower);
    if (transform_request.find("where") == std::string::npos) {
        table->DeleteTable();
    } else {
        request.erase(0, request.find("where") + 6);
        WhereParser where_parser(request, table, 0);
    }
    std::cout << "delete information" << std::endl;
}

void CreateTableRequest::UpdateInformationInTable(std::string& request, Table* table) {
    std::string transform_request = request;
    std::transform(transform_request.begin(), transform_request.end(),
                   transform_request.begin(), tolower);
    if (transform_request.find("where") == std::string::npos) {
        std::cout << "error" << std::endl;
        exit(0);
    }
    WhereParser where_parser(request, table, 1);
}

void CreateTableRequest::SelectInformationFromTable(std::string& request, Table* table) {
    std::string transform_request = request;
    std::transform(transform_request.begin(), transform_request.end(),
                   transform_request.begin(), tolower);
    if (request.find('*') != std::string::npos && request.find("where") == std::string::npos) {
        table->PrintTable();
        return;
    } else if (request.find('*') != std::string::npos && request.find("where") != std::string::npos) {
        WhereParser where_parser(request, table, 2);
        return;
    }
    if (request.find("where") == std::string::npos) {
        std::string column_name = request.substr(0, request.find("from"));
        std::vector<std::string> column_names;
        Split(column_name, ',', column_names);
        DeleteSpace(column_names);
        table->PrintTable(column_names);
    } else {
        WhereParser where_parser(request, table, 2);
    }
}

void CreateTableRequest::JoinTable(std::string& request, Table* left_table, Table* right_table) {
    std::string transform_request = request;
    std::vector<std::string> print_columns;
    std::transform(transform_request.begin(), transform_request.end(),
                   transform_request.begin(), tolower);
    request.erase(0, request.find("select") + 6);
    bool column_active = false;
    std::vector<std::string> column_names;
    if (transform_request.find('*') == std::string::npos) {
        std::string column_name = request.substr(0, request.find("from"));
        Split(column_name, ',', column_names);
        DeleteSpace(column_names);
        column_active = true;
    }
    request.erase(0, request.find("on") + 2);
    std::string left_column = request.substr(0, request.find('='));
    request.erase(0, request.find('=') + 1);
    std::string right_column = request;
    SpaceDelete(left_column);
    SpaceDelete(right_column);
    if (left_column.substr(0, left_column.find('.')) == left_table->table_name_) {
        left_column.erase(0, left_column.find('.') + 1);
        right_column.erase(0, right_column.find('.') + 1);
    } else if (left_column.substr(0, left_column.find('.')) == right_table->table_name_) {
        std::swap(left_column, right_column);
        left_column.erase(0, left_column.find('.') + 1);
        right_column.erase(0, right_column.find('.') + 1);
    }
    CheckQuestionMark(left_column);
    CheckQuestionMark(right_column);
    if (transform_request.find("inner join") != std::string::npos
            || transform_request.find("left join") == std::string::npos
                    && transform_request.find("right join") == std::string::npos) {
        print_columns.resize(std::max(left_table->size_table_, right_table->size_table_));
        std::string left_value, right_value;
        for (int i = 0; i < left_table->size_table_; i++) {
            for (int j = 0; j < right_table->size_table_; j++) {
                left_table->table_[left_column][i]->PutInColumn(left_value);
                right_table->table_[right_column][j]->PutInColumn(right_value);
                if (left_value == right_value) {
                    if (column_active) {
                        for (int l = 0; l < column_names.size(); l++) {
                            std::string column = column_names[l].substr(0, column_names[l].find('.'));
                            CheckQuestionMark(column);
                            if (column == left_table->table_name_) {
                                std::string column_name = column_names[l];
                                column_name.erase(0, column_name.find('.') + 1);
                                CheckQuestionMark(column_name);
                                for (int k = 0; k < left_table->column_types_.size(); k++) {
                                    if (left_table->column_types_[k].first == column_name) {
                                        left_table->table_[left_table->column_types_[k].first][i]->PutInColumn(
                                                print_columns[i]);
                                    }
                                }
                            } else if (column == right_table->table_name_) {
                                std::string column_name = column_names[l];
                                column_name.erase(0, column_name.find('.') + 1);
                                CheckQuestionMark(column_name);
                                for (int k = 0; k < right_table->column_types_.size(); k++) {
                                    if (right_table->column_types_[k].first == column_name) {
                                        right_table->table_[right_table->column_types_[k].first][j]->PutInColumn(
                                                print_columns[i]);
                                    }
                                }
                            }
                        }
                    } else {
                        for (int k = 0; k < left_table->column_types_.size(); k++) {
                            left_table->table_[left_table->column_types_[k].first][i]->PutInColumn(print_columns[i]);
                        }
                        for (int k = 0; k < right_table->column_types_.size(); k++) {
                            right_table->table_[right_table->column_types_[k].first][j]->PutInColumn(print_columns[i]);
                        }
                    }
                }
                left_value.clear();
                right_value.clear();
            }
        }
    } else if (transform_request.find("left join") != std::string::npos) {
        print_columns.resize(left_table->size_table_);
        std::string left_value, right_value;
        if (column_active) {
        } else {
            for (int j = 0; j < left_table->column_types_.size(); j++) {
                for (int i = 0; i < left_table->size_table_; i++) {
                    left_table->table_[left_table->column_types_[j].first][i]->PutInColumn(print_columns[i]);
                }
            }
            bool flag = false;
            for (int i = 0; i < left_table->size_table_; i++) {
                for (int j = 0; j < right_table->size_table_; j++) {
                    left_table->table_[left_column][i]->PutInColumn(left_value);
                    right_table->table_[right_column][j]->PutInColumn(right_value);
                    if (left_value == right_value) {
                        for (int k = 0; k < right_table->column_types_.size(); k++) {
                            right_table->table_[right_table->column_types_[k].first][j]->PutInColumn(print_columns[i]);
                        }
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    for (int k = 0; k < right_table->column_types_.size(); k++) {
                        print_columns[i] += " NULL";
                    }

                }
                flag = false;
                left_value.clear();
                right_value.clear();
            }
        }
    } else if (transform_request.find("right join") != std::string::npos) {
        print_columns.resize(right_table->size_table_);
        std::string left_value, right_value;
        if (column_active) {
        } else {
            for (int j = 0; j < right_table->column_types_.size(); j++) {
                for (int i = 0; i < right_table->size_table_; i++) {
                    right_table->table_[right_table->column_types_[j].first][i]->PutInColumn(print_columns[i]);
                }
            }
            bool flag = false;
            for (int i = 0; i < right_table->size_table_; i++) {
                for (int j = 0; j < left_table->size_table_; j++) {
                    right_table->table_[right_column][i]->PutInColumn(right_value);
                    left_table->table_[left_column][j]->PutInColumn(left_value);
                    if (left_value == right_value) {
                        for (int k = 0; k < left_table->column_types_.size(); k++) {
                            left_table->table_[left_table->column_types_[k].first][j]->PutInColumn(print_columns[i]);
                        }
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    for (int k = 0; k < left_table->column_types_.size(); k++) {
                        print_columns[i] += " NULL";
                    }

                }
                flag = false;
                left_value.clear();
                right_value.clear();
            }
        }
    }

    if (column_active) {
        for (int i = 0; i < column_names.size(); i++) {
            std::cout << column_names[i] << " ";
        }
    } else {
        for (int i = 0; i < left_table->column_types_.size(); i++) {
            std::cout << left_table->column_types_[i].first << " ";
        }
        for (int i = 0; i < right_table->column_types_.size(); i++) {
            std::cout << right_table->column_types_[i].first << " ";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < print_columns.size(); i++) {
        if (!print_columns[i].empty()) {
            std::cout << print_columns[i] << std::endl;
        }
    }

}





