/*
给你一个整数数组arr和一个整数difference，
请你找出并返回arr中最长等差子序列的长度，该子序列中相邻元素之间的差等于difference。
子序列是指在不改变其余元素顺序的情况下，通过删除一些元素或不删除任何元素而从arr派生出来的序列。

示例1：
输入：arr = [1,2,3,4], difference = 1
输出：4
解释：最长的等差子序列是[1,2,3,4]。

示例2：
输入：arr = [1,3,5,7], difference = 1
输出：1
解释：最长的等差子序列是任意单个元素。

示例3：
输入：arr = [1,5,7,8,5,3,4,2,1], difference = -2
输出：4
解释：最长的等差子序列是[7,5,3,1]。

提示：
1 <= arr.length <= 10^5
-10^4 <= arr[i], difference <= 10^4
*/

// 动态规划，超时，与300类似
int longestSubsequence(int* arr, int arrSize, int difference) {
  int dp[arrSize];
  for (int i = 0; i < arrSize; ++i) {
    dp[i] = 1;
  }

  int max = dp[0];
  for (int i = 1; i < arrSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[i] - arr[j] == difference) {
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      max = fmax(max, dp[i]);
    }
  }

  return max;
}

// 用空间换时间
int longestSubsequence(int* arr, int arrSize, int difference) {
  int ans = 0;
  int dp[200000] = {1};  // 第一个值为1
  for (int i = 0; i < arrSize; i++) {
    arr[i] += 100000;
    dp[arr[i]] = dp[arr[i] - difference] + 1;
    ans = fmax(ans, dp[arr[i]]);
  }
  return ans;
}

class Solution {
 public:
  int longestSubsequence(vector<int>& arr, int difference) {
    int n = arr.size();
    vector<int> dp(n, 1);

    int max = dp[0];

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (arr[i] - arr[j] == difference) {
          dp[i] = std::max(dp[i], dp[j] + 1);
          max = std::max(max, dp[i]);
        }
      }
    }

    return max;
  }
};

class Solution {
 public:
  int longestSubsequence(vector<int>& arr, int difference) {
    int n = arr.size();
    unordered_map<int, int> dp;

    int max = 0;
    for (int i = 0; i < n; ++i) {
      auto it = dp.find(arr[i] - difference);
      if (it != dp.end()) {
        dp[arr[i]] = it->second + 1;

      } else {
        dp[arr[i]] = 1;
      }
      max = std::max(max, dp[arr[i]]);
    }

    return max;
  }
};
