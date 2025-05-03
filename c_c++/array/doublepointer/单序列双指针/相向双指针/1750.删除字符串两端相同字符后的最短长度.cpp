/*
给一个只包含字符'a'，'b'和'c'的字符串s，可以执行下面这个操作（5个步骤）任意次：
选择字符串s一个非空的前缀，这个前缀的所有字符都相同。
选择字符串s一个非空的后缀，这个后缀的所有字符都相同。
前缀和后缀在字符串中任意位置都不能有交集。
前缀和后缀包含的所有字符都要相同。
同时删除前缀和后缀。
请返回对字符串s执行上面操作任意次以后（可能0次），能得到的最短长度。

示例1：
输入：s = "ca"
输出：2
解释：没法删除任何一个字符，所以字符串长度仍然保持不变。

示例2：
输入：s = "cabaabac"
输出：0
解释：最优操作序列为：
     选择前缀"c"和后缀"c"并删除它们，得到s="abaaba"。
     选择前缀"a"和后缀"a"并删除它们，得到s="baab"。
     选择前缀"b"和后缀"b"并删除它们，得到s="aa"。
     选择前缀"a"和后缀"a"并删除它们，得到s=""。

示例3：
输入：s = "aabccabba"
输出：3
解释：最优操作序列为：
     选择前缀"aa"和后缀"a"并删除它们，得到s = "bccabb"。
     选择前缀"b"和后缀"bb"并删除它们，得到s = "cca"。


提示：
1 <= s.length <= 10^5
s只包含字符'a'，'b'和'c'。
*/

class Solution {
 public:
  int minimumLength(string s) {
    int left = 0;
    int right = s.size() - 1;
    while (left < right && s[left] == s[right]) {
      while (left + 1 < right && s[left] == s[left + 1]) {
        ++left;
      }
      while (left < right - 1 && s[right] == s[right - 1]) {
        --right;
      }
      ++left;
      --right;
    }

    return right - left + 1;
  }
};