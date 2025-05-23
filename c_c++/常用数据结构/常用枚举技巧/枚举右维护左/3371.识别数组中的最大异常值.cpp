/*
给一个整数数组nums。该数组包含n个元素，其中恰好有n-2个元素是特殊数字。
剩下的两个元素中，一个是所有特殊数字的和，另一个是异常值。
异常值的定义是：既不是原始特殊数字之一，也不是所有特殊数字的和。
注意，特殊数字、和以及异常值的下标必须不同，但可以共享相同的值。
返回nums中可能的最大异常值。

示例1：
输入：nums = [2,3,5,10]
输出：10
解释：特殊数字可以是2和3，因此和为5，异常值为10。

示例2：
输入：nums = [-2,-1,-3,-6,4]
输出：4
解释：特殊数字可以是-2、-1和-3，因此和为-6，异常值为4。

示例3：
输入：nums = [1,1,1,1,1,5,5]
输出：5
解释：特殊数字可以是1、1、1、1和1，因此和为5，另一个5为异常值。


提示：
3 <= nums.length <= 10^5
-1000 <= nums[i] <= 1000
输入保证nums中至少存在一个可能的异常值。
*/

/*
设异常值为x，元素和为y，那么其余n−2个数的和也是y，
所以x+2y就是整个nums数组的元素和total，即x+2y=total，
也就是说，问题相当于从nums中选出两个（下标不同的）数x和y，满足x+2y等于一个定值。
需要计算x的最大值是多少。
枚举异常值x=nums[i]，那么有2y=total−x，
如果total−x是偶数，且y=(total−x​)/2在（除去x的）其余n−1个数中，那么x就是一个异常值。
*/

// 枚举异常值
class Solution {
 public:
  int getLargestOutlier(vector<int>& nums) {
    unordered_map<int, int> cnt;
    int total = 0;
    for (int x : nums) {
      cnt[x]++;
      total += x;
    }

    int ans = INT_MIN;
    for (int x : nums) {
      cnt[x]--;
      if ((total - x) % 2 == 0 && cnt[(total - x) / 2] > 0) {
        ans = max(ans, x);
      }
      cnt[x]++;
    }
    return ans;
  }
};

// 枚举异常值
// 枚举y=nums[i]，那么异常值等于total−2y
// 如果total−2y在（去掉y之后的）哈希表中，那么total−2y就是一个异常值。
class Solution {
 public:
  int getLargestOutlier(vector<int>& nums) {
    unordered_map<int, int> cnt;
    int total = 0;
    for (int x : nums) {
      cnt[x]++;
      total += x;
    }

    int ans = INT_MIN;
    for (int x : nums) {
      if ((total - x) % 2 == 0) {
        int y = (total - x) / 2;
        auto it = cnt.find(y);
        if (it != cnt.end() && (y != x || it->second > 1)) {
          ans = max(ans, x);
        }
      }
    }
    return ans;
  }
};

// 枚举元素和
class Solution {
 public:
  int getLargestOutlier(vector<int>& nums) {
    unordered_map<int, int> cnt;
    int total = 0;
    for (int x : nums) {
      cnt[x]++;
      total += x;
    }

    int ans = INT_MIN;
    for (int y : nums) {
      int t = total - y * 2;
      auto it = cnt.find(t);
      if (it != cnt.end() && (t != y || it->second > 1)) {
        ans = max(ans, t);
      }
    }
    return ans;
  }
};