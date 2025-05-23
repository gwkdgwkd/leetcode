/*
给一个下标从0开始的整数数组nums。
如果下标对i、j满足0 ≤ i < j < nums.length，
如果nums[i]的第一个数字和nums[j]的最后一个数字互质，
则认为nums[i]和nums[j]是一组美丽下标对。
返回nums中美丽下标对的总数目。
对于两个整数x和y，如果不存在大于1的整数可以整除它们，则认为x和y互质。
换而言之，如果gcd(x,y)==1，则认为x和y互质，其中gcd(x,y)是x和y的最大公因数。


示例1：
输入：nums = [2,5,1,4]
输出：5
解释：nums中共有5组美丽下标对：
     i=0和j=1：nums[0]第一个数是2，nums[1]最后一个数是5。2和5互质，gcd(2,5)==1。
     i=0和j=2：nums[0]第一个数是2，nums[2]最后一个数是1。2和1互质，gcd(2,1)==1。
     i=1和j=2：nums[1]第一个数是5，nums[2]最后一个数是1。5和1互质，gcd(5,1)==1。
     i=1和j=3：nums[1]第一个数是5，nums[3]最后一个数是4。5和4互质，gcd(5,4)==1。
     i=2和j=3：nums[2]第一个数是1，nums[3]最后一个数是4。1和4互质，gcd(1,4)==1。
     因此，返回5。

示例2：
输入：nums = [11,21,12]
输出：2
解释：共有2组美丽下标对：
     i=0和j=1：nums[0]的第一个数字是1，nums[1]的最后一个数字是1。gcd(1,1)==1。
     i=0和j=2：nums[0]的第一个数字是1，nums[2]的最后一个数字是2。gcd(1,2)==1。
     因此，返回 2 。


提示：
2 <= nums.length <= 100
1 <= nums[i] <= 9999
nums[i] % 10 != 0
*/

class Solution {
 public:
  int countBeautifulPairs(vector<int>& nums) {
    int ans = 0;
    int cnt[10]{};
    for (auto num : nums) {
      int r = num % 10;
      for (int i = 0; i < 10; ++i) {
        if (gcd(r, i) == 1) {
          ans += cnt[i];
        }
      }

      int l;
      while (num) {
        l = num % 10;
        num /= 10;
      }
      cnt[l]++;
    }
    return ans;
  }
};

class Solution {
 public:
  int countBeautifulPairs(vector<int>& nums) {
    int ans = 0, cnt[10]{};
    for (int x : nums) {
      for (int y = 1; y < 10; y++) {
        if (cnt[y] && gcd(y, x % 10) == 1) {
          ans += cnt[y];
        }
      }
      while (x >= 10) {
        x /= 10;
      }
      cnt[x]++;  // 统计最高位的出现次数
    }
    return ans;
  }
};
