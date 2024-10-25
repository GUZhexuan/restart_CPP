/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-10 23:25:07
 * @LastEditTime: 2024-07-11 00:13:17
 * @FilePath: /CPPprojects/restart_CPP/ByteDance/wordBreak.cpp
 * @Description: Please implement
 */
#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        map<string, bool> mp;
        vector<bool> vec(s.length(), false);
        for(const string& word : wordDict){
            mp[word] = true;
        }
        for(int i = 0 ; i < s.length() ; ++i){
            for(int j = 0 ; j <= i ; ++j){
                bool exist = mp[s.substr(j, i - j + 1)];
                if(j == 0){
                    vec[i] = exist;
                }
                else{
                    vec[i] = (exist & vec[j - 1]);
                }
                if(vec[i])
                    break;
            }
        }
        return vec[s.length() - 1];
    }
};

int main(){
    string s = "catsandog";
    vector<string> wordDict{"cats", "dog", "sand", "and", "cat"};
    // string s = "leetcode";
    // vector<string> wordDict{"leet", "code"};
    Solution temp;
    bool result = temp.wordBreak(s, wordDict);
    cout << boolalpha << result << endl;
}