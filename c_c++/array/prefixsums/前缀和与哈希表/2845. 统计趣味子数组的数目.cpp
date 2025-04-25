/*
给一个下标从0开始的整数数组nums，以及整数modulo和整数k。
请找出并统计数组中趣味子数组的数目。

如果子数组nums[l..r]满足下述条件，则称其为趣味子数组：
在范围[l, r]内，设cnt为满足nums[i]%modulo==k的索引i的数量。
并且cnt%modulo==k。

以整数形式表示并返回趣味子数组的数目。
注意：子数组是数组中的一个连续非空的元素序列。

示例1：
输入：nums = [3,2,4], modulo = 2, k = 1
输出：3
解释：在这个示例中，趣味子数组分别是：
子数组nums[0..0]，也就是[3]。
- 在范围[0, 0]内，只存在1个下标i = 0满足nums[i] % modulo == k。
- 因此cnt = 1，且cnt % modulo == k。
子数组nums[0..1]，也就是[3,2]。
- 在范围[0, 1]内，只存在1个下标i = 0满足 nums[i] % modulo == k。
- 因此cnt = 1，且cnt % modulo == k。
子数组nums[0..2]，也就是[3,2,4]。
- 在范围[0, 2]内，只存在1个下标i = 0满足nums[i] % modulo == k。
- 因此cnt = 1 ，且cnt % modulo == k。
可以证明不存在其他趣味子数组。因此，答案为3。

示例2：
输入：nums = [3,1,9,6], modulo = 3, k = 0
输出：2
解释：在这个示例中，趣味子数组分别是：
子数组nums[0..3]，也就是[3,1,9,6] 。
- 在范围[0, 3]内，只存在3个下标i = 0, 2, 3满足nums[i] % modulo == k。
- 因此cnt = 3，且cnt%modulo == k。
子数组 nums[1..1]，也就是[1]。
- 在范围[1, 1]内，不存在下标满足nums[i] % modulo == k。
- 因此cnt = 0，且 cnt%modulo == k。
可以证明不存在其他趣味子数组，因此答案为2。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= modulo <= 10^9
0 <= k < modulo
*/

/*
首先处理cnt，把满足nums[i]modmodulo=k的nums[i]视作1，不满足的视作0。
示例1的nums=[3,2,4],modulo=2,k=1，只有3%2=1，所以转化后得到数组a=[1,0,0]。
示例2的nums=[3,1,9,6],modulo=3,k=0，转化后得到数组a=[1,0,1,1]。

现在问题变成统计a的子数组中的1的个数，这等于子数组的元素和，于是问题转化成：
计算a中有多少个非空子数组b，满足b的元素和模modulo等于k。

子数组和问题，通常用前缀和处理。
求出a的前缀和数组s，问题转化成：
计算有多少个下标对(l,r)，满足0≤l<r≤n且(s[r]−s[l])%modulo=k。

对于初次接触模运算的同学，可以先从简单的情况开始思考：
想一想，如果k=0，要怎么做？这是1512.好数对的数目的取模加强版。

0≤k<modulo，所以(s[r]−s[l])%modulo=k等价于(s[r]−s[l])modmodulo=k%modulo

所以s[r]−s[l]与k关于模modulo同余。
由于模运算加减法封闭，可以移项，得(s[r]−k)modmodulo=s[l]%modulo。

思路：枚举右，维护左。
根据上式，可以一边枚举r，一边统计答案。
比如(s[r]−k)modmodulo=6，需要知道在r左侧有多少个s[l]%modulo也等于6，
这可以在遍历s的过程中，用哈希表（其实只需要数组）统计s[l]%modulo的出现次数。

细节：
由于a中只有0和1，所以s[l]≤n。
由于s[l]%modulo≤min(n,modulo−1)，不需要哈希表，用min(n+1,modulo)代替，效率更高。

此外，如果k>n，那么s[l]%modulo≤s[l]≤n<k，所有子数组都不满足要求，
直接返回0，不过这个优化不影响运行时间，可以不写。
*/

// 前缀和数组
class Solution {
 public:
  long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
    int len = nums.size();
    vector<int> sum(len + 1, 0);
    for (int i = 0; i < len; ++i) {
      sum[i + 1] = sum[i] + (nums[i] % modulo == k);
    }

    vector<int> cnt(min(len + 1, modulo));
    long long ans = 0;
    for (int s : sum) {
      if (s >= k) {
        ans += cnt[(s - k) % modulo];
      }
      cnt[s % modulo]++;
    }

    return ans;
  }
};

// 前缀和变量
class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(min(n,modulo))。
 public:
  long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
    vector<int> cnt(min((int)nums.size() + 1, modulo));

    cnt[0] = 1;  // 单独统计s[0]=0
    long long ans = 0;
    int s = 0;

    for (int x : nums) {
      s += x % modulo == k;

      if (s >= k) {
        ans += cnt[(s - k) % modulo];
      }

      cnt[s % modulo]++;
    }

    return ans;
  }
};

// 官方题解，前缀和
class Solution {
  // 时间复杂度：O(n)，其中n表示给定数组nums的长度，只需遍历一遍数组即可，为O(n)。
  // 空间复杂度：O(min(n,modulo))，其中n表示给定数组nums的长度，modulo表示给定的数字。
  // 需要用哈希表保存数组中每个元素对modulo取模的结果出现的次数，
  // 最多存在O(min(n,modulo))种不同的取模结果，因此需要的空间即为O(min(n,modulo))。

 public:
  long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
    int n = nums.size();
    unordered_map<int, int> cnt;
    long long res = 0;
    int prefix = 0;
    cnt[0] = 1;
    for (int i = 0; i < n; i++) {
      prefix += nums[i] % modulo == k;
      res += cnt[(prefix - k + modulo) % modulo];
      cnt[prefix % modulo]++;
    }
    return res;
  }
};
