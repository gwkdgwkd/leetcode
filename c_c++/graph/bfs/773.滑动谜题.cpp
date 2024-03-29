/*
在一个2x3的板上（board）有5块砖瓦，用数字1~5来表示，以及一块空缺用0来表示。
一次移动定义为选择0与一个相邻的数字（上下左右）进行交换。
最终当板board的结果是[[1,2,3],[4,5,0]]谜板被解开。
初始状态board，返回最少可以通过多少次移动解开谜板，如果不能解开谜板，则返回-1。

示例1：
输入：board = [[1,2,3],[4,0,5]]
输出：1
解释：交0和5，1步完成

示例2：
输入：board = [[1,2,3],[5,4,0]]
输出：-1
解释：没有办法完成谜板

示例3：
输入：board = [[4,1,2],[5,0,3]]
输出：5
解释：
最少完成谜板的最少移动次数是5，一种移动路径：
尚未移动：[[4,1,2],[5,0,3]]
移动1次：[[4,1,2],[0,5,3]]
移动2次：[[0,1,2],[4,5,3]]
移动3次：[[1,0,2],[4,5,3]]
移动4次：[[1,2,0],[4,5,3]]
移动5次：[[1,2,3],[4,5,0]]

提示：
board.length == 2
board[i].length == 3
0 <= board[i][j] <= 5
board[i][j]中每个值都不同
*/

// BFS + 哈希
#define BOARD_MAX 6
#define NUM_MAX 543211
#define QUE_MAX 720
struct note {
  char position[BOARD_MAX + 1];  // 砖瓦位置
  int s;                         // 交换次数
};
struct note que[QUE_MAX];  // 全局队列
int g_hash[NUM_MAX];       // 数组实现hash

// 0 1 2
// 3 4 5
// 对应0的位置处，可以和哪些位置做交换
int turn[BOARD_MAX][3] = {{1, 3, -1}, {0, 2, 4}, {1, 5, -1},
                          {0, 4, -1}, {1, 3, 5}, {2, 4, -1}};
int find_zero(char* str) {
  for (int i = 0; i < BOARD_MAX; i++) {
    if (str[i] == '0') {
      return i;
    }
  }

  return -1;
}
void swap(char* str, int i, int j) {
  str[i] = str[i] ^ str[j];
  str[j] = str[i] ^ str[j];
  str[i] = str[i] ^ str[j];
}
int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
  int head, tail;            // 队列头、尾
  int i, j, k, flag = 0;     // flag标记是否转到目标
  char next[BOARD_MAX + 1];  // 下一个交换目标
  memset(g_hash, 0, sizeof(g_hash));
  char target[BOARD_MAX + 1] = {"123450"};
  char start[BOARD_MAX + 1];

  // start序列初始化
  k = 0;
  for (i = 0; i < boardSize; i++) {
    for (j = 0; j < boardColSize[0]; j++) {
      start[k++] = board[i][j] + '0';
    }
  }

  // 特殊用例：初始状态即为target，返回0，不用转动即到达终点
  if (strcmp(start, target) == 0) {
    return 0;
  }

  // 队列初始化
  head = 0;
  tail = 0;
  // 从start出发，放入队列，同时更新hash表
  strcpy(que[tail].position, start);
  que[tail].s = 0;
  tail++;
  g_hash[atoi(start)] = 1;

  // 当队列不为空的时候循环
  while (head < tail) {
    int zero_position = find_zero(que[head].position);
    // 从可以交换的方向依次尝试交换
    for (j = 0; (j < 3 && turn[zero_position][j] != -1); j++) {
      strcpy(next, que[head].position);  // 当前队列中首位置的编号
      swap(next, zero_position, turn[zero_position][j]);
      // 判断交换后的位置是否已经在队列中
      if (g_hash[atoi(next)] == 0) {  // 没有在队列中，则入队
        strcpy(que[tail].position, next);
        que[tail].s = que[head].s + 1;  // 交换次数+1
        tail++;

        // 更新交换位置hash
        g_hash[atoi(next)] = 1;
      }
      // 如果到达目标，停止扩展，任务结束，退出循环
      if (strcmp(next, target) == 0) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) {
      break;
    }
    head++;  // 注意这地方，千万不要忘记当一个点扩展结束后，head++才能继续扩展
  }

  // 打印队列中末尾最后一个（目标）的转动次数
  // 注意tail是指向队列队尾（即最后一位）的下一个位置，所以这需要-1
  if (flag == 0) {
    return -1;
  }
  return que[tail - 1].s;
}

