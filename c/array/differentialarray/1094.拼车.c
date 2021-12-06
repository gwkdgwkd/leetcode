// 差分数组
bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity) {
  int people[1001];
  memset(people, 0, sizeof(people));
  for (int i = 0; i < tripsSize; i++) {
    people[trips[i][1]] += trips[i][0];
    people[trips[i][2]] -= trips[i][0];
  }
  int num = 0;
  for (int i = 0; i < 1001; i++) {
    num += people[i];
    if (num > capacity) {
      return false;
    }
  }
  return true;
}