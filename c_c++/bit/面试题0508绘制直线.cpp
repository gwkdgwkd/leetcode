/*
已知一个由像素点组成的单色屏幕，每行均有w个像素点，
所有像素点初始为0，左上角位置为(0,0)。
现将每行的像素点按照每32个像素点为一组存放在一个int中，
再依次存入长度为length的一维数组中。
我们将在屏幕上绘制一条从点(x1,y)到点(x2,y)的直线（即像素点修改为1），
请返回绘制过后的数组。
注意：用例保证屏幕宽度w可被32整除（即一个int不会分布在两行上）。

示例1:
输入：length = 1, w = 32, x1 = 30, x2 = 31, y = 0
输出：[3]
解释：在第0行的第30位到第31位画一条直线，
屏幕二进制形式表示为[00000000000000000000000000000011]，因此返回[3]

示例2:
输入：length = 3, w = 96, x1 = 0, x2 = 95, y = 0
输出：[-1, -1, -1]
解释：由于二进制11111111111111111111111111111111的int类型代表-1，
     因此返回[-1,-1,-1]

提示：
1 <= length <= 10^5
1 <= w <= 3 * 10^5
0 <= x1 <= x2 < w
0 <= y <= 10
*/

int* drawLine(int length, int w, int x1, int x2, int y, int* returnSize) {
  if ((y + 1) > (length * 32 / w)) {
    *returnSize = 0;
    return NULL;
  }

  int* line = malloc(sizeof(int) * length);
  memset(line, 0, sizeof(int) * length);
  int num = y * w / 32;
  for (int i = x1; i <= x2; i++) {
    unsigned int temp = (unsigned int)1 << (31 - (i % 32));
    line[(i / 32) + num] += temp;
  }
  *returnSize = length;
  return (int*)line;
}

class Solution {
 public:
  vector<int> drawLine(int length, int w, int x1, int x2, int y) {
    vector<int> res;
    int cols = w / 32;
    int rows = length / cols;
    for (int row = 0; row < rows; row++) {    // 遍历行数
      for (int col = 0; col < cols; col++) {  // 遍历列组数
        if (row == y) {
          bitset<32> num;
          for (int k = 0; k < 32; k++) {  // 遍历每个组(32个像素)
            if (x1 <= col * 32 + k && col * 32 + k <= x2) {
              num[31 - k] = 1;
            }
          }
          res.push_back((int)num.to_ulong());
        } else {
          res.push_back(0);
        }
      }
    }
    return res;
  }
};