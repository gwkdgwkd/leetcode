/*
小扣在秋日市集选择了一家早餐摊位，一维整型数组staple中记录了每种主食的价格，
一维整型数组drinks中记录了每种饮料的价格。
小扣的计划选择一份主食和一款饮料，且花费不超过x元，请返回小扣共有多少种购买方案。
注意：答案需要以1e9 +
7(1000000007)为底取模，如：计算初始结果为：1000000008，请返回1

示例1：
输入：staple = [10,20,5], drinks = [5,5,2], x = 15
输出：6
解释：小扣有6种购买方案，所选主食与所选饮料在数组中对应的下标分别是：
     第1种方案：staple[0] + drinks[0] = 10 + 5 = 15；
     第2种方案：staple[0] + drinks[1] = 10 + 5 = 15；
     第3种方案：staple[0] + drinks[2] = 10 + 2 = 12；
     第4种方案：staple[2] + drinks[0] = 5 + 5 = 10；
     第5种方案：staple[2] + drinks[1] = 5 + 5 = 10；
     第6种方案：staple[2] + drinks[2] = 5 + 2 = 7。

示例2：
输入：staple = [2,1,1], drinks = [8,9,5,1], x = 9
输出：8
解释：小扣有8种购买方案，所选主食与所选饮料在数组中对应的下标分别是：
     第1种方案：staple[0] + drinks[2] = 2 + 5 = 7；
     第2种方案：staple[0] + drinks[3] = 2 + 1 = 3；
     第3种方案：staple[1] + drinks[0] = 1 + 8 = 9；
     第4种方案：staple[1] + drinks[2] = 1 + 5 = 6；
     第5种方案：staple[1] + drinks[3] = 1 + 1 = 2；
     第6种方案：staple[2] + drinks[0] = 1 + 8 = 9；
     第7种方案：staple[2] + drinks[2] = 1 + 5 = 6；
     第8种方案：staple[2] + drinks[3] = 1 + 1 = 2；


提示：
1 <= staple.length <= 10^5
1 <= drinks.length <= 10^5
1 <= staple[i],drinks[i] <= 10^5
1 <= x <= 2*10^5
*/

// 暴力法，超时
class Solution {
 public:
  int breakfastNumber(vector<int>& staple, vector<int>& drinks, int x) {
    int n = staple.size();
    int m = drinks.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (staple[i] + drinks[j] <= x) {
          ++ans;
        }
      }
    }
    return ans % 1000000007;
  }
};

// 双指针，参考两数之和
class Solution {
 public:
  int breakfastNumber(vector<int>& staple, vector<int>& drinks, int x) {
    sort(staple.begin(), staple.end());
    sort(drinks.begin(), drinks.end());
    int n = staple.size();
    int m = drinks.size();
    int ans = 0;
    int left = 0;
    int right = m - 1;
    while (left < n && right >= 0) {
      int sum = staple[left] + drinks[right];
      if (sum <= x) {
        ++left;
        ans += right + 1;
        ans %= 1000000007;
      } else {
        --right;
      }
    }

    return ans;
  }
};