/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-16 13:51:04
 * @LastEditTime: 2024-07-16 13:57:48
 * @FilePath: /CPPprojects/restart_CPP/ByteDance/maxAreaOfIslands.cpp
 * @Description: Please implement
 */
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

/*
We have implemented the algorithm (backtrack search) which calculates the num of Islands.
*/

class Solution {
public:
    void backtraceSearch(vector<vector<int>>& grid, vector<vector<bool>>& flag, int rows, int cols, int cur_i, int cur_j, int& searchArea) {
        if(flag[cur_i][cur_j]) return;
        if(grid[cur_i][cur_j] == 1){
            searchArea ++;
            flag[cur_i][cur_j] = true;
        }
        else return;
        // search 
        if(cur_i - 1 >= 0) {
            backtraceSearch(grid, flag, rows, cols, cur_i - 1, cur_j, searchArea);
        }
        if(cur_i + 1 < rows){
            backtraceSearch(grid, flag, rows, cols, cur_i + 1, cur_j, searchArea);
        }
        if(cur_j - 1 >= 0) {
            backtraceSearch(grid, flag, rows, cols, cur_i, cur_j - 1, searchArea);
        }
        if(cur_j + 1 < cols){
            backtraceSearch(grid, flag, rows, cols, cur_i, cur_j + 1, searchArea);
        }
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int maxArea = 0;
        vector<vector<bool>> flag(rows, vector<bool>(cols));
        for(int i = 0 ; i < rows ; ++ i) {
            for(int j = 0 ; j < cols ; ++ j) {
                int searchArea = 0;
                if (grid[i][j] == 1 && !flag[i][j]) {
                    backtraceSearch(grid, flag, rows, cols, i, j, searchArea);
                    maxArea = max(maxArea, searchArea);
                }
            }
        }
        return maxArea;
    }

};


int main() {
    
    return 0;
}