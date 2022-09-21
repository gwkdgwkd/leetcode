/*
如果连续数字之间的差严格地在正数和负数之间交替，
则数字序列称为摆动序列。
第一个差（如果存在的话）可能是正数或负数。
仅有一个元素或者含两个不等元素的序列也视作摆动序列。
例如，[1, 7, 4, 9, 2, 5]是一个摆动序列，
因为差值(6, -3, 5, -7, 3)是正负交替出现的。
相反，[1, 4, 7, 2, 5]和[1, 7, 4, 5, 5]不是摆动序列，
第一个序列是因为它的前两个差值都是正数，
第二个序列是因为它的最后一个差值为零。
子序列可以通过从原始序列中删除一些（也可以不删除）元素来获得，
剩下的元素保持其原始顺序。
给你一个整数数组nums，返回nums中作为摆动序列的最长子序列的长度。

示例1：
输入：nums = [1,7,4,9,2,5]
输出：6
解释：整个序列均为摆动序列，各元素之间的差值为(6, -3, 5, -7, 3)。

示例2：
输入：nums = [1,17,5,10,13,15,10,5,16,8]
输出：7
解释：这个序列包含几个长度为7摆动序列。
其中一个是[1, 17, 10, 13, 10, 16, 8]，
各元素之间的差值为(16, -7, 3, -3, 6, -8)。

示例3：
输入：nums = [1,2,3,4,5,6,7,8,9]
输出：2

提示：
1 <= nums.length <= 1000
0 <= nums[i] <= 1000
*/

// 动态规划
int wiggleMaxLength(int* nums, int numsSize) {
  // dp[i][0]表示以i结尾的最大摆动长度，nums[i−1]>nums[i]；
  // dp[i][1]表示以i结尾的最大摆动长度，nums[i−1]<nums[i]。
  int dp[numsSize][2];
  for (int i = 0; i < numsSize; ++i) {
    dp[i][0] = dp[i][1] = 1;
  }

  for (int i = 1; i < numsSize; ++i) {
    if (nums[i - 1] > nums[i]) {
      dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + 1);
    } else if (nums[i - 1] < nums[i]) {
      dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] + 1);
    } else {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][1];
    }
  }

  return fmax(dp[numsSize - 1][0], dp[numsSize - 1][1]);
}

int wiggleMaxLength(int* nums, int numsSize) {
  int up = 1, down = 1;
  for (int i = 1; i < numsSize; i++) {
    if (nums[i] > nums[i - 1]) {
      up = fmax(up, down + 1);
    } else if (nums[i] < nums[i - 1]) {
      down = fmax(up + 1, down);
    }
  }
  return fmax(up, down);
}

// 贪心算法
// 局部最优：删除单调坡度上的节点（不包括单调坡度两端的节点），
//         那么这个坡度就可以有两个局部峰值。
// 整体最优：整个序列有最多的局部峰值，从而达到最长摆动序列。
// 实际操作上，其实连删除的操作都不用做，
// 因为要求的是最长摆动子序列的长度，
// 所以只需要统计数组的峰值数量就可以了。
// 相当于是删除单一坡度上的节点，然后统计长度。
// 时间复杂度O(n)，空间复杂度O(1)
int wiggleMaxLength(int* nums, int numsSize) {
  if (numsSize < 2) return numsSize;

  int prediff = 0;
  int curdiff = 0;
  int result = 1;  // 默认最右面有一个峰值
  for (int i = 1; i < numsSize; ++i) {
    curdiff = nums[i] - nums[i - 1];
    if ((curdiff > 0 && prediff <= 0) || (curdiff < 0 && prediff >= 0)) {
      prediff = curdiff;
      ++result;
    }
  }

  return result;
}

class Solution {
 public:
  int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    // dp[i][0]：表示从0到i且nums[i]>nums[i-1]的最大长度
    // dp[i][1]：表示从0到i且nums[i]<nums[i-1]的最大长度
    vector<vector<int>> dp(n, vector<int>(2, 1));

    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + 1);
      } else if (nums[i] < nums[i - 1]) {
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + 1);
      } else {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = dp[i - 1][1];
      }
    }

    return max(dp[n - 1][0], dp[n - 1][1]);
  }
};
