/*
给一个整数数组nums，数组中共有n个整数。
132模式的子序列由三个整数nums[i]、nums[j]和nums[k]组成，
并同时满足：i < j < k和nums[i] < nums[k] < nums[j]。
如果nums中存在132模式的子序列，返回true；否则，返回false。

示例1：
输入：nums = [1,2,3,4]
输出：false
解释：序列中不存在132模式的子序列。

示例2：
输入：nums = [3,1,4,2]
输出：true
解释：序列中有1个132模式的子序列：[1, 4, 2]。

示例3：
输入：nums = [-1,3,2,0]
输出：true
解释：序列中有3个132模式的的子序列：[-1, 3, 2]、[-1, 3, 0]和[-1, 2, 0]。


提示：
n == nums.length
1 <= n <= 2 * 10^5
-10^9 <= nums[i] <= 10^9
*/

// 单调栈
class Solution {
 public:
  bool find132pattern(vector<int>& nums) {
    stack<int> st;
    int n = nums.size(), k = INT_MIN;
    for (int i = n - 1; i >= 0; i--) {
      if (nums[i] < k) return true;
      while (!st.empty() and st.top() < nums[i]) {
        k = max(k, st.top());
        st.pop();
      }
      st.push(nums[i]);
    }
    return false;
  }
};

// 维护中间元素+贪心思想
// 对于nums[j]我们需要找到在他右边的比他小的数!
// 那么是否任意一个比他小的数都可以呢，其实不是的，
// 需要找到nums[j]右边最大的数nums[k]如果nums[k]>nums[i]，那么说明存在一个132模式
//  那么现在有3个问题：
//  1.为什么不是nums[j]右边任意一个比他小的数呢？比如说：5,7,10,4,8,9
//    假设我们遍历到10,发现10比4,5,6都要大,假设我们找的是4,
//    而4是4,5,6中最小的,同时我们保证5,7均大于4,如果选取4作为nums[k],
//    那么肯定无法组成132模式,但是实际上任意选一个5,7和10,9都是可以组成132模式的
//  2.如何找到nums[j]右边最大的那个nums[k]：
//    这可以通过单调栈来解决
//  3.如何找到并且快速判断nums[j] > nums[i]
//    可以用前缀和的思想
class Solution {
 public:
  bool find132pattern(vector<int>& nums) {
    int n = nums.size(), numsk = INT_MIN;
    vector<int> leftMin(n, INT_MAX);
    for (int i = 1; i < n; ++i) leftMin[i] = min(leftMin[i - 1], nums[i - 1]);
    stack<int> stk;
    for (int j = n - 1; j >= 0; --j) {
      while (!stk.empty() && stk.top() < nums[j]) {
        numsk = stk.top();  // 找到nums[j]右边最大的nums[k](其实有点贪心思想)
        stk.pop();
      }
      if (numsk > leftMin[j]) return true;
      stk.push(nums[j]);
    }
    return false;
  }
};