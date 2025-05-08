/*
给一个数组nums，它包含若干正整数。
一开始分数score = 0，请你按照下面算法求出最后分数：
从数组中选择最小且没有被标记的整数。如果有相等元素，选择下标最小的一个。
将选中的整数加到score中。
标记被选中元素，如果有相邻元素，则同时标记与它相邻的两个元素。
重复此过程直到数组中所有元素都被标记。
请返回执行上述算法后最后的分数。


示例1：
输入：nums = [2,1,3,4,5,2]
输出：7
解释：我们按照如下步骤标记元素：
     1是最小未标记元素，所以标记它和相邻两个元素：[2,1,3,4,5,2]。
     2是最小未标记元素，所以标记它和左边相邻元素：[2,1,3,4,5,2]。
     4是仅剩唯一未标记的元素，所以我们标记它：[2,1,3,4,5,2]。
     总得分为1 + 2 + 4 = 7。

示例2：
输入：nums = [2,3,5,1,3,2]
输出：5
解释：我们按照如下步骤标记元素：
     1是最小未标记元素，所以标记它和相邻两个元素：[2,3,5,1,3,2]。
     2是最小未标记元素，由于有两个2，我们选择最左边的一个2，
     也就是下标为0处的2，以及它右边相邻的元素：[2,3,5,1,3,2]。
     2是仅剩唯一未标记的元素，所以我们标记它：[2,3,5,1,3,2]。
     总得分为 1 + 2 + 2 = 5。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
*/

// 带着下标去排序
class Solution {
  // 时间复杂度：O(nlogn)，其中n为nums的长度。
  // 空间复杂度：O(n)。
 public:
  long long findScore(vector<int> &nums) {
    int n = nums.size(), ids[n];
    iota(ids, ids + n, 0);
    stable_sort(ids, ids + n, [&](int i, int j) { return nums[i] < nums[j]; });

    long long ans = 0;
    bool vis[n + 2];  // 保证下标不越界
    memset(vis, 0, sizeof(vis));
    for (int i : ids)
      if (!vis[i + 1]) {  // 避免-1，偏移一位
        vis[i] = vis[i + 2] = true;
        ans += nums[i];
      }

    return ans;
  }
};

// 转换 + 分组循环
class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  //           注意代码中的i只增不减，所以整个二重循环是O(n)的。
  // 空间复杂度：O(1)，仅用到若干额外变量。
 public:
  long long findScore(vector<int> &nums) {
    long long ans = 0;
    for (int i = 0, n = nums.size(); i < n; i += 2) {  // i选了i+1不能选
      int i0 = i;
      while (i + 1 < n && nums[i] > nums[i + 1])  // 找到下坡的坡底
        ++i;
      for (int j = i; j >= i0; j -= 2)  // 从坡底i到坡顶i0，每隔一个累加
        ans += nums[j];
    }
    return ans;
  }
};
