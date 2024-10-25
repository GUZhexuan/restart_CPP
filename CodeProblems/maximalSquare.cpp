/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-14 00:24:14
 * @LastEditTime: 2024-07-14 00:56:20
 * @FilePath: /CPPprojects/restart_CPP/ByteDance/maximalSquare.cpp
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
    int maximalSquare(vector<vector<char>>& matrix) {
        // Use dp[i] denote the sidelength of the big square using i^th as the right_bottom one
        int max_length = 0;
        int rows = matrix.size();
        int columns = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(columns));
        for(int i = 0 ; i < rows ; ++ i){
            for(int j = 0 ; j < columns ; ++ j){
                if(matrix[i][j] == '0'){
                    dp[i][j] = 0;
                }
                else{
                    if(i - 1 >= 0 && j - 1 >= 0){
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    else{
                        dp[i][j] = 1;
                    }
                    max_length = max(max_length, dp[i][j]);
                }
            }
        }
        return max_length * max_length;
    }
};

int main(){
    Solution sol;
    vector<vector<char>> vec{{'1', '0', '1', '0', '0'},
                            {'1', '0', '1', '1', '1'},
                            {'1', '1', '1', '1', '1'},
                            {'1', '0', '0', '1', '0'}};

    int ans = sol.maximalSquare(vec);
    cout << ans << endl;
    return 0;
}