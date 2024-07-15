/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-15 10:58:36
 * @LastEditTime: 2024-07-15 11:19:44
 * @FilePath: /CPPprojects/restart_CPP/ByteDance/numIslands.cpp
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
    void backtraceSearch(vector<vector<char>>& grid, vector<vector<bool>>& flag, int rows, int cols, int cur_i, int cur_j) {
        if(flag[cur_i][cur_j]) return;
        if(grid[cur_i][cur_j] == '1'){
            flag[cur_i][cur_j] = true;
        }
        else return;
        // search 
        if(cur_i - 1 >= 0) {
            backtraceSearch(grid, flag, rows, cols, cur_i - 1, cur_j);
        }
        if(cur_i + 1 < rows){
            backtraceSearch(grid, flag, rows, cols, cur_i + 1, cur_j);
        }
        if(cur_j - 1 >= 0) {
            backtraceSearch(grid, flag, rows, cols, cur_i, cur_j - 1);
        }
        if(cur_j + 1 < cols){
            backtraceSearch(grid, flag, rows, cols, cur_i, cur_j + 1);
        }
    }

    /*
    To be more memory friendly, we can directly modify the values of the 'grid' itself rather than 
    maintaining a new matrix 'flag'.
    */
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> flag(rows, vector<bool>(cols));
        int Islands = 0;
        for(int i = 0 ; i < rows ; ++ i) {
            for(int j = 0 ; j < cols ; ++ j) {
                if (grid[i][j] == '1' && !flag[i][j]) {
                    Islands ++;
                    backtraceSearch(grid, flag, rows, cols, i, j);
                }
            }
        }
        return Islands;
    }
};

int main() {

    return 0;
}