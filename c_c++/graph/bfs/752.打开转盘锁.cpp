/*
有一个带有四个圆形拨轮的转盘锁，每个拨轮都有10个数字：
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'。
每个拨轮可以自由旋转：例如把'9'变为'0'，'0'变为'9'。
每次旋转都只能旋转一个拨轮的一位数字，锁的初始数字为'0000'，代表四个拨轮。
列表deadends包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，
这个锁将会被永久锁定，无法再被旋转，字符串target代表可以解锁的数字，
需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回-1。

示例 1：
输入：deadends = ["0201","0101","0102","1212","2002"],
     target = "0202"
输出：6
解释：
可能的移动序列为：
"0000"->"1000"->"1100"->"1200"->"1201"->"1202"->"0202"。
"0000"->"0001"->"0002"->"0102"->"0202"这样的序列是不能解锁的，
因为当拨动到"0102"时这个锁就会被锁定。

示例2：
输入：deadends = ["8888"], target = "0009"
输出：1
解释：把最后一位反向旋转一次即可"0000" -> "0009"。

示例 3：
输入：deadends = ["8887","8889","8878","8898",
                 "8788","8988","7888","9888"],
     target = "8888"
输出：-1
解释：无法旋转到目标数字且不被锁定。

提示：
1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target不在deadends之中
target和deadends[i]仅由若干位数字组成
*/

// 剑指OfferII109开密码锁

// BFS
int visited[10000] = {0};
char que[10000][5];
int front;
int rear;
void AddOne(char *src, char *des, int i) {
  strncpy(des, src, 5);

  if (des[i] == '9') {
    des[i] = '0';
  } else {
    des[i]++;
  }
}
void DecOne(char *src, char *des, int i) {
  strncpy(des, src, 5);
  if (des[i] == '0') {
    des[i] = '9';
  } else {
    des[i]--;
  }
}
int openLock(char **deadends, int deadendsSize, char *target) {
  int step = 0;
  if (target == NULL) return -1;
  front = 0;
  rear = 0;
  memset(visited, 0, sizeof(visited));

  // 参考labuladong的小技巧，将deadends的状态先进行状态修改，
  // 在后续遍历到的时候遇到这个状态就不要加到队列中去，
  // 即这个状态不在继续衍生
  for (int i = 0; i < deadendsSize; i++) {
    visited[atoi(deadends[i])] = 1;
  }
  // 处理0000为死状态的情况
  if (visited[atoi("0000")] == 1) return -1;

  // 初始节点压入队列中
  strncpy(que[rear], "0000", 5);
  visited[atoi("0000")] = 1;
  rear++;

  int queSize = rear - front;

  while (front < rear) {
    // 通过quesize的方法计算step的方式增加了函数层数，不是很好，可以优化
    for (int i = 0; i < queSize; i++) {
      // 和targe相比，匹配则返回步数
      if (strcmp(que[front], target) == 0) return step;
      // 不匹配的情况下将四个字符都向下或向上拨一下后加入queue中
      for (int k = 0; k < 4; k++) {
        char buf[5];
        AddOne(que[front], buf, k);
        if (visited[atoi(buf)] == 0) {
          strncpy(que[rear], buf, 5);
          visited[atoi(buf)] = 1;
          rear++;
        }
        DecOne(que[front], buf, k);
        if (visited[atoi(buf)] == 0) {
          strncpy(que[rear], buf, 5);
          visited[atoi(buf)] = 1;
          rear++;
        }
      }
      front++;
    }
    step++;
    queSize = rear - front;
  }
  return -1;
}

class Solution {
  string addOne(string s, int i) {
    if (s[i] == '9') {
      s[i] = '0';
    } else {
      s[i]++;
    }
    return s;
  }
  string decOne(string s, int i) {
    if (s[i] == '0') {
      s[i] = '9';
    } else {
      s[i]--;
    }
    return s;
  }

 public:
  int openLock(vector<string> &deadends, string target) {
    string start("0000");
    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.find(start) != dead.end()) {
      return -1;
    }

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
        for (int j = 0; j < 4; ++j) {
          string add = addOne(temp, j);
          if (dead.find(add) == dead.end()) {
            dead.insert(add);
            q.push(add);
          }
          string dec = decOne(temp, j);
          if (dead.find(dec) == dead.end()) {
            dead.insert(dec);
            q.push(dec);
          }
        }
      }
      ++step;
    }

    return -1;
  }
};