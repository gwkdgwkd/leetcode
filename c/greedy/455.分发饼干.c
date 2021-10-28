// 贪心算法，本质是选择每一阶段的局部最优，从而达到全局最优
// 何验证可不可以用贪心算法呢？最好用的策略就是举反例，如果想不到反例，那么就试一试贪心吧。
// 贪心算法一般分为如下四步：
//  将问题分解为若干个子问题
//  找出适合的贪心策略
//  求解每一个子问题的最优解
//  将局部最优解堆叠成全局最优解
// 不好意思了，贪心没有套路，说白了就是常识性推导加上举反例。
// 时间复杂度：快排O(nlogn) + 遍历O(n) = O(nlogn)。
int cmp(void* a, void* b) { return *(int*)a - *(int*)b; }
int findContentChildren(int* g, int gSize, int* s, int sSize) {
  // 可以尝试使用贪心策略，先将饼干数组和小孩数组排序。
  // 然后从后向前遍历小孩数组，用大饼干优先满足胃口大的，并统计满足小孩数量。
  qsort(g, gSize, sizeof(int), cmp);
  qsort(s, sSize, sizeof(int), cmp);

  int index = sSize - 1;
  int count = 0;
  // 这里的局部最优就是大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个，全局最优就是喂饱尽可能多的小孩
  for (int i = gSize - 1; i >= 0; --i) {
    if (index >= 0 && g[i] <= s[index]) {
      --index;
      ++count;
    }
  }

  return count;
}