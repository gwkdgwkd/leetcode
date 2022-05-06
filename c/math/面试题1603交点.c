/*
给定两条线段（表示为起点start = {X1, Y1}和终点end = {X2,Y2}），
如果它们有交点，请计算其交点，没有交点则返回空值。
要求浮点型误差不超过10^-6。
若有多个交点（线段重叠）则返回X值最小的点，X坐标相同则返回Y值最小的点。

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