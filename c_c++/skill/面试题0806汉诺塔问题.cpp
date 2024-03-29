/*
在经典汉诺塔问题中，有3根柱子及N个不同大小的穿孔圆盘，盘子可以滑入任意一根柱子。
一开始，所有盘子自上而下按升序依次套在第一根柱子上，即每一个盘子只能放在更大的盘子上面。
移动圆盘时受到以下限制：
1.每次只能移动一个盘子；
2.盘子只能从柱子顶端滑出移到下一根柱子；
3.盘子只能叠在比它大的盘子上。
请编写程序，用栈将所有盘子从第一根柱子移到最后一根柱子，你需要原地修改栈。

示例1：
输入：A = [2, 1, 0], B = [], C = []
输出：C = [2, 1, 0]

示例2：
输入：A = [1, 0], B = [], C = []
输出：C = [1, 0]

提示：A中盘子的数目不大于14个。
*/

void move(int n, int* a, int* n1, int* b, int* n2, int* c, int* n3) {
  if (n == 1) {
    c[(*n3)++] = a[--(*n1)];
  } else {
    move(n - 1, a, n1, c, n3, b, n2);
    c[(*n3)++] = a[--(*n1)];
    move(n - 1, b, n2, a, n1, c, n3);
  }
}
void hanota(int* A, int ASize, int* B, int BSize, int** C, int* CSize) {
  int n = ASize;
  int* ret = (int*)malloc(sizeof(int) * 14);
  int* b = (int*)malloc(sizeof(int) * 14);
  move(n, A, &ASize, b, &BSize, ret, CSize);
  *C = ret;
  *CSize = n;
}

class Solution {
  // 把A中的n个元素移动到C，需要借助B：
  void move(int n, vector<int>& A, vector<int>& B, vector<int>& C) {
    if (n == 1) {  // 如果只移动一个，那么不需要B，可以直接移动
      C.push_back(A.back());
      A.pop_back();
      return;
    }

    move(n - 1, A, C, B);  // 把A中上面的n-1个，通过C移动到B
    C.push_back(A.back());  // 把A中最下面的也是最大的那个盘子移动到C
    A.pop_back();
    move(n - 1, B, A, C);  // 把之前移动到B的n-1个盘子，通过A移动到C
  }

 public:
  void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
    int n = A.size();
    move(n, A, B, C);  // 把A中的n个盘子，全部通过B的帮助移动到C
  }
};