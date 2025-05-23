/*
给一个下标从0开始的数组nums，数组中的元素都是正整数。
请选出两个下标i和j（i!=j），且nums[i]的数位和与nums[j]的数位和相等。
请找出所有满足条件的下标i和j，找出并返回nums[i]+nums[j]可以得到的最大值。
如果不存在这样的下标对，返回-1。

示例1：
输入：nums = [18,43,36,13,7]
输出：54
解释：满足条件的数对(i,j)为：
     (0,2)，两个数字的数位和都是9，相加得到18 + 36 = 54。
     (1,4)，两个数字的数位和都是7，相加得到43 + 7 = 50。
     所以可以获得的最大和是54。

示例2：
输入：nums = [10,12,19,14]
输出：-1
解释：不存在满足条件的数对，返回-1。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
*/

class Solution {
 public:
  int maximumSum(vector<int>& nums) {
    auto count = [](int num) {
      int ans = 0;
      while (num) {
        ans += num % 10;
        num /= 10;
      }
      return ans;
    };

    int n = nums.size();
    unordered_map<int, priority_queue<int>> m;
    for (auto num : nums) {
      m[count(num)].push(num);
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
  int maximumSum(vector<int>& nums) {
    int ans = -1;
    int mx[82]{};  // 至多9个9相加
    for (int num : nums) {
      int s = 0;                       // num的数位和
      for (int x = num; x; x /= 10) {  // 枚举num的每个数位
        s += x % 10;
      }
      if (mx[s]) {  // 说明左边也有数位和等于s的元素
        ans = max(ans, mx[s] + num);  // 更新答案的最大值
      }
      mx[s] = max(mx[s], num);  // 维护数位和等于s的最大元素
    }
    return ans;
  }
};