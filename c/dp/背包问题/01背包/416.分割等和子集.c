/*
给你一个只包含正整数的非空数组nums。
请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例1：
输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成[1, 5, 5]和[11] 。

示例2：
输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。

提示：
1 <= nums.length <= 200
1 <= nums[i] <= 100
*/

// 剑指OfferII101分割等和子集

// 官方题解
// 时间复杂度：
// 空间复杂度：O(n*sum)
bool canPartition(int* nums, int numsSize) {
  if (numsSize < 2) {
    return false;
  }
  int sum = 0, maxNum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
    maxNum = fmax(maxNum, nums[i]);
  }
  if (sum & 1) {
    return false;
  }
  int target = sum / 2;
  if (maxNum > target) {
    return false;
  }
  int dp[numsSize][target + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < numsSize; i++) {
    dp[i][0] = true;
  }
  dp[0][nums[0]] = true;
  for (int i = 1; i < numsSize; i++) {
    int num = nums[i];
    for (int j = 1; j <= target; j++) {
      if (j >= num) {
        dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
    if (dp[i][target]) {
      return true;
    }
  }
  return dp[numsSize - 1][target];
}

bool canPartition(int* nums, int numsSize) {
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % 2) {
    return false;
  } else {
    sum /= 2;
  }

  bool dp[numsSize + 1][sum + 1];
  for (int i = 0; i < numsSize + 1; ++i) {
    dp[i][0] = true;
  }
  for (int i = 1; i < sum + 1; ++i) {
    dp[0][i] = false;
  }

  for (int i = 1; i <= numsSize; ++i) {
    for (int j = 1; j <= sum; ++j) {
      if (nums[i - 1] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
      }
    }
    if (dp[i][sum]) {
      return true;
    }
  }
  return dp[numsSize][sum];
}

bool canPartition(int* nums, int numsSize) {
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % 2) {
    return false;
  } else {
    sum /= 2;
  }

  bool dp[sum + 1];
  dp[0] = true;
  for (int i = 1; i <= sum; ++i) {
    dp[i] = false;
  }

  for (int i = 0; i < numsSize; ++i) {
    for (int j = sum; j >= 0; --j) {
      if (j >= nums[i]) {
        dp[j] = dp[j] || dp[j - nums[i]];
      }
    }
  }
  return dp[sum];
}

// 官方题解，压缩空间
bool canPartition(int* nums, int numsSize) {
  if (numsSize < 2) {
    return false;
  }
  int sum = 0, maxNum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
    maxNum = fmax(maxNum, nums[i]);
  }
  if (sum & 1) {
    return false;
  }
  int target = sum / 2;
  if (maxNum > target) {
    return false;
  }
  int dp[target + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = true;
  for (int i = 0; i < numsSize; i++) {
    int num = nums[i];
    for (int j = target; j >= num; --j) {
      dp[j] |= dp[j - num];
    }
  }
  return dp[target];
}

// 按01背包的方式计算
// 空间复杂度：O(sum)
bool canPartition(int* nums, int numsSize) {
  if (numsSize < 2) {
    return false;
  }
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % 2) {
    return false;
  }
  sum /= 2;

  int dp[sum + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < numsSize; ++i) {
    for (int j = sum; j >= nums[i]; --j) {
      dp[j] = fmax(dp[j], dp[j - nums[i]] + nums[i]);
    }
  }

  // 如果dp[sum]==sum，说明可以将这个数组分割成两个子集，使得两个子集的元素和相等
  return dp[sum] == sum;
}
