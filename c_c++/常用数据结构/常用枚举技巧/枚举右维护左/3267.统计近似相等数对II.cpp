/*
给一个正整数数组nums。
如果执行以下操作至多两次可以让两个整数x和y相等，那么我们称这个数对是近似相等的：
选择x或者y之一，将这个数字中的两个数位交换。
请返回nums中，下标i和j满足i < j且nums[i]和nums[j]近似相等的数对数目。
注意 ，执行操作后得到的整数可以有前导0。

示例1：
输入：nums = [1023,2310,2130,213]
输出：4
解释：近似相等数对包括：
     1023和2310。交换1023中数位1和2，然后交换数位0和3，得到2310。
     1023和213。交换1023中数位1和0，然后交换数位1和2，得到0213，也就是21 。
     2310和213。交换2310中数位2和0，然后交换数位3和2，得到0213，也就是213。
     2310和2130。交换2310中数位3和1，得到2130。

示例2：
输入：nums = [1,10,100]
输出：3
解释：近似相等数对包括：
     1和10。交换10中数位1和0，得到01，也就是1。
     1和100。交换100中数位1和从左往右的第二个0，得到001，也就是1。
     10和100。交换100中数位1 和从左往右的第一个0，得到010，也就是10。


提示：
2 <= nums.length <= 5000
1 <= nums[i] < 10^7
*/

class Solution {
  const int POW10[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

 public:
  int countPairs(vector<int>& nums) {
    ranges::sort(nums);
    int ans = 0, a[7];
    unordered_map<int, int> cnt;
    for (int x : nums) {
      unordered_set<int> st = {x};  // 不交换
      int m = 0;
      for (int v = x; v; v /= 10) {
        a[m++] = v % 10;
      }
      for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
          if (a[i] == a[j]) {  // 小优化
            continue;
          }
          int y = x + (a[j] - a[i]) * (POW10[i] - POW10[j]);
          st.insert(y);  // 交换一次
          swap(a[i], a[j]);
          for (int p = i + 1; p < m; p++) {
            for (int q = p + 1; q < m; q++) {
              st.insert(y + (a[q] - a[p]) * (POW10[p] - POW10[q]));  // 交换两次
            }
          }
          swap(a[i], a[j]);
        }
      }
      for (int v : st) {
        ans += cnt.contains(v) ? cnt[v] : 0;
      }
      cnt[x]++;
    }
    return ans;
  }
};
