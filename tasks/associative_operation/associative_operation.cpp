#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    int flag = 1;
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table.size(); ++j) {
            for (int k = 0; k < table.size(); ++k) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    flag = 0;
                    break;
                }
            }
        }
    }
    if (flag == 0) {
        return false;
    } else {
        return true;
    }
}
