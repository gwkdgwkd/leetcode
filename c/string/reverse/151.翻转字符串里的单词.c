/*
给你一个字符串s，颠倒字符串中单词的顺序。
单词是由非空格字符组成的字符串。s中使用至少一个空格将字符串中的单词分隔开。
返回单词顺序颠倒且单词之间用单个空格连接的结果字符串。
注意：输入字符串s中可能会存在前导空格、尾随空格或者单词间的多个空格。
返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

示例1：
输入：s = "the sky is blue"
输出："blue is sky the"

示例2：
输入：s = "  hello world  "
输出："world hello"
解释：颠倒后的字符串中不能存在前导空格和尾随空格。

示例3：
输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，颠倒后的字符串需要将单词间的空格减少到仅有一个。

提示：
1 <= s.length <= 10^4
s包含英文大小写字母、数字和空格' '
s中至少存在一个 单词

进阶：如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用O(1)额外空间复杂度的原地解法。
*/

// 剑指Offer58-I翻转单词顺序

int removeSpace(char* s, int len, char val) {
  int slowIndex = 0, fastIndex = 0;  // 定义快指针，慢指针
  // 去掉字符串前面的空格
  while (len > 0 && fastIndex < len && s[fastIndex] == ' ') {
    fastIndex++;
  }
  for (; fastIndex < len; fastIndex++) {
    // 去掉字符串中间部分的冗余空格
    if (fastIndex - 1 > 0 && s[fastIndex - 1] == s[fastIndex] &&
        s[fastIndex] == ' ') {
      continue;
    } else {
      s[slowIndex++] = s[fastIndex];
    }
  }
  if (slowIndex - 1 > 0 && s[slowIndex - 1] == ' ') {  // 去掉字符串末尾的空格
    s[slowIndex - 1] = 0;
    return slowIndex;
  } else {
    s[slowIndex] = 0;  // 重新设置字符串大小
    return slowIndex + 1;
  }
}

void reverseString(char* s, int sSize) {
  for (int start = 0, end = sSize - 1; start < end; ++start, --end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
  }

  return;
}

char* reverseWords(char* s) {
  int len = removeSpace(s, strlen(s), ' ');
  reverseString(s, len - 1);

  int start;
  for (int i = 0; i < len; ++i) {
    if (i == 0 || (i > 0 && s[i - 1] == ' ')) {
      start = i;
    }
    if (s[i] == ' ' || i == len - 1) {
      reverseString(s + start, i - start);
    } else {
      continue;
    }
  }
  return s;
}