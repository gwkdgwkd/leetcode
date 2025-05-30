/*
给一个有序数组nums，请原地删除重复出现的元素，
使得出现次数超过两次的元素只出现两次，返回删除后数组的新长度。
不要使用额外的数组空间，必须在原地修改输入数组并在使用O(1)额外空间的条件下完成。
说明：为什么返回数值是整数，但输出的答案是数组呢？
请注意，输入数组是以引用方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
可以想象内部操作如下:
nums是以引用方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);
在函数里修改输入数组对于调用者是可见的。
根据你的函数返回的长度, 它会打印出数组中该长度范围内的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}

示例1：
输入：nums = [1,1,1,2,2,3]
输出：5, nums = [1,1,2,2,3]
解释：函数应返回新长度length = 5,
     并且原数组的前五个元素被修改为1, 1, 2, 2, 3。
     不需要考虑数组中超出新长度后面的元素。

示例2：
输入：nums = [0,0,1,1,1,1,2,3,3]
输出：7, nums = [0,0,1,1,2,3,3]
解释：函数应返回新长度length = 7,
     并且原数组的前七个元素被修改为0, 0, 1, 1, 2, 3, 3。
     不需要考虑数组中超出新长度后面的元素。


提示：
1 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4
nums已按升序排列
*/

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) {
      return n;
    }
    int slow = 2;
    int fast = 2;

    while (fast < n) {
      if (nums[slow - 2] != nums[fast]) {
        nums[slow++] = nums[fast];
      }
      ++fast;
    }
    return slow;
  }
};