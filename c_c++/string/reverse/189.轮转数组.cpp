/*
给你一个数组，将数组中的元素向右轮转k个位置，其中k是非负数。

示例1:
输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右轮转1步: [7,1,2,3,4,5,6]
向右轮转2步: [6,7,1,2,3,4,5]
向右轮转3步: [5,6,7,1,2,3,4]

示例2:
输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释:
向右轮转1步: [99,-1,-100,3]
向右轮转2步: [3,99,-1,-100]

提示：
1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5

进阶：
尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
你可以使用空间复杂度为O(1)的原地算法解决这个问题吗？
*/

// 时间复杂度：O(n)
// 空间复杂度：O(n)
void rotate(int* nums, int numsSize, int k) {
  int newArr[numsSize];
  for (int i = 0; i < numsSize; ++i) {
    newArr[(i + k) % numsSize] = nums[i];
  }
  for (int i = 0; i < numsSize; ++i) {
    nums[i] = newArr[i];
  }
}

// 环状替换
// 时间复杂度：O(n)，每个元素只会被遍历一次。
// 空间复杂度：O(1)
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void swap(int* a, int* b) {
  int t = *a;
  *a = *b, *b = t;
}
void rotate(int* nums, int numsSize, int k) {
  k = k % numsSize;
  int count = gcd(k, numsSize);  // 最大公约数
  for (int start = 0; start < count; ++start) {
    int current = start;
    int prev = nums[start];
    do {
      int next = (current + k) % numsSize;
      swap(&nums[next], &prev);
      current = next;
    } while (start != current);
  }
}

// 时间复杂度：O(n)，每个元素被翻转两次
// 空间复杂度：O(1)
void reverse(int* nums, int left, int right) {
  for (int l = left, r = right; l < r; ++l, --r) {
    int temp = nums[l];
    nums[l] = nums[r];
    nums[r] = temp;
  }
}
void rotate(int* nums, int numsSize, int k) {
  k %= numsSize;
  reverse(nums, 0, numsSize - 1);
  reverse(nums, 0, k - 1);
  reverse(nums, k, numsSize - 1);
}

class Solution {
  void reverse(vector<int>& nums, int left, int right) {
    while (left < right) {
      swap(nums[left], nums[right]);
      ++left;
      --right;
    }
  }

 public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    reverse(nums, 0, n - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, n - 1);
  }
};

// 剑指Offer58-II左旋转字符串
// 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
// 请定义一个函数实现字符串左旋转操作的功能。
// 比如，输入字符串abcdefg和数字2，
// 该函数将返回左旋转两位得到的结果cdefgab。
void reverse(char* s, int left, int right) {
  while (left < right) {
    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    ++left;
    --right;
  }
}
char* reverseLeftWords(char* s, int n) {
  int len = strlen(s);
  reverse(s, 0, len - 1);
  reverse(s, 0, len - n - 1);
  reverse(s, len - n, len - 1);
  return s;
}