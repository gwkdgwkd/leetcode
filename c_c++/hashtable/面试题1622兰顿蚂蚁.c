/*
一只蚂蚁坐在由白色和黑色方格构成的无限网格上。开始时，网格全白，蚂蚁面向右侧。每行走一步，蚂蚁执行以下操作。
(1)如果在白色方格上，则翻转方格的颜色，向右(顺时针)转90度，并向前移动一个单位。
(2)如果在黑色方格上，则翻转方格的颜色，向左(逆时针方向)转90度，并向前移动一个单位。
编写程序来模拟蚂蚁执行的前K个动作，并返回最终的网格。
网格由数组表示，每个元素是一个字符串，代表网格中的一行，黑色方格由'X'表示，白色方格由'_'表示，
蚂蚁所在的位置由 'L', 'U', 'R', 'D' 表示，分别表示蚂蚁 左、上、右、下 的朝向。
只需要返回能够包含蚂蚁走过的所有方格的最小矩形。

示例1:
输入: 0
输出: ["R"]

示例2:
输入: 2
输出:
[
  "_X",
  "LX"
]

示例3:
输入: 5
输出:
[
  "_U",
  "X_",
  "XX"
]

说明：K <= 100000
*/

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) < (b) ? (a) : (b))
#define RET_LEN 10000
char ret_[RET_LEN][RET_LEN];
char *ret[RET_LEN];
typedef struct _hash_st {
  int key[2];
  int val;
  UT_hash_handle hh;
} hash_st;
char **printKMoves(int K, int *returnSize) {
  hash_st *pool = (hash_st *)calloc(K, sizeof(hash_st));
  int psize = 0;

  hash_st *head = NULL;

  int cur[2] = {0};
  char dirc = 'R';

  int llen = 0;
  int dlen = 0;
  int rlen = 0;
  int ulen = 0;

  for (int i = 0; i < K; i++) {
    // printf("[%d, %d](%c)    ", cur[0], cur[1], dirc);
    // 获得当前黑白状态
    int color;

    hash_st *tmph;
    HASH_FIND(hh, head, cur, sizeof(cur), tmph);
    if (tmph == NULL) {
      hash_st *new = &pool[psize++];
      new->key[0] = cur[0];
      new->key[1] = cur[1];
      new->val = 1;  // 没有使用的位置总是空白‘0’，但后面使用过后就为‘1’

      HASH_ADD_KEYPTR(hh, head, new->key, sizeof(new->key), new);

      color = 0;
    } else {
      color = tmph->val;

      tmph->val = (color == 0) ? 1 : 0;  // 记录使用过后的颜色
    }

    // 转向
    switch (dirc) {
      case 'L':
        dirc = (color == 0) ? 'U' : 'D';
        break;
      case 'R':
        dirc = (color == 0) ? 'D' : 'U';
        break;
      case 'U':
        dirc = (color == 0) ? 'R' : 'L';
        break;
      case 'D':
        dirc = (color == 0) ? 'L' : 'R';
        break;
      default:
        printf("dirc ERROR!\n");
    }

    //前进
    switch (dirc) {
      case 'L':
        cur[1]--;
        llen = MMIN(llen, cur[1]);
        break;
      case 'R':
        cur[1]++;
        rlen = MMAX(rlen, cur[1]);
        break;
      case 'U':
        cur[0]++;
        ulen = MMAX(ulen, cur[0]);
        break;
      case 'D':
        cur[0]--;
        dlen = MMIN(dlen, cur[0]);
        break;
      default:
        printf("dirc ERROR!\n");
    }
  }

  // 最终位置会填写方向，无需hash操作
  // printf("[%d, %d](%c)\n", cur[0], cur[1], dirc);

  // 准备输出结果
  int row = ulen - dlen + 1;
  int col = rlen - llen + 1;

  for (int i = 0; i < row; i++) {
    ret[i] = ret_[i];
    for (int j = 0; j < col; j++) {
      ret[i][j] = '_';
    }
    // 收尾
    ret[i][col] = '\0';
  }

  // 遍历hash表，刷入所有‘X'，注意坐标原点在左上
  hash_st *tmpc, *tmph;
  HASH_ITER(hh, head, tmpc, tmph) {
    int y = tmpc->key[0];
    int x = tmpc->key[1];
    y = ulen - y;
    x -= llen;

    ret[y][x] = tmpc->val == 1 ? 'X' : '_';
  }

  ret[ulen - cur[0]][cur[1] - llen] = dirc;

  *returnSize = row;
  return ret;
}