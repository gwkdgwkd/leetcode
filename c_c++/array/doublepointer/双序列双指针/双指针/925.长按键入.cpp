/*
你的朋友正在使用键盘输入他的名字name。
偶尔，在键入字符c时，按键可能会被长按，而字符可能被输入1次或多次。
你将会检查键盘输入的字符typed。
如果它对应的可能是你的朋友的名字（其中一些字符可能被长按），那么就返回True。

示例1：
输入：name = "alex", typed = "aaleex"
输出：true
解释：'alex'中的'a'和'e'被长按。

示例2：
输入：name = "saeed", typed = "ssaaedd"
输出：false
解释：'e'一定需要被键入两次，但在typed的输出中不是这样。


提示：
1 <= name.length, typed.length <= 1000
name和typed的字符都是小写字母
*/

// 双指针
class Solution {
 public:
  bool isLongPressedName(string name, string typed) {
    int i = 0, j = 0;
    while (j < typed.length()) {
      if (i < name.length() && name[i] == typed[j]) {
        i++;
        j++;
      } else if (j > 0 && typed[j] == typed[j - 1]) {
        j++;
      } else {
        return false;
      }
    }
    return i == name.length();
  }
};