/*
正在探访一家农场，农场从左到右种植了一排果树。
这些树用一个整数数组fruits表示，其中fruits[i]是第i棵树上的水果种类。
想要尽可能多地收集水果。
然而，农场的主人设定了一些严格的规矩，必须按照要求采摘水果：
只有两个篮子，并且每个篮子只能装单一类型的水果。
每个篮子能够装的水果总量没有限制。
可以选择任意一棵树开始采摘，必须从每棵树（包括开始采摘的树）上恰好摘一个水果。
采摘的水果应当符合篮子中的水果类型。
每采摘一次，将会向右移动到下一棵树，并继续采摘。
一旦走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
给一个整数数组fruits，返回你可以收集的水果的最大数目。

示例1：
输入：fruits = [1,2,1]
输出：3
解释：可以采摘全部3棵树。

示例2：
输入：fruits = [0,1,2,2]
输出：3
解释：可以采摘[1,2,2]这三棵树。
     如果从第一棵树开始采摘，则只能采摘[0,1]这两棵树。

示例3：
输入：fruits = [1,2,3,2,2]
输出：4
解释：可以采摘[2,3,2,2]这四棵树。
     如果从第一棵树开始采摘，则只能采摘[1,2]这两棵树。

示例4：
输入：fruits = [3,3,3,1,2,1,1,2,3,3,4]
输出：5
解释：可以采摘[1,2,1,1,2]这五棵树。


提示：
1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length
*/

class Solution {
 public:
  int totalFruit(vector<int>& fruits) {
    int n = fruits.size();
    unordered_map<int, int> cnt;
    int ans = 0;
    int right = 0;
    int left = 0;
    while (right < n) {
      cnt[fruits[right]]++;
      while (cnt.size() > 2) {
        int l = fruits[left++];
        if (--cnt[l] == 0) {
          cnt.erase(l);
        }
      }
      ans = max(ans, right - left + 1);
      ++right;
    }
    return ans;
  }
};