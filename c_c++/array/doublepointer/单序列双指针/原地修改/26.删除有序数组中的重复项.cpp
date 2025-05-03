/*
给一个升序排列的数组nums，请原地删除重复出现的元素，
使每个元素只出现一次，返回删除后数组的新长度。
元素的相对顺序应该保持一致。
由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。
更规范地说，如果在删除重复项之后有k个元素，那么nums的前k个元素应该保存最终结果。
将最终结果插入nums的前k个位置后返回k。
不要使用额外的空间，你必须在原地修改输入数组并在使用O(1)额外空间的条件下完成。

判题标准：
系统会用下面的代码来测试你的题解：
int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案
int k = removeDuplicates(nums); // 调用
assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
如果所有断言都通过，那么您的题解将被通过。

示例1：
输入：nums = [1,1,2]
输出：2, nums = [1,2]
解释：函数应该返回新的长度2，并且原数组nums的前两个元素被修改为1,2。
     不需要考虑数组中超出新长度后面的元素。

示例2：
输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]
解释：函数应该返回新的长度5，并且原数组nums的前五个元素被修改为0,1,2,3,4。
     不需要考虑数组中超出新长度后面的元素。

提示：
0 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4
nums已按升序排列
*/

// 双指针，与27类似
int removeDuplicates(int* nums, int numsSize) {
  if (numsSize == 0) return 0;
  int fast = 1;
  int slow = 1;
  while (fast < numsSize) {
    if (nums[fast - 1] != nums[fast]) {
      nums[slow++] = nums[fast];
    }
    fast++;
  }

  return slow;
}

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int slow = 1;
    int fast = 1;
    int len = nums.size();

    while (fast < len) {
      if (nums[fast - 1] != nums[fast]) {
        nums[slow++] = nums[fast];
      }
      ++fast;
    }

    return slow;
  }
};

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int slow = 0;
    int fast = 0;
    int len = nums.size();

    while (fast < len) {
      if (nums[slow] != nums[fast]) {
        nums[++slow] = nums[fast];
      }
      ++fast;
    }

    return slow + 1;
  }
};
