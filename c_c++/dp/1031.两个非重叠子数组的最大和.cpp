/*
给出非负整数数组A，返回两个非重叠（连续）子数组中元素的最大和，子数组的长度分别为L和M。
这里需要澄清的是，长为L的子数组可以出现在长为M的子数组之前或之后。
从形式上看，返回最大的V，而V=(A[i]+A[i+1]+...+A[i+L-1])+(A[j]+A[j+1]+...+A[j+M-1])
并满足下列条件之一：
0 <= i < i + L - 1 < j < j + M - 1 < A.length,或
0 <= j < j + M - 1 < i < i + L - 1 < A.length.

示例1：
输入：A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
输出：20
解释：子数组的一种选择中，[9]长度为1，[6,5]长度为2。

示例2：
输入：A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
输出：29
解释：子数组的一种选择中，[3,8,1]长度为3，[8,9]长度为2。

示例3：
输入：A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
输出：31
解释：子数组的一种选择中，[5,6,0,9]长度为4，[0,3,8]长度为3。

提示：
L >= 1
M >= 1
L + M <= A.length <= 1000
0 <= A[i] <= 1000
*/

// 前缀和 + 动态规划
#define max(a, b) ((a) > (b) ? (a) : (b))
int maxSumTwoNoOverlap(int* A, int ASize, int L, int M) {
  int* s;
  int prevMaxSum, sum, i, t;

  s = malloc((ASize + 1) * sizeof(int));
  s[0] = sum = 0;
  for (i = 1; i <= ASize; i++) s[i] = s[i - 1] + A[i - 1];

  // L、M前后关系的两种情况
  for (t = 0; t < 2; t++) {
    prevMaxSum = 0;
    for (i = L; i + M <= ASize; i++) {
      prevMaxSum = max(prevMaxSum, s[i] - s[i - L]);
      sum = max(sum, prevMaxSum + s[i + M] - s[i]);
    }
    // 借用prevMaxSum来交换一下L和M
    prevMaxSum = L;
    L = M;
    M = prevMaxSum;
  }

  free(s);
  return sum;
}

class Solution {
 public:
  int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
    int n = nums.size();
    vector<int> presum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      presum[i] = presum[i - 1] + nums[i - 1];
    }

    int sum = 0;
    // 然后分两种情况讨论：
    // 情况1，L在M左侧，可以考虑从左往右依次枚举M的起始点，M的起始点每向右移动一格，
    // L可以取的区间也右移一格，如果新的L区间，元素和更大，那么更新L的最大元素和。
    // 情况2，M在L左侧，过程同上，依葫芦画瓢重复一次即可。
    for (int k = 0; k < 2; ++k) {
      int firstsum = 0;
      // i表示右边子数组的起点：
      for (int i = firstLen; i + secondLen <= n; ++i) {
        firstsum = max(firstsum, presum[i] - presum[i - firstLen]);
        sum = max(sum, firstsum + presum[i + secondLen] - presum[i]);
      }
      swap(firstLen, secondLen);
    }
    return sum;
  }
};

class Solution {
 public:
  int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
    int ans = 0, n = nums.size(), s[n + 1];
    s[0] = 0;
    partial_sum(nums.begin(), nums.end(), s + 1);  // 计算nums的前缀和
    auto f = [&](int firstLen, int secondLen) {
      int maxSumA = 0;
      for (int i = firstLen + secondLen; i <= n; ++i) {
        maxSumA = max(maxSumA, s[i - secondLen] - s[i - secondLen - firstLen]);
        ans = max(ans, maxSumA + s[i] - s[i - secondLen]);
      }
    };
    f(firstLen, secondLen);  // 左a右b
    f(secondLen, firstLen);  // 左b右a
    return ans;
  }
};

class Solution {
 public:
  int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
    int n = nums.size(), s[n + 1];
    s[0] = 0;
    partial_sum(nums.begin(), nums.end(), s + 1);  // 计算nums的前缀和
    int ans = 0, maxSumA = 0, maxSumB = 0;
    for (int i = firstLen + secondLen; i <= n; ++i) {
      maxSumA = max(maxSumA, s[i - secondLen] - s[i - secondLen - firstLen]);
      maxSumB = max(maxSumB, s[i - firstLen] - s[i - firstLen - secondLen]);
      ans = max(ans, max(maxSumA + s[i] - s[i - secondLen],   // 左a右b
                         maxSumB + s[i] - s[i - firstLen]));  // 左b右a
    }
    return ans;
  }
};
