/*
给一个长度固定的整数数组arr，请将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。
注意：请不要在超过该数组长度的位置写入元素。
请对输入的数组就地进行上述修改，不要从函数返回任何东西。

示例1：
输入：arr = [1,0,2,3,0,4,5,0]
输出：[1,0,0,2,3,0,0,4]
解释：调用函数后，输入的数组将被修改为：[1,0,0,2,3,0,0,4]

示例2：
输入：arr = [1,2,3]
输出：[1,2,3]
解释：调用函数后，输入的数组将被修改为：[1,2,3]


提示：
1 <= arr.length <= 10^4
0 <= arr[i] <= 9
*/

class Solution {
 public:
  void duplicateZeros(vector<int>& arr) {
    int n = arr.size();
    int cnt = 0;  // 数组中0的个数
    for (int i = 0; i < n; ++i) {
      if (arr[i] == 0) {
        ++cnt;
      }
    }

    int slow = n + cnt - 1;
    int fast = n - 1;
    while (fast >= 0) {  // 从后往前遍历
      if (arr[fast] == 0) {
        if (slow <= n - 1) {  // 如果slow位置有效，则更新数组
          arr[slow] = arr[fast];
        }
        slow--;
      }
      if (slow <= n - 1) {
        arr[slow] = arr[fast];
      }
      slow--;
      fast--;
    }
  }
};