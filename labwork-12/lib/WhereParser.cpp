#include "WhereParser.h"

WhereParser::WhereParser(std::string& request, Table* table, size_t command_type) {
    switch (command_type) {
        case static_cast<size_t>(Command::delete_):ParseDelete(request, table);
            break;
        case static_cast<size_t>(Command::update):ParseUpdate(request, table);
            break;
        case static_cast<size_t>(Command::select):ParseSelect(request, table);
            break;
        default:break;
    }
}

void WhereParser::ParseOperation(std::string& request) {
    std::vector<std::string> and_result;
    std::regex or_regex("OR", std::regex_constants::icase); // OR
    std::sregex_token_iterator or_expressions(request.begin(), request.end(), or_regex, -1);
    std::sregex_token_iterator end;
    for (; or_expressions != end; ++or_expressions) {
        std::string expression = *or_expressions;
        std::regex and_regex("AND", std::regex_constants::icase); // AND
        std::sregex_token_iterator and_expressions(expression.begin(), expression.end(), and_regex, -1);
        std::sregex_token_iterator and_end;
        for (; and_expressions != and_end; ++and_expressions) {
            std::string and_expression = *and_expressions;
            SpaceDelete(and_expression);
            and_result.push_back(and_expression);
        }
        result_.push_back(and_result);
        and_result.clear();
    }
}


void WhereParser::ParseDelete(std::string& request, Table* table) {
    ParseOperation(request);
    std::vector<int> delete_row;
    CheckingForSuitableLines(delete_row, table);
    for (int i = 0; i < delete_row.size(); ++i) {
        table->DeleteRow(delete_row[i] - i);
    }
}

void WhereParser::ParseUpdate(std::string& request, Table* table) {
    std::vector<std::string> column_names;
    request.erase(0, request.find("set") + 3);
    std::string column_name = request.substr(0, request.find("where"));
    Split(column_name, ',', column_names);
    DeleteSpace(column_names);
    std::vector<std::string> values;
    for (auto& i : column_names) {
        values.push_back(i.substr(i.find("=") + 2, i.size()));
        CheckQuestionMark(values.back());
        i.erase(i.find("=") - 1, i.size());
    }
    request.erase(0, request.find("where") + 5);
    ParseOperation(request);
    std::vector<int> update_row;
    CheckingForSuitableLines(update_row, table);
    for (int i = 0; i < update_row.size(); ++i) {
        for (int j = 0; j < column_names.size(); ++j) {
            for (int k = 0; k < table->column_types_.size(); ++k) {
                if (table->column_types_[k].first == column_names[j]) {
                    UpdateCell(table->column_types_[k].second, column_names[j], update_row[i], table, values[j]);
                    break;
                }
            }
        }
    }
}

void WhereParser::ParseSelect(std::string& request, Table* table) {
    if (request.find('*') != std::string::npos) {
        request.erase(0, request.find("where") + 6);
        ParseOperation(request);
        std::vector<int> select_row;
        CheckingForSuitableLines(select_row, table);
        std::vector<std::string> print_row(table->size_table_);
        for (int i = 0; i < select_row.size(); ++i) {
            for (int j = 0; j < table->column_types_.size(); j++) {
                for (int k = 0; k < table->size_table_; k++) {
                    if (select_row[i] == k) {
                        table->table_[table->column_types_[j].first][k]->PutInColumn(print_row[k]);
                    }
                }
            }
        }
        for (int i = 0; i < table->column_types_.size(); ++i) {
            std::cout << table->column_types_[i].first << " ";
        }
        std::cout << "\n";
        for (auto& i : print_row) {
            if (i[0] != '\0') {
                std::cout << i << "\n";
            }
        }
    } else {
        std::vector<std::string> column_names;
        std::string column_name = request.substr(0, request.find("from"));
        Split(column_name, ',', column_names);
        DeleteSpace(column_names);
        request.erase(0, request.find("where") + 6);
        ParseOperation(request);
        std::vector<int> select_row;
        CheckingForSuitableLines(select_row, table);
        std::vector<std::string> print_row(table->size_table_);
        for (int i = 0; i < table->column_types_.size(); ++i) {
            for (int j = 0; j < column_names.size(); ++j) {
                if (table->column_types_[i].first == column_names[j]) {
                    for (int k = 0; k < select_row.size(); ++k) {
                        table->table_[table->column_types_[i].first][select_row[k]]->PutInColumn(print_row[select_row[k]]);
                    }
                }
            }
        }

        for (int i = 0; i < column_names.size(); ++i) {
            std::cout << column_names[i] << " ";
        }
        std::cout << "\n";
        for (auto& i : print_row) {
            if (i[0] != '\0') {
                std::cout << i << "\n";
            }
        }
    }
}

Operation WhereParser::ParseLogisticOperation(std::string& request) {
    std::regex regex(R"(("?\w+"?)\s*(=|>|<|!=)\s*("?\w+"?))");
    std::smatch match;
    std::regex_search(request, match, regex);
    std::string first = match[1];
    std::string second = match[3];
    std::string operation = match[2];
    CheckQuestionMark(first);
    CheckQuestionMark(second);
    Operation operation_ = Operation();
    operation_.column_name_ = first;
    operation_.operation_ = operation;
    operation_.value_ = second;
    return operation_;
}


