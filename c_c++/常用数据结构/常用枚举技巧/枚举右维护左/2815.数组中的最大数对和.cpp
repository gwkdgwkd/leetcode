/*
给一个下标从0开始的整数数组nums。
请从nums中找出和最大的一对数，且这两个数数位上最大的数字相等。
返回最大和，如果不存在满足题意的数字对，返回-1。

示例1：
输入：nums = [51,71,17,24,42]
输出：88
解释：i=1和j=2，nums[i]和nums[j]数位上最大的数字相等，且总和71+17=88。
     i=3和j=4，nums[i]和nums[j]数位上最大的数字相等，且总和24+42=66。
     可以证明不存在其他数对满足数位上最大的数字相等，所以答案是88。

示例2：
输入：nums = [1,2,3,4]
输出：-1
解释：不存在数对满足数位上最大的数字相等。


提示：
2 <= nums.length <= 100
1 <= nums[i] <= 10^4
*/

class Solution {
 public:
  int maxSum(vector<int>& nums) {
    auto get = [](int num) {
      int ans = 0;
      while (num) {
        ans = max(ans, num % 10);
        num /= 10;
      }
      return ans;
    };

    unordered_map<int, priority_queue<int>> m;
    for (int num : nums) {
      m[get(num)].push(num);
    }

    int ans = -1;
    for (auto it = m.begin(); it != m.end(); it++) {
      if (it->second.size() < 2) {
        continue;
      }
      int a = it->second.top();
      it->second.pop();
      int b = it->second.top();
      ans = max(ans, a + b);
    }

    return ans;
  }
};

class Solution {
 public:
  int maxSum(vector<int>& nums) {
    int ans = -1;
    int max_val[10];
    ranges::fill(max_val, INT_MIN);  // 表示不存在最大值
    for (int v : nums) {
      int max_d = 0;
      for (int x = v; x; x /= 10) {
        max_d = max(max_d, x % 10);
      }
      ans = max(ans, v + max_val[max_d]);
      max_val[max_d] = max(max_val[max_d], v);
    }
    return ans;
  }
};
