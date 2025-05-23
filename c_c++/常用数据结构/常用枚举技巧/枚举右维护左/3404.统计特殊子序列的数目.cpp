/*
给一个只包含正整数的数组nums。
特殊子序列是一个长度为4的子序列，用下标(p, q, r, s)表示，
它们满足p < q < r < s，且这个子序列必须满足以下条件：
nums[p] * nums[r] == nums[q] * nums[s]
相邻坐标之间至少间隔一个数字。换句话说，q - p > 1 ，r - q > 1且s - r > 1。
子序列指的是从原数组中删除零个或者更多元素后，剩下元素不改变顺序组成的数字序列。
请返回nums中不同特殊子序列的数目。

示例1：
输入：nums = [1,2,3,4,3,6,1]
输出：1
解释：nums中只有一个特殊子序列。
     (p, q, r, s) = (0, 2, 4, 6)：
     对应的元素为 (1, 3, 3, 1)。
     nums[p] * nums[r] = nums[0] * nums[4] = 1 * 3 = 3
     nums[q] * nums[s] = nums[2] * nums[6] = 3 * 1 = 3

示例2：
输入：nums = [3,4,3,4,3,4,3,4]
输出：3
解释：nums中共有三个特殊子序列。
     (p, q, r, s) = (0, 2, 4, 6) ：
        对应元素为(3, 3, 3, 3) 。
        nums[p] * nums[r] = nums[0] * nums[4] = 3 * 3 = 9
        nums[q] * nums[s] = nums[2] * nums[6] = 3 * 3 = 9
     (p, q, r, s) = (1, 3, 5, 7) ：
        对应元素为(4, 4, 4, 4) 。
        nums[p] * nums[r] = nums[1] * nums[5] = 4 * 4 = 16
        nums[q] * nums[s] = nums[3] * nums[7] = 4 * 4 = 16
     (p, q, r, s) = (0, 2, 5, 7) ：
        对应元素为(3, 3, 4, 4) 。
        nums[p] * nums[r] = nums[0] * nums[5] = 3 * 4 = 12
        nums[q] * nums[s] = nums[2] * nums[7] = 3 * 4 = 12


提示：
7 <= nums.length <= 1000
1 <= nums[i] <= 1000
*/

/*
本题由于数据范围只有[1,1000]，在这个范围内比较分数是否相等，
是无误的，所以也可以直接用浮点数计算。
什么情况下用浮点数是错的？
取两个接近1但不相同的分数a/(a+1)​和(a−1)/a​，根据IEEE754，
在使用双精度浮点数的情况下，如果这两个数的绝对差aa/(a+1)​比2^-52还小，
那么计算机可能会把这两个数舍入到同一个附近的浮点数上。
所以当a达到2^26的时候，算法就可能有问题了。
如果用单精度浮点数，就是当a达到2^11.5时才会有问题。所以本题用单精度浮点数也可以。
*/

// 枚举右，维护左
class Solution {
 public:
  long long numberOfSubsequences(vector<int>& nums) {
    int n = nums.size();
    long long ans = 0;
    unordered_map<float, int> cnt;
    // 枚举b和c
    for (int i = 4; i < n - 2; i++) {
      // 增量式更新，本轮循环只需枚举b=nums[i-2]这一个数，至于更前面的b，
      // 已经在前面的循环中添加到cnt中了，不能重复添加float b = nums[i - 2];
      // 枚举a
      for (int j = 0; j < i - 3; j++) {
        cnt[nums[j] / b]++;
      }

      float c = nums[i];
      // 枚举d
      for (int j = i + 2; j < n; j++) {
        ans += cnt[nums[j] / c];
      }
    }
    return ans;
  }
};

class Solution {
 public:
  long long numberOfSubsequences(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> suf;
    // 枚举c
    for (int i = 4; i < n - 2; i++) {
      int c = nums[i];
      // 枚举d
      for (int j = i + 2; j < n; j++) {
        int d = nums[j];
        int g = gcd(c, d);
        // 把分子和分母（两个short）压缩成一个int
        suf[(d / g) << 16 | (c / g)]++;
      }
    }

    long long ans = 0;
    // 枚举b
    for (int i = 2; i < n - 4; i++) {
      int b = nums[i];
      // 枚举a
      for (int j = 0; j < i - 1; j++) {
        int a = nums[j];
        int g = gcd(a, b);
        ans += suf[(a / g) << 16 | (b / g)];
      }
      // 撤销之前统计的d'/c'
      int c = nums[i + 2];
      for (int j = i + 4; j < n; j++) {
        int d = nums[j];
        int g = gcd(c, d);
        suf[(d / g) << 16 | (c / g)]--;
      }
    }
    return ans;
  }
};