bool WhereParser::CheckOperation(const Operation& operation, int row, Table* table) {
    if (operation.operation_ == "=") {
        for (int i = 0; i < table->column_types_.size(); ++i) {
            if (table->column_types_[i].first == operation.column_name_) {
                return CallAcceptType(table->column_types_[i].second, operation, row, table);
            }
        }
    } else if (operation.operation_ == ">") {
        for (int i = 0; i < table->column_types_.size(); ++i) {
            if (table->column_types_[i].first == operation.column_name_) {
                return CallAcceptLessType(table->column_types_[i].second, operation, row, table);
            }
        }
    } else if (operation.operation_ == "<") {
        for (int i = 0; i < table->column_types_.size(); ++i) {
            if (table->column_types_[i].first == operation.column_name_) {
                return CallAcceptMoreType(table->column_types_[i].second, operation, row, table);
            }
        }
    }
}

bool WhereParser::CallAcceptType(int number_type, const Operation& operation, int row, Table* table) {
    if (number_type == 0) {
        auto* visitor = new VisitorInteger();
        bool result = table->table_[operation.column_name_][row]->Accept(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 1) {
        auto* visitor = new VisitorDouble();
        bool result = table->table_[operation.column_name_][row]->Accept(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 2) {
        auto* visitor = new VisitorFloat();
        bool result = table->table_[operation.column_name_][row]->Accept(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 3) {
        auto* visitor = new VisitorBoolean();
        bool result = table->table_[operation.column_name_][row]->Accept(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 4) {
        return false;
    }
    if (number_type >= 5) {
        auto* visitor = new VisitorVarchar();
        bool result = table->table_[operation.column_name_][row]->Accept(visitor, operation.value_);
        delete visitor;
        return result;
    }
}

bool WhereParser::CallAcceptLessType(int number_type, const Operation& operation, int row, Table* table) {

    if (number_type == 0) {
        auto* visitor = new VisitorInteger();
        bool result = table->table_[operation.column_name_][row]->AcceptLess(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 1) {
        auto* visitor = new VisitorDouble();
        bool result = table->table_[operation.column_name_][row]->AcceptLess(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 2) {
        auto* visitor = new VisitorFloat();
        bool result = table->table_[operation.column_name_][row]->AcceptLess(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 3) {
        auto* visitor = new VisitorBoolean();
        bool result = table->table_[operation.column_name_][row]->AcceptLess(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 4) {
        return false;
    }
    if (number_type >= 5) {
        auto* visitor = new VisitorVarchar();
        bool result = table->table_[operation.column_name_][row]->AcceptLess(visitor, operation.value_);
        delete visitor;
        return result;
    }
}

bool WhereParser::CallAcceptMoreType(int number_type, const Operation& operation, int row, Table* table) {
    if (number_type == 0) {
        auto* visitor = new VisitorInteger();
        bool result = table->table_[operation.column_name_][row]->AcceptMore(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 1) {
        auto* visitor = new VisitorDouble();
        bool result = table->table_[operation.column_name_][row]->AcceptMore(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 2) {
        auto* visitor = new VisitorFloat();
        bool result = table->table_[operation.column_name_][row]->AcceptMore(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 3) {
        auto* visitor = new VisitorBoolean();
        bool result = table->table_[operation.column_name_][row]->AcceptMore(visitor, operation.value_);
        delete visitor;
        return result;
    }
    if (number_type == 4) {
        return false;
    }
    if (number_type >= 5) {
        auto* visitor = new VisitorVarchar();
        bool result = table->table_[operation.column_name_][row]->AcceptMore(visitor, operation.value_);
        delete visitor;
        return result;
    }
}

void WhereParser::UpdateCell(int number_type,
                             const std::string& column_name,
                             int row,
                             Table* table,
                             const std::string& value) {
    if (number_type == 0) {
        auto* visitor = new VisitorInteger();
        table->table_[column_name][row]->UpdateValue(visitor, value);
        delete visitor;
    }
    if (number_type == 1) {
        auto* visitor = new VisitorDouble();
        table->table_[column_name][row]->UpdateValue(visitor, value);
        delete visitor;
    }
    if (number_type == 2) {
        auto* visitor = new VisitorFloat();
        table->table_[column_name][row]->UpdateValue(visitor, value);
        delete visitor;
    }
    if (number_type == 3) {
        auto* visitor = new VisitorBoolean();
        table->table_[column_name][row]->UpdateValue(visitor, value);
        delete visitor;
    }
    if (number_type == 4) {
        return;
    }
    if (number_type >= 5) {
        auto* visitor = new VisitorVarchar();
        table->table_[column_name][row]->UpdateValue(visitor, value);
        delete visitor;
    }

}

void WhereParser::CheckingForSuitableLines(std::vector<int>& number_lines, Table* table) {
    bool or_flag = false;
    bool and_flag = true;
    Operation operation;
    for (int i = 0; i < table->size_table_; ++i) {
        for (auto& j : result_) {
            for (auto& k : j) {
                operation = ParseLogisticOperation(k);
                and_flag = and_flag && CheckOperation(operation, i, table);
            }
            or_flag = or_flag || and_flag;
            and_flag = true;
        }
        if (or_flag) {
            number_lines.push_back(i);
        }
        or_flag = false;
    }

}


