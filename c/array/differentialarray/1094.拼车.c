/*
车上最初有capacity个空座位。车只能向一个方向行驶（也就是说，不允许掉头或改变方向）
给定整数capacity和一个数组trips,trip[i]=[numPassengersi,fromi,toi]表示第i次旅行有numPassengersi乘客，
接他们和放他们的位置分别是fromi和toi。这些位置是从汽车的初始位置向东的公里数。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回true，否则请返回false。

示例1：
输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false

示例2：
输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

提示：
1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 10^5
*/

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