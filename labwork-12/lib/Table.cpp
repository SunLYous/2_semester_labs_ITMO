#include "Table.h"

Table::~Table() {
    for (auto& i : table_) {
        for (auto& j : i.second) {
            delete j;
        }
    }

}

std::string Table::GetTableName() {
    return table_name_;
}

void Table::PrintTable() {
    std::cout << table_name_ << '\n';
    for (int i = 0; i < column_types_.size(); i++) {
        std::cout << column_types_[i].first << ' ';
    }
    std::cout << '\n';
    std::vector<std::string> column(table_[column_types_[0].first].size());
    for (auto& i : column_types_) {
        for (int j = 0; j < table_[i.first].size(); j++) {
            if (not_null) {
                for (int m = 0; m < null.size(); m++) {
                    if (null[i.first]) {
                        std::string check;
                        table_[i.first][j]->PutInColumn(check);
                        if (check == " null") {
                            column[j] += "     ";
                            break;
                        } else {
                            column[j] += check;
                            break;
                        }
                    } else {
                        table_[i.first][j]->PutInColumn(column[j]);
                        break;
                    }
                }
            } else
                table_[i.first][j]->PutInColumn(column[j]);
        }
    }
    for (int i = 0; i < column.size(); i++) {
        std::cout << column[i] << '\n';
    }
}

size_t Table::GetSizeTable() {
    return size_table_;
}

void Table::DeleteTable() {
    for (auto& i : table_) {
        for (auto& j : i.second) {
            delete j;
        }
    }
    table_.clear();
    size_table_ = 0;
}

void Table::DeleteRow(size_t row) {
    for (auto& i : table_) {
        delete i.second[row];
        i.second.erase(i.second.begin() + row);
    }
    size_table_--;
}

void Table::PrintTable(const std::vector<std::string>& column_names) {
    std::cout << table_name_ << '\n';
    std::vector<std::string> print;
    for (int i = 0; i < column_names.size(); i++) {
        for (int j = 0; j < column_types_.size(); j++) {
            if (column_names[i] == column_types_[j].first) {
                std::cout << column_names[i] << ' ';
                print.push_back(column_names[i]);
            }
        }
    }
    std::cout << '\n';
    std::vector<std::string> column(size_table_);
    for (int i = 0; i < print.size(); i++) {
        for (int j = 0; j < size_table_; j++) {
            if (not_null) {
                for (int m = 0; m < null.size(); m++) {
                    if (null[print[i]]) {
                        std::string check;
                        table_[print[i]][j]->PutInColumn(check);
                        if (check == " null") {
                            column[j] += "     ";
                            break;
                        } else {
                            column[j] += check;
                            break;
                        }
                    } else {
                        table_[print[i]][j]->PutInColumn(column[j]);
                        break;
                    }
                }
            } else
                table_[print[i]][j]->PutInColumn(column[j]);
        }
    }
    for (int i = 0; i < column.size(); i++) {
        std::cout << column[i] << '\n';
    }
}

std::pair<std::string, size_t> Table::GetTypeColumn(size_t column) {
    return column_types_[column];
}

size_t Table::GetSizeColumn(std::string column_name) {
    return column_types_.size();
}
