/*
给定一个整数数组arr，以及一个整数target作为目标值，
返回满足i < j < k且arr[i] + arr[j] + arr[k] == target的元组i, j, k的数量。
由于结果会非常大，请返回109 + 7的模。

示例1：
输入：arr = [1,1,2,2,3,3,4,4,5,5], target = 8
输出：20
解释：按值枚举(arr[i], arr[j], arr[k])：
     (1, 2, 5)出现8次；
     (1, 3, 4)出现8次；
     (2, 2, 4)出现2次；
     (2, 3, 3)出现2次。

示例2：
输入：arr = [1,1,2,2,2,2], target = 5
输出：12
解释：arr[i] = 1, arr[j] = arr[k] = 2出现12次：
     我们从[1,1]中选择一个1，有2种情况，
     从[2,2,2,2]中选出两个2，有6种情况。


提示：
3 <= arr.length <= 3000
0 <= arr[i] <= 100
0 <= target <= 300
*/

class Solution {
 public:
  int threeSumMulti(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    long long ans = 0;
    for (int i = 2; i < n; ++i) {
      int c = arr[i];
      int left = 0;
      int right = i - 1;
      while (left < right) {
        int sum = arr[left] + arr[right] + c;
        if (sum < target) {
          ++left;
        } else if (sum > target) {
          --right;
        } else {
          if (arr[left] == arr[right]) {
            ans += (right - left + 1) * (right - left) / 2;
            // ans = ans
            break;
          } else {
            int t1 = 0, t2 = 0;
            int l = arr[left], r = arr[right];
            while (l == arr[left]) {
              ++t1;
              ++left;
            }
            while (r == arr[right]) {
              ++t2;
              --right;
            }
            ans += t1 * t2;
          }
        }
      }
    }
    return ans % 1000000007;
  }
};