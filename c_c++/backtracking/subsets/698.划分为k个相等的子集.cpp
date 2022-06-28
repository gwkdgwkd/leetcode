/*
给定一个整数数组nums和一个正整数k，找出是否有可能把这个数组分成k个非空子集，其总和都相等。

示例1：
输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成4个子集（5），（1,4），（2,3），（2,3）等于总和。

示例2:
输入: nums = [1,2,3,4], k = 3
输出: false

提示：
1 <= k <= len(nums) <= 16
0 < nums[i] < 10000
每个元素的频率在[1,4]范围内
*/

#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

// 回溯算法，以数字的视角，超时
// n个数字，每个数字有k个桶可供选择，所以组合出的结果个数为k^n，时间复杂度也就是O(k^n)。
int *bucket;
bool cmp(const void *a, const void *b) { return *(int *)a > *(int *)b; }
bool backtrack1(int *nums, int numsSize, int k, int index, int target) {
  if (index == numsSize) {
    // 检查所有桶的数字之和是否都是target
    for (int i = 0; i < k; ++i) {
      if (bucket[i] != target) {
        return false;
      }
    }
    return true;  // nums成功平分成k个子集
  }

  for (int i = 0; i < k; ++i) {  // 穷举nums[index]可能装入的桶
    if (bucket[i] + nums[index] > target) {  // 剪枝，桶装满了
      continue;
    }

    bucket[i] += nums[index];  // 将nums[index]装入bucket[i]
    // 递归穷举下一个数字的选择
    if (backtrack1(nums, numsSize, k, index + 1, target)) {
      return true;
    }
    bucket[i] -= nums[index];  // 撤销选择
  }

  return false;  // nums[index]装入哪个桶都不行
}
bool canPartitionKSubsets1(int *nums, int numsSize, int k) {
  if (k > numsSize) {
    return false;
  }
  bucket = (int *)calloc(k, sizeof(int));

  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % k) {
    return false;
  }

  qsort(nums, numsSize, sizeof(int), cmp);

  return backtrack1(nums, numsSize, k, 0, sum / k);
}

// 回溯算法，从桶的视角
// 每个桶要遍历n个数字，选择装入或不装入，组合的结果有2^n种；
// 而我们有k个桶，所以总的时间复杂度为O(k*2^n)。
// 当然，这是理论上的最坏复杂度，实际的复杂度肯定要好一些，毕竟我们添加了这么多剪枝逻辑。
// 不过，从复杂度的上界已经可以看出第一种思路要慢很多了。
// 通俗来说，我们应该尽量少量多次，就是说宁可多做几次选择，也不要给太大的选择空间；
// 宁可二选一选k次，也不要k选一选一次。
bool *used;
bool backtrack2(int *nums, int numsSize, int k, int start, int target,
                int bucket) {
  // base case
  if (k == 0) {
    // 所有桶都被装满了，而且nums一定全部用完了，因为target == sum / k
    return true;
  }
  if (bucket == target) {
    // 装满了当前桶，递归穷举下一个桶的选择，让下一个桶从nums[0]开始选数字
    return backtrack2(nums, numsSize, k - 1, 0, target, 0);
  }

  // 从start开始向后探查有效的nums[i]装入当前桶
  for (int i = start; i < numsSize; i++) {
    // 剪枝
    if (used[i]) {
      continue;  // nums[i]已经被装入别的桶中
    }
    if (nums[i] + bucket > target) {
      continue;  // 当前桶装不下nums[i]
    }
    // 做选择，将nums[i]装入当前桶中
    used[i] = true;
    bucket += nums[i];
    // 递归穷举下一个数字是否装入当前桶
    if (backtrack2(nums, numsSize, k, i + 1, target, bucket)) {
      return true;
    }
    // 撤销选择
    used[i] = false;
    bucket -= nums[i];
  }
  // 穷举了所有数字，都无法装满当前桶
  return false;
}
bool canPartitionKSubsets2(int *nums, int numsSize, int k) {
  if (k > numsSize) {
    return false;
  }
  used = (bool *)calloc(numsSize, sizeof(bool));

  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  if (sum % k) {
    return false;
  }

  return backtrack2(nums, numsSize, k, 0, sum / k, 0);
}

int main() {
  int nums1[] = {3522, 181, 521, 515,  304,  123,  2512, 312,
                 922,  407, 146, 1932, 4037, 2646, 3871, 269};

  printf("%d\n", canPartitionKSubsets1(nums1, sizeof(nums1) / sizeof(int), 5));
  printf("%d\n", canPartitionKSubsets2(nums1, sizeof(nums1) / sizeof(int), 5));
  int nums2[] = {2240, 3029, 520,  203, 1908, 505,  2600, 739,
                 696,  345,  1197, 76,  394,  2902, 1276};
  printf("%d\n", canPartitionKSubsets1(nums2, sizeof(nums2) / sizeof(int), 6));
  printf("%d\n", canPartitionKSubsets2(nums2, sizeof(nums2) / sizeof(int), 6));

  return 0;
}

// 比较慢
class Solution {
 public:
  bool backTracking(vector<int> &nums, vector<bool> &used, int k, int sum,
                    int &target, int startIndex) {
    if (k == 0) return true;  // 如果已经划分完毕了，返回true
    if (sum == target)
      return backTracking(nums, used, k - 1, 0, target,
                          0);  // 此次划分等于目标值

    for (int i = startIndex; i < nums.size(); ++i) {
      if (used[i])
        continue;
      else if (sum + nums[i] > target)
        continue;
      sum += nums[i];
      used[i] = true;
      if (backTracking(nums, used, k, sum, target, i + 1)) return true;
      used[i] = false;
      sum -= nums[i];
    }
    return false;
  }
  bool canPartitionKSubsets(vector<int> &nums, int k) {
    int numsSum = accumulate(nums.begin(), nums.end(), 0);
    if (numsSum % k != 0) return false;
    int target = numsSum / k;
    int maxNum = *max_element(nums.begin(), nums.end());
    if (maxNum > target) return false;
    vector<bool> used(nums.size(), false);
    return backTracking(nums, used, k, 0, target, 0);
  }
};

// 比较快
class Solution {
 public:
#define ll long long
  int vis[17];
  bool canPartitionKSubsets(vector<int> &nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    ll sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % k) return false;
    sum /= k;
    function<bool(int, int, int)> dfs = [&](int l, int cnt, int maxt) -> bool {
      if (cnt == 0) return 1;
      if (maxt == sum) return dfs(0, cnt - 1, 0);
      for (int i = l; i < n; ++i) {
        if (maxt + nums[i] > sum) break;
        if (vis[i]) continue;
        vis[i] = 1;
        if (dfs(i + 1, cnt, maxt + nums[i])) return 1;
        vis[i] = 0;
        while (i + 1 < n && nums[i + 1] == nums[i]) i++;
      }
      return 0;
    };
    return dfs(0, k, 0);
  }
};