// 官方题解
struct HashTable {
  char str[7];
  UT_hash_handle hh;
};
struct Node {
  char str[7];
  int val;
};
const int neighbors[6][3] = {{1, 3, -1}, {0, 2, 4}, {1, 5, -1},
                             {0, 4, -1}, {1, 3, 5}, {2, 4, -1}};
void swap(char* x, char* y) {
  char t = *x;
  *x = *y, *y = t;
}
// 枚举status通过一次旋转得到的数字
char** getNextStatus(char* status, int* retSize) {
  char** ret = malloc(sizeof(char*) * 3);
  *retSize = 0;
  int x = 0;
  while (status[x] != '0') {
    x++;
  }
  for (int i = 0; i < 3 && neighbors[x][i] != -1; i++) {
    int y = neighbors[x][i];
    swap(&status[x], &status[y]);
    ret[(*retSize)] = malloc(sizeof(char) * 7);
    strcpy(ret[(*retSize)++], status);
    swap(&status[x], &status[y]);
  }
  return ret;
}
int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
  char str_0[] = "123450";
  char initial[7];
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      initial[i * 3 + j] = (char)(board[i][j] + '0');
    }
  }
  initial[6] = '\0';
  if (strcmp(initial, str_0) == 0) {
    return 0;
  }

  struct Node q[10001];
  int left = 0, right = 0;
  strcpy(q[right].str, initial);
  q[right++].val = 0;

  struct HashTable* seen = NULL;
  struct HashTable* tmp = malloc(sizeof(struct HashTable));
  strcpy(tmp->str, initial);
  HASH_ADD(hh, seen, str, sizeof(char) * 7, tmp);

  while (left < right) {
    char* status = q[left].str;
    int step = q[left++].val;
    int nextStatusSize;
    char** nextStatus = getNextStatus(status, &nextStatusSize);
    for (int i = 0; i < nextStatusSize; i++) {
      HASH_FIND(hh, seen, nextStatus[i], sizeof(char) * 5, tmp);
      if (tmp == NULL) {
        if (strcmp(nextStatus[i], str_0) == 0) {
          return step + 1;
        }
        strcpy(q[right].str, nextStatus[i]);
        q[right++].val = step + 1;
        tmp = malloc(sizeof(struct HashTable));
        strcpy(tmp->str, nextStatus[i]);
        HASH_ADD(hh, seen, str, sizeof(char) * 5, tmp);
      }
    }
  }

  return -1;
}

class Solution {
        // 字符0在下标0-5位置时，可以移动到的位置，-1表示不能移动：
    const int neighbors[6][3] = {{1, 3, -1}, {0, 2, 4}, {1, 5, -1},
                                 {0, 4, -1}, {3, 1, 5}, {4, 2, -1}};
 public:
  int slidingPuzzle(vector<vector<int>>& board) {
    string target("123450");
    string start;
    for (const auto& v : board) {
      for (const auto& i : v) {
        start.push_back(i + '0');
      }
    }

    unordered_set<string> us;
    us.insert(start);
    queue<string> q;
    q.push(start);


    int step = 0;
    while (!q.empty()) {
      int n = q.size();
      for (int i = 0; i < n; ++i) {
        string temp = q.front();
        q.pop();
        if (temp == target) {
          return step;
        }
        int k = temp.find('0');
        for (int j = 0; j < 3 && neighbors[k][j] != -1; ++j) {
          string dst = temp;
          swap(dst[k], dst[neighbors[k][j]]);
          if (us.find(dst) == us.end()) {
            us.insert(dst);
            q.push(dst);
          }
        }
      }
      ++step;
    }

    return -1;
  }
};