/*
稀疏数组搜索。
有个排好序的字符串数组，其中散布着一些空字符串，编写一种方法，找出给定字符串的位置。

示例1：
输入：words=["at","","","","ball","","","car","","","dad","",""],
s = "ta"
输出：-1
说明：不存在返回-1。

示例2：
输入：words=["at","","","","ball","","","car","","","dad","",""],
s = "ball"
输出：4

提示：words的长度在[1,1000000]之间
*/

int findString(char** words, int wordsSize, char* s) {
  int left = 0;
  int right = wordsSize - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (strcmp(words[left], s) != 0) {
      left++;
    } else {
      return left;
    }
    if (strcmp(words[right], s) != 0) {
      right--;
    } else {
      return right;
    }
    if (strcmp(words[mid], s) == 0) {
      return mid;
    }
  }
  return -1;
}

class Solution {
 public:
  int findString(vector<string>& words, string s) {
    int left = 0;
    int right = words.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (s == words[left]) {
        return left;
      } else {
        ++left;
      }

      if (s == words[right]) {
        return right;
      } else {
        --right;
      }

      if (words[mid] == s) {
        return mid;
      }
    }
    return -1;
  }
};