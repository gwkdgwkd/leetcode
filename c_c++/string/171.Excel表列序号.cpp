/*
给一个字符串columnTitle，表示Excel表格中的列名称，返回该列名称对应的列序号。
例如：
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...

示例1：
输入：columnTitle = "A"
输出：1

示例2：
输入：columnTitle = "AB"
输出：28

示例3：
输入：columnTitle = "ZY"
输出：701

提示：
1 <= columnTitle.length <= 7
columnTitle仅由大写英文组成
columnTitle在范围["A"，"FXSHRXW"]内
*/

int titleToNumber(char* columnTitle) {
  int ret = 0;
  for (int i = 0; i < strlen(columnTitle); ++i) {
    ret = ret * 26 + (columnTitle[i] - 'A' + 1);
  }
  return ret;
}

class Solution {
 public:
  int titleToNumber(string columnTitle) {
    int n = columnTitle.size();
    long ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = ans * 26 + columnTitle[i] - 'A' + 1;
    }
    return ans;
  }
};