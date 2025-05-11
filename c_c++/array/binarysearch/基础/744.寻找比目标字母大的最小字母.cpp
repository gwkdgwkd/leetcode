/*
给一个字符数组letters，该数组按非递减顺序排序，以及一个字符target。
letters里至少有两个不同的字符。
返回letters中大于target的最小的字符。
如果不存在这样的字符，则返回letters的第一个字符。

示例1：
输入: letters = ["c", "f", "j"]，target = "a"
输出: "c"
解释：letters中字典上比'a'大的最小字符是'c'。

示例2:
输入: letters = ["c","f","j"], target = "c"
输出: "f"
解释：letters中字典顺序上大于'c'的最小字符是'f'。

示例3:
输入: letters = ["x","x","y","y"], target = "z"
输出: "x"
解释：letters中没有一个字符在字典上大于'z'，所以返回letters[0]。


提示：
2 <= letters.length <= 10^4
letters[i]是一个小写字母
letters按非递减顺序排序
letters最少包含两个不同的字母
target是一个小写字母
*/

class Solution {
 public:
  char nextGreatestLetter(vector<char>& letters, char target) {
    if (letters[letters.size() - 1] <= target) {
      return letters[0];
    }
    int left = 0;
    int right = letters.size();
    while (left <= right) {
      int mid = left + (right - left) / 2;
      // 找大于target的最小的字符，就是找大于等于target+1的第一个元素，
      // 转换一下target = target + 1，即可转变为寻找lower bound的问题：
      if (letters[mid] < target + 1) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return letters[left];
  }
};