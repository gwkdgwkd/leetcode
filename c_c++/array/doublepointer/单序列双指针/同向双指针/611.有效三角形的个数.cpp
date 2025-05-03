/*
给定一个包含非负整数的数组nums，返回其中可以组成三角形三条边的三元组个数。

示例1：
输入：nums = [2,2,3,4]
输出：3
解释：有效的组合是:
     2,3,4 (使用第一个2)
     2,3,4 (使用第二个2)
     2,2,3

示例2：
输入：nums = [4,2,3,4]
输出：4


提示：
1 <= nums.length <= 1000
0 <= nums[i] <= 1000
*/

// 枚举最长边+相向双指针
class Solution {
 public:
  int triangleNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int ans = 0;
    int n = nums.size();
    for (int i = 2; i < n; ++i) {
      int c = nums[i];
      int left = 0;
      int right = i - 1;
      while (left < right) {
        if (nums[left] + nums[right] > c) {
          // 由于nums已经从小到大排序，nums[left]+nums[right]>c同时意味着：
          // nums[i+1]+nums[j]>c
          // nums[i+2]+nums[j]>c
          // ...
          // nums[j-1]+nums[j]>c
          // 从left到right一共j-i个：
          ans += right - left;
          --right;
        } else {
          // 由于 nums 已经从小到大排序，nums[i]+nums[j]<=c同时意味着：
          // nums[i]+nums[j-1]<=c
          // ...
          // nums[i]+nums[i+1]<=c
          // 所以在后续的内层循环中，nums[i]不可能作为三角形的边长，没有用了：
          ++left;
        }
      }
    }
    return ans;
  }
};

// 优化
class Solution {
  // 时间复杂度：O(n2)，其中n为nums的长度。
  // 空间复杂度：O(1)。不计入排序的栈开销，仅用到若干额外变量。
 public:
  int triangleNumber(vector<int>& nums) {
    ranges::sort(nums);
    int ans = 0;
    for (int k = nums.size() - 1; k > 1; k--) {  // 首先把循环改成倒序枚举k
      int c = nums[k];
      // 优化一：
      // 在执行双指针之前，如果发现最小的a和b相加大于c，也就是nums[0]+nums[1]>nums[k]，
      // 说明从nums[0]到nums[k]中任选三个数a,b,c都满足a+b>c，
      // 那么直接把Ck+13​=6(k+1)k(k−1)​加入答案，退出外层循环。
      // 这是为什么要倒序枚举k的原因，正序枚举没法退出外层循环。
      if (nums[0] + nums[1] > c) {
        ans += (k + 1) * k * (k - 1) / 6;
        break;
      }

      // 优化二：
      // 在执行双指针之前，如果发现最大的a和b相加小于等于c，
      // 也就是nums[k−2]+nums[k−1]≤nums[k]，
      // 说明不存在a+b>c，不执行双指针，继续外层循环。
      if (nums[k - 2] + nums[k - 1] <= c) {
        continue;
      }

      int i = 0;      // a=nums[i]
      int j = k - 1;  // b=nums[j]
      while (i < j) {
        if (nums[i] + nums[j] > c) {
          ans += j - i;
          j--;
        } else {
          i++;
        }
      }
    }

    return ans;
  }
};

/* 枚举最短边 + 同向双指针
枚举最短边a，问题变成计算满足c−b<a的(b,c)个数。
这个条件意味着，当a固定不变时，b和c不能隔太远。
这可以用同向双指针解决，
枚举a=nums[i]，其中 i=0,1,2,…,n−3。
如果a=0，则跳过。
现在计算，对于k=i+2,i+3,…,n−1，有多少个符合要求的j？。
枚举k的同时，维护指针j，初始值为i+1。
如果发现nums[k]−nums[j]≥a，说明b和c隔太远了，那么把j不断加一，
直到c−b<a，也就是nums[k]−nums[j]<a为止。
此时，对于固定的a=nums[i]和固定的c=nums[k]，nums[j],nums[j+1],…,nums[k−1]，
都可以作为b，这一共有k−j个，加入答案。
*/
class Solution {
 public:
  int triangleNumber(vector<int>& nums) {
    ranges::sort(nums);
    int n = nums.size(), ans = 0;
    for (int i = 0; i < n - 2; i++) {
      int a = nums[i];
      if (a == 0) {  // 三角形的边不能是0
        continue;
      }
      int j = i + 1;
      for (int k = i + 2; k < n; k++) {
        while (nums[k] - nums[j] >= a) {
          j++;
        }
        // 如果a=nums[i]和c=nums[k]固定不变
        // 那么b可以是nums[j],nums[j+1],...,nums[k-1]，一共有k-j个
        ans += k - j;
      }
    }

    return ans;
  }
};