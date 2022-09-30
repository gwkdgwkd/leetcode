/*
字符串有三种编辑操作：插入一个字符、删除一个字符或者替换一个字符。
给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。

示例1:
输入:
first = "pale"
second = "ple"
输出: True

示例2:
输入:
first = "pales"
second = "pal"
输出: False
*/

bool oneEditAway(char* first, char* second) {
  if (strcmp(first, second) == 0) {
    return true;
  }

  int len_1 = strlen(first);
  int len_2 = strlen(second);
  if (abs(len_1 - len_2) > 1) {
    return false;
  }

  if (strcmp(first, "") == 0 || strcmp(second, "") == 0) {
    return true;
  }

  int times = 0;
  // 双指针
  int pos1 = 0;
  int pos2 = 0;
  while (pos1 < len_1 && pos2 < len_2) {
    if (times > 1) {
      return false;
    }
    if (first[pos1] == second[pos2]) {
      pos1++;
      pos2++;
      continue;
    } else {
      if (pos1 + 1 < len_1) {
        // 第一个字符串下一位与第二个字符串当前位置相同，位置1递增
        if (first[pos1 + 1] == second[pos2]) {
          pos1++;
          times++;
          continue;
        }
      }

      if (pos2 + 1 < len_2) {
        // 第二个字符串下一位与第一个字符串当前位置相同，位置2递增
        if (second[pos2 + 1] == first[pos1]) {
          pos2++;
          times++;
          continue;
        }
      }

      pos1++;
      pos2++;
      times++;
    }
  }

  // 返回条件
  // 1.times == 0；
  // 2.times == 1并且pos1和pos2均已到达对应字符末尾
  return (pos1 == len_1) && (pos2 == len_2) && (times == 1) || times == 0;
}

class Solution {
 public:
  bool oneEditAway(string first, string second) {
    int len1 = first.size();
    int len2 = second.size();
    if (abs(len1 - len2) > 1) {
      return false;
    }
    if (len1 < len2) {
      swap(first, second);
    }
    int diff = 0;
    for (int i = 0, j = 0; i < first.size(); ++i, ++j) {
      if (first[i] != second[j]) {
        if (++diff > 1) {
          return false;
        }
        if (len1 != len2) {  // 只有长度不等，second才原地踏步
          --j;  // second是短的，相当于这次循环没有后移j
        }
      }
    }
    return true;
  }
};