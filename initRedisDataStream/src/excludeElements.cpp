#include "main.h"

using namespace std;

vector<string> excludeElements(const vector<string>& current_row, const vector<int>& exclude_indices) {
    vector<string> result;

    for (size_t i = 0; i < current_row.size(); ++i) {
        if (find(exclude_indices.begin(), exclude_indices.end(), i) != exclude_indices.end()) {
            result.push_back(current_row[i]);
        }
    }
    return result;
}
