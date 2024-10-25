/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-12 00:58:47
 * @LastEditTime: 2024-07-12 16:40:50
 * @FilePath: /CPPprojects/restart_CPP/ByteDance/spiralMatrix.cpp
 * @Description: Please implement
 */
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int columns = matrix[0].size();
        vector<int> ans;
        ans.resize(rows * columns);
        int required_nums = ceil(min(rows, columns) / 2.0);
        int index = 0;
        for(int i = 0 ; i < required_nums ; ++ i){
            for(int j = i ; j < columns - i ; ++j){
                ans[index++] = matrix[i][j];
            }
            if (index == rows * columns) break;
            for(int j = i + 1 ; j < rows - i ; ++j){
                ans[index++] = matrix[j][columns - 1 - i];
            }
            if (index == rows * columns) break;
            for(int j = columns - 2 - i ; j >= i ; --j){
                ans[index++] = matrix[rows - 1 - i][j];
            }
            if (index == rows * columns) break;
            for(int j = rows - 2 - i ; j >= i + 1 ; --j){
                ans[index++] = matrix[j][i];
            }
            if (index == rows * columns) break;
        }
        return ans;
    }
};

int main(){
    // vector<vector<int>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> vec{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    Solution sol;
    vector<int> ans;
    ans = sol.spiralOrder(vec);
    for(auto elem : ans){
        cout << elem << " ";
    }
    cout << endl;
    return 0;
}