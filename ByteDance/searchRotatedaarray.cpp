/*
 * @author: Zhexuan Gu
 * @Date: 2024-07-13 22:52:42
 * @LastEditTime: 2024-07-13 23:54:53
 * @FilePath: /CPPprojects/restart_CPP/ByteDance/searchRotatedaarray.cpp
 * @Description: Please implement
 */
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

/*
To achieve O(logn) time complexity, it's easy to come up with binary search;
However, currently, the ordered array is rotated, e.g.,

[0,1,2,4,5,6,7] ---> [4,5,6,7,0,1,2]

Hence, we can't directly apply binary search on it.

0
*/

class Solution {
public:
    int binarySearch(vector<int>& nums, int left, int right, int target) {
        if (left > right || left < 0 || right >= nums.size())
            return -1;
        int mid = ((left + right) >> 1);
        if (nums[mid] == target)
            return mid;
        if (nums[mid] < target){
            // in the ordered case, we should be confident that we can find target int the right subarray

            /*
            Now we should thinks about/classify the mid point into the former or latter rotated array
            */

            if((nums[mid] < nums[right] && nums[right] >= target) || (nums[mid] > nums[left] && nums[left] < target))
                return binarySearch(nums, mid + 1, right, target);
            else
                return binarySearch(nums, left, mid - 1, target);
        }
        else{
            if((nums[mid] > nums[left] && nums[left] <= target) || (nums[mid] < nums[right] && nums[right] > target))
                return binarySearch(nums, left, mid - 1, target);
            else
                return binarySearch(nums, mid + 1, right, target);
        }
    }
    int search(vector<int>& nums, int target) {
        int right = nums.size() - 1;
        int left = 0;
        int ans = binarySearch(nums, left, right, target);
        return ans;
    }
};

int main(){
    Solution sol;
    vector<int> vec{4, 5, 6, 7, 8, 1, 2, 3};
    int ans = sol.search(vec, 8);
    cout << ans << endl;
    return 0;
}