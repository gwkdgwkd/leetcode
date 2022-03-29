/*
编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组s的形式给出。
不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用O(1)的额外空间解决这一问题。

示例1：
输入：s = ["h","e","l","l","o"]
输出：["o","l","l","e","h"]

示例2：
输入：s = ["H","a","n","n","a","h"]
输出：["h","a","n","n","a","H"]

提示：
1 <= s.length <= 105
s[i]都是ASCII码表中的可打印字符
*/

void reverseString(char* s, int sSize) {
  for (int start = 0, end = sSize - 1; start < end; ++start, --end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
  }

  return;
}

void reverseString(char* s, int sSize) {
  int left = 0, right = sSize - 1;
  int tmp;
  while (left < right) {
    tmp = s[right];
    s[right] = s[left];
    s[left] = tmp;
    ++left;
    --right;
  }
}