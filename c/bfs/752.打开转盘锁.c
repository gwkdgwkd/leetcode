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

  // 参考labuladong的小技巧，将deadends的状态先进行状态修改，在后续遍历到的时候遇到这个状态就不要加到队列中去，即这个状态不在继续衍生
  for (int i = 0; i < deadendsSize; i++) {
    visited[atoi(deadends[i])] = 1;
  }
  // 处理“0000”为死状态的情况
  if (visited[atoi("0000")] == 1) return -1;

  // 初始节点压入队列中
  strncpy(que[rear], "0000", 5);
  visited[atoi("0000")] = 1;
  rear++;

  int queSize = rear - front;

  while (front < rear) {
    // 通过quesize的方法计算step的方式 增加了函数层数，不是很好，可以优化
    for (int i = 0; i < queSize; i++) {
      // 和targe相比，匹配则返回步数
      if (strcmp(que[front], target) == 0) return step;
      // 不匹配的情况下将四个字符都向下或向上拨 一下 后加入queue中
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