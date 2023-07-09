#include "SQLClass.h"

void SQLClass::SearchRequest(std::string& request) {
    std::string without_registers_request = request;
    std::transform(without_registers_request.begin(), without_registers_request.end(),
                   without_registers_request.begin(), tolower);
    if (without_registers_request.find("create table") != std::string::npos) {
        auto table = create.ParserCreateRequest(request);
        if (table != nullptr) {
            tables_.push_back(table);
        }
    } else if (without_registers_request.find("insert into") != std::string::npos) {
        bool check = false;
        std::string name_table;
        request.erase(0, 12);
        name_table = request.substr(0, request.find(' '));
        CheckQuestionMark(name_table);
        for (int i = 0; i < tables_.size(); i++) {
            if (tables_[i]->GetTableName() == name_table) {
                create.AddElementToTable(tables_[i], request);
                check = true;
                break;
            }
        }
        if (!check) {
            std::cout << "invalid request";
            exit(0);
        }
    } else if (without_registers_request.find("drop table") != std::string::npos) {
        std::string name_table;
        std::cout << "drop table: ";
        if (request.find('"') != std::string::npos) {
            name_table = request.substr(request.find('"') + 1, request.rfind('"') - request.find('"') - 1);
            std::cout << name_table << std::endl;
        } else {
            name_table =
                    without_registers_request.substr(request.rfind(' ') + 1, request.size() - request.rfind(' ') - 1);
        }
        for (int i = 0; i < tables_.size(); i++) {
            if (tables_[i]->GetTableName() == name_table) {
                std::cout << name_table << std::endl;
                delete tables_[i];
                tables_.erase(tables_.begin() + i);
                return;
            }
        }
    } else if (without_registers_request.find("delete from") != std::string::npos) {
        std::string name_table;
        request.erase(0, 12);
        name_table = request.substr(0, request.find(' '));
        request.erase(0, request.find(' ') + 1);
        if (name_table[0] == '"') {
            name_table = name_table.substr(1, name_table.size() - 2);
        }
        for (int i = 0; i < tables_.size(); i++) {
            if (tables_[i]->GetTableName() == name_table) {
                create.DeleteLineOfTheTable(request, tables_[i]);
                return;
            }
        }
        std::cout << "don't find table" << std::endl;
    } else if (without_registers_request.find("update") != std::string::npos) {
        std::string name_table;
        std::cout << "update" << '\n';
        request.erase(0, 7);
        name_table = request.substr(0, request.find(' '));
        if (name_table[0] == '"') {
            name_table = name_table.substr(1, name_table.size() - 2);
        }
        for (int i = 0; i < tables_.size(); i++) {
            if (tables_[i]->GetTableName() == name_table) {
                create.UpdateInformationInTable(request, tables_[i]);
                return;
            }
        }
    } else if (without_registers_request.find("select") != std::string::npos) {
        if (without_registers_request.find("join") != std::string::npos) {
            std::string left_table;
            std::string right_table;
            left_table = request.substr(without_registers_request.find("from") + 5,
                                        without_registers_request.find("join") - without_registers_request.find("from")
                                                - 6);
            if(left_table.find("left") != std::string::npos){
                left_table = left_table.substr(0, left_table.find("left") - 1);
            }
            if(left_table.find("right") != std::string::npos){
                left_table = left_table.substr(0, left_table.find("right") - 1);
            }
            right_table = request.substr(without_registers_request.find("join") + 5,
                                         without_registers_request.find("on") - without_registers_request.find("join")
                                                 - 6);
            std::cout << left_table << " " << right_table << std::endl;
            CheckQuestionMark(left_table);
            CheckQuestionMark(right_table);
            Table* left = nullptr;
            Table* right = nullptr;
            for (int i = 0; i < tables_.size(); i++) {
                if (tables_[i]->GetTableName() == left_table) {
                    left = tables_[i];
                }
                if (tables_[i]->GetTableName() == right_table) {
                    right = tables_[i];
                }
            }
            create.JoinTable(request, left, right);
            return;
        } else {
            std::string name_table;
            if (without_registers_request.find("where") == std::string::npos) {
                name_table = request.substr(without_registers_request.find("from") + 5,
                                            without_registers_request.size()
                                                    - (without_registers_request.find("from") + 5));
                request.erase(0, 7);
                CheckQuestionMark(name_table);
                for (int i = 0; i < tables_.size(); i++) {
                    if (tables_[i]->GetTableName() == name_table) {
                        create.SelectInformationFromTable(request, tables_[i]);
                        return;
                    }
                }
            } else {
                name_table = request.substr(without_registers_request.find("from") + 5,
                                            without_registers_request.find("where")
                                                    - without_registers_request.find("from") - 6);
                request.erase(0, 7);
                CheckQuestionMark(name_table);
                for (int i = 0; i < tables_.size(); i++) {
                    if (tables_[i]->GetTableName() == name_table) {
                        create.SelectInformationFromTable(request, tables_[i]);
                        return;
                    }
                }

            }
        }
    } else {
        std::cout << "invalid request";
        exit(0);
    }
}


std::string SQLClass::DeleteSpace(std::string& request) {
    std::erase(request, '\n');
    std::erase(request, '\t');
    std::string result;
    bool space = false;
    for (char check : request) {
        if (std::isspace(check)) {
            if (!space) {
                result += ' ';
                space = true;
            }
        } else {
            result += check;
            space = false;
        }
    }
    if (result.back() == ' ') {
        result.pop_back();
    }
    if (result[0] == ' ') {
        result.erase(0, 1);
    }
    return result;
}

void SQLClass::DivisionIntoRequests(std::string& request) {
    for (int i = 0; i < request.size(); i++) {
        if (request[i] == ';') {
            requests_.push_back(request.substr(0, i));
            request.erase(0, i + 1);
            i = 0;
        }
    }
}

void SQLClass::ParsingRequest(std::string& request) {
    request = DeleteSpace(request);
    DivisionIntoRequests(request);
    for (auto& command : requests_) {
        if (command.empty()) {
            std::cout << "invalid request";
            return;
        }
        SearchRequest(command);
    }
}

SQLClass::~SQLClass() {
    for (auto& table : tables_) {
        delete table;
    }
}

size_t SQLClass::GetSizeTable(const std::string& table_name) {
    for (auto& table : tables_) {
        if (table->GetTableName() == table_name) {
            return table->GetSizeTable();
        }
    }
    return 0;
}


