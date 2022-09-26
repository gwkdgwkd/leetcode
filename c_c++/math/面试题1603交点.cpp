/*
给定两条线段（表示为起点start = {X1, Y1}和终点end = {X2,Y2}），
如果它们有交点，请计算其交点，没有交点则返回空值。
要求浮点型误差不超过10^-6。
若有多个交点（线段重叠）则返回X值最小的点，
X坐标相同则返回Y值最小的点。

示例1：
输入：
line1 = {0, 0}, {1, 0}
line2 = {1, 1}, {0, -1}
输出：{0.5, 0}

示例2：
输入：
line1 = {0, 0}, {3, 3}
line2 = {1, 1}, {2, 2}
输出：{1, 1}

示例3：
输入：
line1 = {0, 0}, {1, 1}
line2 = {1, 0}, {2, 1}
输出：{}，两条线段没有交点

提示：
坐标绝对值不会超过2^7
输入的坐标均是有效的二维坐标
*/

typedef struct {
  double x;
  double y;
} TPoint;
#define INIT_POINT(pt, p) \
  pt.x = (double)p[0];    \
  pt.y = (double)p[1];

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define HAFL_POINT(phalf, s, e)  \
  phalf.x = (s->x + e->x) / 2.0; \
  phalf.y = (s->y + e->y) / 2.0;

#define MIN_ERROR 0.0000001
#define EQUAL(a, b) \
  (fabs(a->x - b->x) <= MIN_ERROR && fabs(a->y - b->y) <= MIN_ERROR)

#define NOT_IN_RANGE(a, b, c) (a < b || a > c)

int cnt = 0;
int IsNotInRange(TPoint *s1, TPoint *e1, TPoint *s2, TPoint *e2) {
  double min1, min2;
  double max1, max2;
  min1 = MIN(s1->x, e1->x);
  max1 = MAX(s1->x, e1->x);
  min2 = MIN(s2->x, e2->x);
  max2 = MAX(s2->x, e2->x);
  if (min2 > max1 || max2 < min1) {
    // printf("\r\n out (%f,%f)->(%f,%f) ;  (%f,%f)->(%f,%f)",
    //    s1->x, s1->y, e1->x, e1->y,  s2->x, s2->y, e2->x, e2->y) ;
    return 1;
  } else {
    min1 = MIN(s1->y, e1->y);
    max1 = MAX(s1->y, e1->y);
    min2 = MIN(s2->y, e2->y);
    max2 = MAX(s2->y, e2->y);
    if (min2 > max1 || max2 < min1) {
      // printf("\r\n out (%f,%f)->(%f,%f) ;  (%f,%f)->(%f,%f)",
      //       s1->x, s1->y, e1->x, e1->y,  s2->x, s2->y, e2->x, e2->y) ;
      return 1;
    }
  }
  return 0;
}
double *GetCross(TPoint *s1, TPoint *e1, TPoint *s2, TPoint *e2) {
  if (cnt++ > 500) {
    // return NULL;
  }
  // printf("\r\n (%f,%f)->(%f,%f) ;  (%f,%f)->(%f,%f)",
  //      s1->x, s1->y, e1->x, e1->y,
  //      s2->x, s2->y, e2->x, e2->y) ;
  if (IsNotInRange(s1, e1, s2, e2)) {
    return NULL;
  }
  double *res;

  if (EQUAL(s1, e1) && EQUAL(s2, e2)) {
    if (EQUAL(s1, s2)) {
      res = (double *)malloc(2 * sizeof(double));
      res[0] = (s1->x + s2->x) / 2;
      res[1] = (s1->y + s2->y) / 2;
      return res;
    }
    // printf("\r\n end ,return null");
    return NULL;
  }

  TPoint p1Half;
  TPoint p2Half;
  HAFL_POINT(p1Half, s1, e1);
  HAFL_POINT(p2Half, s2, e2);
  res = GetCross(s1, &p1Half, s2, &p2Half);
  if (res) {
    return res;
  }
  res = GetCross(&p1Half, e1, s2, &p2Half);
  if (res) {
    return res;
  }
  res = GetCross(s1, &p1Half, &p2Half, e2);
  if (res) {
    return res;
  }
  res = GetCross(&p1Half, e1, &p2Half, e2);
  if (res) {
    return res;
  }
  return NULL;
}
double *intersection(int *start1, int start1Size, int *end1, int end1Size,
                     int *start2, int start2Size, int *end2, int end2Size,
                     int *returnSize) {
  TPoint ptStart1, ptEnd1;
  TPoint ptStart2, ptEnd2;
  int k1, k2;  // y = kx + b
  INIT_POINT(ptStart1, start1);
  INIT_POINT(ptEnd1, end1);
  INIT_POINT(ptStart2, start2);
  INIT_POINT(ptEnd2, end2);
  double *ret = NULL;
  cnt = 0;
  ret = GetCross(&ptStart1, &ptEnd1, &ptStart2, &ptEnd2);
  // printf("\r\n ret= %p cnt =%d", ret, cnt);
  if (ret == NULL) {
    *returnSize = 0;
    // ret = (double*)calloc(2 , sizeof(double));
    // printf("\r\n no result");
  } else {
    *returnSize = 2;
    // printf("\r\n ret.= (%f, %f)", ret[0], ret[1]);
  }
  return ret;
}

