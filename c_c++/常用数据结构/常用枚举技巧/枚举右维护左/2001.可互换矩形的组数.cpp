/*
用一个下标从0开始的二维整数数组rectangles来表示n个矩形，
其中rectangles[i]=[widthi,heighti]表示第i个矩形的宽度和高度。
如果两个矩形i和j（i<j）的宽高比相同，则认为这两个矩形可互换。
更规范的说法是，两个矩形满足widthi/heighti==widthj/heightj，
使用实数除法而非整数除法，则认为这两个矩形可互换。
计算并返回rectangles中有多少对可互换矩形。

示例1：
输入：rectangles = [[4,8],[3,6],[10,20],[15,30]]
输出：6
解释：下面按下标（从0开始）列出可互换矩形的配对情况：
     矩形0和矩形1：4/8 == 3/6
     矩形0和矩形2：4/8 == 10/20
     矩形0和矩形3：4/8 == 15/30
     矩形1和矩形2：3/6 == 10/20
     矩形1和矩形3：3/6 == 15/30
     矩形2和矩形3：10/20 == 15/30

示例2：
输入：rectangles = [[4,5],[7,8]]
输出：0
解释：不存在成对的可互换矩形。


提示：
n == rectangles.length
1 <= n <= 10^5
rectangles[i].length == 2
1 <= widthi, heighti <= 10^5
*/

class Solution {
  int gcd(int a, int b) {
    while (b) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
  //   int gcd(int a, int b) {
  //     if (a < b) return gcd(b, a);
  //     if (a % b == 0) return b;
  //     return gcd(b, a % b);
  //   }

 public:
  long long interchangeableRectangles(vector<vector<int>>& rectangles) {
    unordered_map<int, unordered_map<int, long long>> cnt;
    for (auto r : rectangles) {
      int c = gcd(r[0], r[1]);
      r[0] /= c;
      r[1] /= c;
      cnt[r[0]][r[1]]++;
      // ans += cnt[static_cast<float>(r[0])/r[1]]++; // 精度不准
    }
    long long ans = 0;
    for (auto it = cnt.begin(); it != cnt.end(); it++) {
      for (auto i = it->second.begin(); i != it->second.end(); i++) {
        ans += i->second * (i->second - 1) / 2;
      }
    }
    return ans;
  }
};
