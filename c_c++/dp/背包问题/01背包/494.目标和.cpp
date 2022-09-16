/*
给你一个整数数组nums和一个整数target。
向数组中的每个整数前添加'+'或'-'，
然后串联起所有整数，可以构造一个表达式：
例如，nums=[2,1]，可以在2之前添加'+'，
在1之前添加'-'，然后串联起来得到表达式"+2-1"。
返回可以通过上述方法构造的、运算结果等于target的不同表达式的数目。

示例1：
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有5种方法让最终目标和为3。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

示例2：
输入：nums = [1], target = 1
输出：1

提示：
1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000
*/

// 剑指OfferII102加减的目标值

// 这也算是用01背包的方法进行计算么?
// 时间复杂度：O(n×(sum-target))。
// 空间复杂度：O(sum-target)。
int findTargetSumWays(int* nums, int numsSize, int target) {
  if (numsSize == 1 && nums[0] != target && nums[0] != -target) {
    return 0;
  }

  // 把所有的nums分成两组，一组加+，一组加-，和为target
  // 方程组：
  // left-right=target
  // left+right=sum
  // 求解：
  // left-(sum-left)=target
  // left=(sum+target)/2
  // 所以问题就变成了装满容量为x的背包，有几种方法
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  int dpsize = sum + target;
  if (dpsize % 2) {  // 此时没有方法，直接返回
    return 0;
  }
  dpsize /= 2;

  // 表示填满i(包括i)这么大容积的背包，有dp[i]种方法
  int dp[dpsize + 1];
  // dp[j]其他下标对应的数值应该初始化为0，从递归公式也可以看出，
  // dp[j]要保证是0的初始值，才能正确的由dp[j-nums[i]]推导出来。
  memset(dp, 0, sizeof(dp));  // 其他元素初始化为0，意义是？
  dp[0] = 1;  // 装满容量为0的背包，有一种方法，就是装0件物品
  for (int i = 0; i < numsSize; ++i) {
    for (int j = dpsize; j >= nums[i]; --j) {
      // 不考虑nums[i]的情况下，填满容量为j-nums[i]的背包，
      // 有dp[j-nums[i]]种方法；
      // 那么只要搞到nums[i]的话，凑成dp[j]就有dp[j-nums[i]]种方法。
      dp[j] += dp[j - nums[i]];
      // 求组合类问题的公式，都与上面的递推公式类似。
    }
  }

  return dp[dpsize];
}

class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    if (nums.size() == 1) {
      return abs(target) != abs(nums[0]) ? 0 : 1;
    }
    target += accumulate(nums.begin(), nums.end(), 0);
    if (target % 2) {
      return 0;
    }

    target /= 2;
    cout << target << endl;
    int m = nums.size();
    vector<vector<int>> dp(m, vector<int>(target + 1, 0));

    if (nums[0]) {
      dp[0][0] = 1;
      dp[0][nums[0]] = 1;
    } else {
      dp[0][0] = 2;  // 如果nums[0]==0，那么需要初始化为2
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 0; j <= target; ++j) {
        if (j < nums[i]) {
          dp[i][j] = dp[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];
        }
      }
    }

    return dp[m - 1][target];
  }
};

class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    if (nums.size() == 1 && abs(target) != abs(nums[0])) {
      return 0;
    }

    target += accumulate(nums.begin(), nums.end(), 0);
    if (target % 2) {
      return 0;
    }
    target /= 2;

    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < nums.size(); ++i) {
      for (int j = target; j >= nums[i]; --j) {
        dp[j] += dp[j - nums[i]];
      }
    }

    return dp[target];
  }
};
