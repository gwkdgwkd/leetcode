/*
给定两个正方形及一个二维平面，请找出将这两个正方形分割成两半的一条直线。
假设正方形顶边和底边与x轴平行，每个正方形的数据square包含3个数值，
正方形的左下顶点坐标[X,Y] = [square[0],square[1]]，以及正方形的边长square[2]。
所求直线穿过两个正方形会形成4个交点，请返回4个交点形成线段的两端点坐标。
两个端点即为4个交点中距离最远的2个点，这2个点所连成的线段一定会穿过另外2个交点。
2个端点坐标[X1,Y1]和[X2,Y2]的返回格式为{X1,Y1,X2,Y2}，
要求若X1 != X2，需保证X1 < X2，否则需保证Y1 <= Y2。
若同时有多条直线满足要求，则选择斜率最大的一条计算并返回（与Y轴平行的直线视为斜率无穷大）。

示例：
输入：
square1 = {-1, -1, 2}
square2 = {0, -1, 2}
输出： {-1,0,2,0}
解释：直线y=0能将两个正方形同时分为等面积的两部分，
     返回的两线段端点为[-1,0]和[2,0]

提示：
square.length == 3
square[2] > 0
*/

#define X1 (square1[0])
#define Y1 (square1[1])
#define C1X (square1[0] + square1[2] / 2.0)
#define C1Y (square1[1] + square1[2] / 2.0)
#define X2 (square2[0])
#define Y2 (square2[1])
#define C2X (square2[0] + square2[2] / 2.0)
#define C2Y (square2[1] + square2[2] / 2.0)
double* cutSquares(int* square1, int square1Size, int* square2, int square2Size,
                   int* returnSize) {
  double* answer;
  double gradient;
  answer = (double*)malloc(4 * sizeof(double));
  if (C1X == C2X) {  // 中心点的纵坐标相同
    answer[0] = C1X;
    answer[1] = fmin(Y1, Y2);
    answer[2] = C2X;
    answer[3] = fmax(Y1 + square1[2], Y2 + square2[2]);
  } else {  // 中心点的纵坐标不同
    gradient = (C2Y - C1Y) / (C2X - C1X);
    printf("gradient = %f", gradient);
    if (gradient >= 1.0) {  // 斜率大于1，交点在上下两边，纵坐标最小的点在左边
      answer[1] = fmin(Y1, Y2);
      answer[0] = (answer[1] - C1Y) / gradient + C1X;
      answer[3] = fmax(Y1 + square1[2], Y2 + square2[2]);
      answer[2] = (answer[3] - C1Y) / gradient + C1X;
    } else if (gradient <=
               -1.0) {  // 斜率小于-1，交点在上下两边，纵坐标最小的点在右边
      answer[1] = fmax(Y1 + square1[2], Y2 + square2[2]);
      answer[0] = (answer[1] - C1Y) / gradient + C1X;
      answer[3] = fmin(Y1, Y2);
      answer[2] = (answer[3] - C1Y) / gradient + C1X;
    } else {  // 斜率在-1到1之间，交点在左右两边
      answer[0] = fmin(X1, X2);
      answer[1] = (answer[0] - C1X) * gradient + C1Y;
      answer[2] = fmax(X1 + square1[2], X2 + square2[2]);
      answer[3] = (answer[2] - C1X) * gradient + C1Y;
    }
  }
  *returnSize = 4;
  return answer;
}

class Solution {
 public:
  vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
    // 计算两个正方形中心(cx1, cy1), (cx2, cy2)
    double cx1 = square1[0] + ((double)square1[2]) / 2;
    double cy1 = square1[1] + ((double)square1[2]) / 2;
    double cx2 = square2[0] + ((double)square2[2]) / 2;
    double cy2 = square2[1] + ((double)square2[2]) / 2;

    vector<pair<double, double> > res;  // 候选顶点集
    // 处理特殊情况cx1 == cx2和cy1 == cy2
    if (cx1 == cx2) {
      res.push_back({cx1, square1[1]});
      res.push_back({cx1, square2[1]});
      res.push_back({cx1, square1[1] + square1[2]});
      res.push_back({cx1, square2[1] + square2[2]});
    } else if (cy1 == cy2) {
      res.push_back({square1[0], cy1});
      res.push_back({square2[0], cy1});
      res.push_back({square1[0] + square1[2], cy1});
      res.push_back({square2[0] + square2[2], cy1});
    } else {
      // 直线方程f(y)
      auto fy = [=](double y) -> double {
        const double k = (cx2 - cx1) / (cy2 - cy1);
        return k * (y - cy1) + cx1;
      };
      // 直线方程f(x)
      auto fx = [=](double x) -> double {
        const double k = (cy2 - cy1) / (cx2 - cx1);
        return k * (x - cx1) + cy1;
      };
      for (auto& sq : {square1, square2}) {
        for (auto& p : vector<pair<double, double> >{
                 {fy(sq[1]), sq[1]},
                 {fy(sq[1] + sq[2]), sq[1] + sq[2]},
                 {sq[0], fx(sq[0])},
                 {sq[0] + sq[2], fx(sq[0] + sq[2])}}) {
          // 判断候选顶点是否在正方形中
          if (p.first >= sq[0] && p.first <= sq[0] + sq[2]) {
            if (p.second >= sq[1] && p.second <= sq[1] + sq[2]) {
              res.push_back(p);
            }
          }
        }
      }
    }
    // 对顶点集排序
    sort(res.begin(), res.end());
    // 所求顶点为排序后的res数组的第一个顶点和最后一个顶点。
    return {
        res.front().first,
        res.front().second,
        res.back().first,
        res.back().second,
    };
  }
};
