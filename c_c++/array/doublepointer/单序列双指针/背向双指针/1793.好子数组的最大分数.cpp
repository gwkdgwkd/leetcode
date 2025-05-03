/*
给一个整数数组nums（下标从0开始）和一个整数k。
一个子数组(i, j)的分数定义为min(nums[i],nums[i+1],...,nums[j])*(j-i +1)。
一个好子数组的两个端点下标需要满足i <= k <= j。
请返回好子数组的最大可能分数。

示例1：

输入：nums = [1,4,3,7,4,5], k = 3
输出：15
解释：最优子数组的左右端点下标是(1, 5)，
     分数为min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15。

示例2：
输入：nums = [5,5,4,5,4,1,1,1], k = 0
输出：20
解释：最优子数组的左右端点下标是(0, 4)，
     分数为 min(5,5,4,5,4) * (4-0+1) = 4 * 5 = 20。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 2 * 10^4
0 <= k < nums.length
*/

/* 双指针
例如nums=[1,9,7,8,8,1],k=3。
其中面积最大的矩形，左边界下标L=1，右边界下标R=4。
尝试从i=k,j=k出发，通过不断移动指针来找到最大矩形。
比较nums[i−1]和nums[j+1]的大小，谁大就移动谁（一样大移动哪个都可以）。

定理：按照这种移动方式，一定会在某个时刻恰好满足i=L且j=R。
证明：
如果i先到达L，那么此时j<R。
设L到R之间的最小元素为m，在方法一中知道nums[L−1]<m，
由于nums[i−1]=nums[L−1]<m≤nums[j+1]，那么后续一定是j一直向右移动到R。
对于j先到达R的情况也同理，所以一定会在某个时刻恰好满足i=L且j=R。
在移动过程中，不断用nums[i]和nums[j]更新矩形高度的最小值minH，
同时用minH*(j−i+1)更新答案的最大值。
*/
class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(1)，仅用到若干额外变量。
 public:
  int maximumScore(vector<int>& nums, int k) {
    int n = nums.size();
    int left = k;
    int right = k;
    int ans = nums[k];
    int h = nums[k];
    for (int i = 0; i < n - 1; ++i) {  // 循环n-1次
      if (right == n - 1 || (left > 0 && nums[left - 1] > nums[right + 1])) {
        h = min(h, nums[--left]);
      } else {
        h = min(h, nums[++right]);
      }
      ans = max(ans, h * (right - left + 1));
    }
    return ans;
  }
};

/* 单调栈
和84.柱状图中最大的矩形是一样的，计算的是最大矩形面积。
只不过多了一个约束：矩形必须包含下标k。

假设h=nums[p]是矩形的高度，那么矩形的宽度最大是多少？需要知道：
在p左侧的小于h的最近元素的下标left。
在p右侧的小于h的最近元素的下标right。
这可以用单调栈求出。
那么矩形的宽度就是right−left−1，矩形面积为h*(right−left−1)。
对于本题，如果下标k在开区间(left,right)中，
就说明矩形包含下标k，用矩形面积更新答案的最大值。
*/
class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(n)。
 public:
  int maximumScore(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> left(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
      while (!st.empty() && nums[i] <= nums[st.top()]) {
        st.pop();
      }
      if (!st.empty()) {
        left[i] = st.top();
      }
      st.push(i);
    }

    vector<int> right(n, n);
    st = stack<int>();
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && nums[i] <= nums[st.top()]) {
        st.pop();
      }
      if (!st.empty()) {
        right[i] = st.top();
      }
      st.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      int h = nums[i], l = left[i], r = right[i];
      if (l < k && k < r) {  // 相比 84 题多了个 if 判断
        ans = max(ans, h * (r - l - 1));
      }
    }
    return ans;
  }
};
