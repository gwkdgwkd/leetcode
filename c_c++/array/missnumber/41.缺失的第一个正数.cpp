/*
给你一个未排序的整数数组nums，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为O(n)并且只使用常数级别额外空间的解决方案。

示例1：
输入：nums = [1,2,0]
输出：3

示例2：
输入：nums = [3,4,-1,1]
输出：2

示例3：
输入：nums = [7,8,9,11,12]
输出：1

提示：
1 <= nums.length <= 5 * 10^5
-2^31 <= nums[i] <= 2^31 - 1
*/

// 常数级别额外空间表示不能用哈希表，使用数组下标当做哈希的k
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int firstMissingPositive(int* nums, int numsSize) {
  // [3,4,-1,1]

  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] <= 0) {
      nums[i] = numsSize + 1;
    }
    // printf("%d ", nums[i]);
  }
  // printf("\n");  // 3 4 5 1

  for (int i = 0; i < numsSize; ++i) {
    int num = abs(nums[i]);
    if (num <= numsSize) {  // 数组中出现的数字
      // 把出现过的数字对应位置的数字设成负数
      nums[num - 1] = -abs(nums[num - 1]);
    }
  }
  // for (int i = 0; i < numsSize; ++i) {
  //   printf("%d ", nums[i]);
  // }
  // printf("\n");  // -3 4 -5 -1

  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] > 0) {  // 第一个非负数，就是缺失的第一个正整数
      return i + 1;
    }
  }

  return numsSize + 1;  // 如果都出现了，那么少的就是数组长度加1
}

class Solution {
  // 对于一个长度为N的数组，其中没有出现的最小正整数只能在[1,N+1]中。
  // 如果[1,N]都出现了，那么答案是N+1，否则答案是[1,N]中没有出现的最小正整数。
 public:
  int firstMissingPositive(vector<int>& nums) {
    int len = nums.size();

    // 算法的流程如下：
    // n = 6    3    4   -1    1    9   -5     1.将负数变为n+1
    //                    ↓              ↓
    // n = 6    3    4    7    1    9    7     2.将小于等于6的元素添加负号
    //        7->-7 1->-1    3->-3
    // n = 6   -3    4   -7   -1    9    7     3.返回第一个大于零的元素下标+1
    //             返回1+1

    // 1.将数组中所有小于等于0的数修改为N+1；
    for (int i = 0; i < len; ++i) {
      if (nums[i] <= 0) {
        nums[i] = len + 1;
      }
    }

    // 2.遍历数组中的每一个数x，它可能已经被打了标记，因此原本对应的数为∣x∣，
    //   如果∣x∣∈[1,N]，那么给数组中的第∣x∣−1个位置的数添加一个负号，
    //   注意如果它已经有负号，不需要重复添加；
    for (int i = 0; i < len; ++i) {
      int index = abs(nums[i]);
      if (index <= len) {
        nums[index - 1] = -abs(nums[index - 1]);
      }
    }

    // 3.在遍历完成之后，如果数组中的每一个数都是负数，那么答案是N+1，
    //   否则答案是第一个正数的位置加1。
    for (int i = 0; i < len; ++i) {
      if (nums[i] > 0) {
        return i + 1;
      }
    }

    return len + 1;
  }
};

// 置换
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int firstMissingPositive(int* nums, int numsSize) {
  // 给定的数组恢复成，数组的第x−1个元素为x，
  // 对数组进行一次遍历，对于遍历到的数x=nums[i]，如果x∈[1,N]，
  // 我们就知道x应当出现在数组中的x−1的位置，
  // 因此交换nums[i]和nums[x−1]，这样x就出现在了正确的位置。
  // 在完成交换后，新的nums[i]可能还在[1,N]的范围内，
  // 我们需要继续进行交换操作，直到x∉[1,N]。
  // 注意到上面的方法可能会陷入死循环。
  // 如果nums[i]恰好与nums[x−1]相等，那么就会无限交换下去。
  // 此时我们有nums[i]=x=nums[x−1]，说明x已经出现在了正确的位置。
  // 因此我们可以跳出循环，开始遍历下一个数。
  for (int i = 0; i < numsSize; ++i) {
    while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
      int t = nums[nums[i] - 1];
      nums[nums[i] - 1] = nums[i];
      nums[i] = t;
    }
  }

  // 在恢复后，数组应当有[1,2...N]的形式，但其中有若干个位置上的数是错误的，
  // 每一个错误的位置就代表了一个缺失的正数
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] != i + 1) {
      return i + 1;
    }
  }
  return numsSize + 1;
}

class Solution {
  // 可以使用置换的方法，将给定的数组恢复成下面的形式：
  // 如果数组中包含x∈[1,N]，那么恢复后，数组的第x−1个元素为x。
 public:
  int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();

    // 可以对数组进行一次遍历，对于遍历到的数x=nums[i]，如果x∈[1,N]，
    // 就知道xxx应当出现在数组中的x−1的位置，因此交换nums[i]和nums[x−1]，
    // 这样x就出现在了正确的位置，在完成交换后，
    // 新的nums[i]可能还在[1,N]的范围内，需要继续进行交换操作，直到x∉[1,N]。
    for (int i = 0; i < n; ++i) {
      // 可能会陷入死循环，如果nums[i]恰好与nums[x−1]相等，
      // 那么就会无限交换下去，此时有nums[i]=x=nums[x−1]，
      // 说明x已经出现在了正确的位置，因此可以跳出循环，开始遍历下一个数。
      while (0 < nums[i] && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
        swap(nums[nums[i] - 1], nums[i]);
      }
    }
    // 由于每次的交换操作都会使得某一个数交换到正确的位置，
    // 因此交换的次数最多为N，整个方法的时间复杂度为O(N)。

    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }

    return n + 1;
  }
};