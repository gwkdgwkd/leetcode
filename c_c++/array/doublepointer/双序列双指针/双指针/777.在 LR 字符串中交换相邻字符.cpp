/*
在一个由'L','R'和'X'三个字符组成的字符串（例如"RXXLRXRXL"）中进行移动操作。
一次移动操作指用一个"LX"替换一个"XL"，或者用一个"XR"替换一个"RX"。
现给定起始字符串start和结束字符串result，请编写代码，
当且仅当存在一系列移动操作使得start可以转换成result时，返回True。

示例1：
输入：start = "RXXLRXRXL", result = "XRLXXRRLX"
输出：true
解释：通过以下步骤我们可以将start转化为result：
     RXXLRXRXL->XRXLRXRXL->XRLXRXRXL->XRLXXRRXL->XRLXXRRLX

示例2：
输入：start = "X", result = "L"
输出：false


提示：
1 <= start.length <= 10^4
start.length == result.length
start和result都只包含'L','R'或'X'。
*/

// 同[2337.移动片段得到字符串]
class Solution {
 public:
  bool canTransform(string start, string result) {
    int n = start.size();
    int i = 0;
    int j = 0;
    while (i < n && j < n) {
      while (i < n && start[i] == 'X') {
        ++i;
      }
      while (j < n && result[j] == 'X') {
        ++j;
      }
      if (i < n && j < n) {
        if (start[i] != result[j]) {
          return false;
        }
        if ((start[i] == 'L' && i < j) || (start[i] == 'R' && i > j)) {
          return false;
        }
        ++i;
        ++j;
      }
    }
    while (i < n) {
      if (start[i] != 'X') {
        return false;
      }
      ++i;
    }
    while (j < n) {
      if (result[j] != 'X') {
        return false;
      }
      ++j;
    }
    return true;
  }
};