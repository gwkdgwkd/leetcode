/*
给一个长度为n下标从0开始的整数数组nums，它包含1到n的所有数字，请返回上升四元组的数目。
如果一个四元组(i, j, k, l)满足以下条件，我们称它是上升的：
0 <= i < j < k < l < n且nums[i] < nums[k] < nums[j] < nums[l]。

示例1：
输入：nums = [1,3,2,4,5]
输出：2
解释：当i=0，j=1，k=2且l=3时，有nums[i]<nums[k]<nums[j]<nums[l]。
     当i=0，j=1，k=2且l=4时，有nums[i]<nums[k]<nums[j]<nums[l]。
     没有其他的四元组，所以我们返回2。

示例2：
输入：nums = [1,2,3,4]
输出：0
解释：只存在一个四元组i=0，j=1，k=2，l=3，但是nums[j]<nums[k]，所以我们返回0。


提示：
4 <= nums.length <= 4000
1 <= nums[i] <= nums.length
nums中所有数字互不相同，nums是一个排列。
*/

// 根据132模式的取名法，本题可以取名为1324模式

class Solution {
 public:
  long long countQuadruplets(vector<int> &nums) {
    int n = nums.size();

    vector<vector<int>> great(n, vector<int>(n + 1));
    for (int k = n - 2; k; k--) {
      great[k] = great[k + 1];
      for (int x = 1; x < nums[k + 1]; x++) {
        great[k][x]++;
      }
    }

    long ans = 0;
    for (int j = 1; j < n - 2; j++) {
      for (int k = j + 1; k < n - 1; k++) {
        if (int x = nums[k]; nums[j] > x) {
          ans += (x - n + 1 + j + great[j][x]) * great[k][nums[j]];
        }
      }
    }

    return ans;
  }
};

class Solution {
 public:
  long long countQuadruplets(vector<int> &nums) {
    int n = nums.size();
    vector<vector<int>> great(n, vector<int>(n + 1));
    for (int k = n - 2; k; k--) {
      great[k] = great[k + 1];
      for (int x = 1; x < nums[k + 1]; x++) {
        great[k][x]++;
      }
    }

    long ans = 0;
    for (int j = 1; j < n - 2; j++) {
      for (int k = j + 1; k < n - 1; k++) {
        if (int x = nums[k]; nums[j] > x) {
          ans += (x - n + 1 + j + great[j][x]) * great[k][nums[j]];
        }
      }
    }

    return ans;
  }
};

class Solution {
 public:
  long long countQuadruplets(vector<int> &nums) {
    long long cnt4 = 0;

    vector<int> cnt3(nums.size());
    for (int l = 2; l < nums.size(); l++) {
      int cnt2 = 0;
      for (int j = 0; j < l; j++) {
        if (nums[j] < nums[l]) {  // 3 < 4
          cnt4 += cnt3[j];
          // 把j当作i，把l当作k，现在nums[i]<nums[k]，即1<2
          cnt2++;
        } else {  // 把l当作k，现在nums[j]>nums[k]，即3>2
          cnt3[j] += cnt2;
        }
      }
    }

    return cnt4;
  }
};
