/*
珠玑妙算游戏（the game of master mind）的玩法如下。
计算机有4个槽，每个槽放一个球，
颜色可能是红色（R）、黄色（Y）、绿色（G）或蓝色（B）。
例如，计算机可能有RGGB4种（槽1为红色，槽2、3为绿色，槽4为蓝色）。
作为用户，你试图猜出颜色组合。
打个比方，你可能会猜YRGB。
要是猜对某个槽的颜色，则算一次猜中；
要是只猜对颜色但槽位猜错了，则算一次伪猜中。
注意，猜中不能算入伪猜中。
给定一种颜色组合solution和一个猜测guess，编写一个方法，
返回猜中和伪猜中的次数answer，
其中answer[0]为猜中的次数，answer[1]为伪猜中的次数。

示例：
输入：solution="RGBY",guess="GGRR"
输出：[1,1]
解释：猜中1次，伪猜中1次。

提示：
len(solution) = len(guess) = 4
solution和guess仅包含"R","G","B","Y"这4种字符
*/

int* masterMind(char* solution, char* guess, int* returnSize) {
  int* a = calloc(sizeof(int), 2);
  int i, j;
  *returnSize = 2;
  for (i = 0; i < 4; i++) {
    if (guess[i] == solution[i]) {
      a[0]++;  // 计数对的
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (guess[i] == solution[j]) {
        a[1]++;             // 对的+伪对
        solution[j] = 'W';  // 防止重复
        break;
      }
    }
  }
  a[1] -= a[0];
  return a;
}

class Solution {
 public:
  vector<int> masterMind(string solution, string guess) {
    int num1 = 0, num2 = 0;
    unordered_map<char, int> alpha_map;
    for (char ch : solution) {
      alpha_map[ch]++;
    }
    for (int i = 0; i < guess.size(); i++) {
      if (solution[i] == guess[i]) {
        num1++;
      }
      // 注意这里为猜中+伪猜中的次数总和
      if (alpha_map[guess[i]]) {
        alpha_map[guess[i]]--;
        num2++;
      }
    }
    return {num1, num2 - num1};
  }
};