class Solution {
 public:
  // 判断(xk, yk)是否在线段(x1, y1)~(x2, y2)上
  // 这里的前提是(xk, yk)一定在直线(x1, y1)~(x2, y2)上
  bool inside(int x1, int y1, int x2, int y2, int xk, int yk) {
    // 若与x轴平行，只需要判断x的部分
    // 若与y轴平行，只需要判断y的部分
    // 若为普通线段，则都要判断
    return (x1 == x2 || (min(x1, x2) <= xk && xk <= max(x1, x2))) &&
           (y1 == y2 || (min(y1, y2) <= yk && yk <= max(y1, y2)));
  }

  void update(vector<double> &ans, double xk, double yk) {
    // 将一个交点与当前ans中的结果进行比较
    // 若更优则替换
    if (!ans.size() || xk < ans[0] || (xk == ans[0] && yk < ans[1])) {
      ans = {xk, yk};
    }
  }

  vector<double> intersection(vector<int> &start1, vector<int> &end1,
                              vector<int> &start2, vector<int> &end2) {
    int x1 = start1[0], y1 = start1[1];
    int x2 = end1[0], y2 = end1[1];
    int x3 = start2[0], y3 = start2[1];
    int x4 = end2[0], y4 = end2[1];

    vector<double> ans;
    // 判断(x1, y1)~(x2, y2)和(x3, y3)~(x4, y3)是否平行
    if ((y4 - y3) * (x2 - x1) == (y2 - y1) * (x4 - x3)) {
      // 若平行，则判断(x3, y3)是否在直线(x1, y1)~(x2, y2)上
      if ((y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)) {
        // 判断(x3, y3)是否在线段(x1, y1)~(x2, y2)上
        if (inside(x1, y1, x2, y2, x3, y3)) {
          update(ans, (double)x3, (double)y3);
        }
        // 判断(x4, y4)是否在线段(x1, y1)~(x2, y2)上
        if (inside(x1, y1, x2, y2, x4, y4)) {
          update(ans, (double)x4, (double)y4);
        }
        // 判断(x1, y1)是否在线段(x3, y3)~(x4, y4)上
        if (inside(x3, y3, x4, y4, x1, y1)) {
          update(ans, (double)x1, (double)y1);
        }
        // 判断(x2, y2)是否在线段(x3, y3)~(x4, y4)上
        if (inside(x3, y3, x4, y4, x2, y2)) {
          update(ans, (double)x2, (double)y2);
        }
      }
      // 在平行时，其余的所有情况都不会有交点
    } else {
      // 联立方程得到t1和t2的值
      double t1 = (double)(x3 * (y4 - y3) + y1 * (x4 - x3) - y3 * (x4 - x3) -
                           x1 * (y4 - y3)) /
                  ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
      double t2 = (double)(x1 * (y2 - y1) + y3 * (x2 - x1) - y1 * (x2 - x1) -
                           x3 * (y2 - y1)) /
                  ((x4 - x3) * (y2 - y1) - (x2 - x1) * (y4 - y3));
      // 判断t1和t2是否均在[0, 1]之间
      if (t1 >= 0.0 && t1 <= 1.0 && t2 >= 0.0 && t2 <= 1.0) {
        ans = {x1 + t1 * (x2 - x1), y1 + t1 * (y2 - y1)};
      }
    }
    return ans;
  }
};
