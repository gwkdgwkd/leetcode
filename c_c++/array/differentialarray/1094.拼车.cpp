/*
车上最初有capacity个空座位。
车只能向一个方向行驶，也就是说，不允许掉头或改变方向。
给定整数capacity和一个数组trips,trip[i]=[numPassengersi,fromi,toi]，
表示第i次旅行有numPassengersi乘客，接他们和放他们的位置分别是fromi和toi。
这些位置是从汽车的初始位置向东的公里数。
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
  int people[1001];  // fromi和toi的范围
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

/* 差分数组
考虑数组a=[1,3,3,5,8]，对其中的相邻元素两两作差（右边减左边），
得到数组[2,0,2,3]，然后在开头补上a[0]，得到差分数组d=[1,2,0,2,3]。
这有什么用呢？
如果从左到右累加d中的元素，就还原回了a数组[1,3,3,5,8]，这类似求导与积分的概念。
这又有什么用呢？
现在把连续子数组a[1],a[2],a[3]都加上10，得到a′=[1,13,13,15,8]。
再次两两作差，并在开头补上 a′[0]，得到差分数组d′=[1,12,0,2,−7]。
对比d和d′，可以发现只有d[1]和d[4]变化了，这意味着对a中连续子数组的操作，
可以转变成对差分数组d中两个数的操作。
*/
class Solution {
 public:
  bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> diff(1001, 0);
    for (const auto& trip : trips) {
      diff[trip[1]] += trip[0];
      diff[trip[2]] -= trip[0];
    }

    int num = 0;
    for (int i : diff) {
      num += i;
      if (num > capacity) {
        return false;
      }
    }
    return true;
  }
};