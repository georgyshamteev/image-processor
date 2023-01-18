#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    int flag = 1;
    for (int i = 0; i < table.length; ++i) {
        for (int j = 0; j < table.length; ++j) {
            for (int k = 0; k < table.length; ++k) {
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
