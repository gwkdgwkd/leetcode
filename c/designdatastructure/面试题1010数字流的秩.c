/*
假设你正在读取一串整数。每隔一段时间，你希望能找出数字x的秩(小于或等于x的值的个数)。
请实现数据结构和算法来支持这些操作，也就是说：
实现track(int x)方法，每读入一个数字都会调用该方法；
实现getRankOfNumber(int x)方法，返回小于或等于x的值的个数。
注意：本题相对原题稍作改动

示例:
输入:
["StreamRank", "getRankOfNumber", "track", "getRankOfNumber"]
[[], [1], [0], [0]]
输出:
[null,0,null,1]

提示：
x <= 50000
track和getRankOfNumber方法的调用次数均不超过2000次
*/

typedef struct {
  int hash[50005];
} StreamRank;
StreamRank* streamRankCreate() {
  StreamRank* obj = (StreamRank*)malloc(sizeof(StreamRank));
  memset(obj, 0, sizeof(StreamRank));
  return obj;
}
void streamRankTrack(StreamRank* obj, int x) { obj->hash[x]++; }
int streamRankGetRankOfNumber(StreamRank* obj, int x) {
  int sum = 0;
  for (int i = 0; i <= x; i++) {
    sum += obj->hash[i];
  }
  return sum;
}
void streamRankFree(StreamRank* obj) { free(obj); }