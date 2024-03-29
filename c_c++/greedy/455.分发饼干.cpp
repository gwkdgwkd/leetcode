/*
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。
但是，每个孩子最多只能给一块饼干。
对每个孩子i，都有一个胃口值g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；
并且每块饼干j，都有一个尺寸s[j]。
如果s[j] >= g[i]，可以将这个饼干j分配给孩子i，这个孩子会得到满足。
你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

示例1：
输入： g = [1,2,3], s = [1,1]
输出： 1
解释：
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，
你只能让胃口值是1的孩子满足。
所以你应该输出1。

示例2：
输入： g = [1,2], s = [1,2,3]
输出： 2
解释：
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2。

提示：
1 <= g.length <= 3 * 10^4
0 <= s.length <= 3 * 10^4
1 <= g[i], s[j] <= 2^31 - 1
*/

// 贪心算法，本质是选择每一阶段的局部最优，从而达到全局最优
// 何验证可不可以用贪心算法呢？
// 最好用的策略就是举反例，如果想不到反例，那么就试一试贪心吧。
// 贪心算法一般分为如下四步：
// 1.将问题分解为若干个子问题；
// 2.找出适合的贪心策略；
// 3.求解每一个子问题的最优解；
// 4.将局部最优解堆叠成全局最优解。
// 贪心没有套路，说白了就是常识性推导加上举反例。
// 时间复杂度：快排O(nlogn) + 遍历O(n) = O(nlogn)。
int cmp(void* a, void* b) { return *(int*)a - *(int*)b; }
int findContentChildren(int* g, int gSize, int* s, int sSize) {
  // 可以尝试使用贪心策略，先将饼干数组和小孩数组排序。
  // 然后从后向前遍历小孩数组，用大饼干优先满足胃口大的，并统计满足小孩数量。
  qsort(g, gSize, sizeof(int), cmp);
  qsort(s, sSize, sizeof(int), cmp);

  int index = sSize - 1;
  int count = 0;
  // 这里的局部最优就是大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个，
  // 全局最优就是喂饱尽可能多的小孩：
  for (int i = gSize - 1; i >= 0; --i) {
    if (index >= 0 && g[i] <= s[index]) {
      --index;
      ++count;
    }
  }

  return count;
}

class Solution {
 public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int m = g.size();
    int n = s.size();
    int i = m - 1;
    int j = n - 1;
    int ans = 0;
    while (i >= 0 && j >= 0) {
      if (s[j] >= g[i]) {
        ++ans;
        --j;
      }
      --i;
    }

    return ans;
  }
};