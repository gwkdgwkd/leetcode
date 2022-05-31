/*
给定一个二维平面及平面上的N个点列表Points，其中第i个点的坐标为Points[i]=[Xi,Yi]。
请找出一条直线，其通过的点的数目最多。
设穿过最多点的直线所穿过的全部点编号从小到大排序的列表为S，你仅需返回[S[0],S[1]]作为答案，
若有多条直线穿过了相同数量的点，则选择S[0]值较小的直线返回，S[0]相同则选择S[1]值较小的直线返回。

示例：
输入： [[0,0],[1,1],[1,0],[2,0]]
输出： [0,2]
解释： 所求直线穿过的3个点的编号为[0,2,3]

提示：
2 <= len(Points) <= 300
len(Points[i]) = 2
*/

int* bestLine(int** points, int pointsSize, int* pointsColSize,
              int* returnSize) {
  int* res = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;
  int maxNum = 2;
  res[0] = 0;
  res[1] = 1;
  if (pointsSize < 3)  // 只有两个点直接返回
    return res;
  for (int i = 0; i < pointsSize - 1; i++) {  // 三重循环遍历
    for (int j = i + 1; j < pointsSize; j++) {
      long long x1 = points[j][0] - points[i][0];
      long long y1 = points[j][1] - points[i][1];  // 获取向量AB=(xb-xa,yb-ya);
      int tempNum = 2;
      for (int k = j + 1; k < pointsSize; k++) {
        long long x2 = points[k][0] - points[i][0];
        long long y2 =
            points[k][1] - points[i][1];  // 构造新的向量AC=(xc-xa,yc-ya);
        if (y1 * x2 == x1 * y2)           // 如果向量共线
          tempNum++;
      }
      if (tempNum > maxNum) {  // 更新结果
        maxNum = tempNum;
        res[0] = i;
        res[1] = j;
      }
    }
  }
  return res;
}