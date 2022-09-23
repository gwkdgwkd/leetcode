/*
在柠檬水摊上，每一杯柠檬水的售价为5美元。
顾客排队购买你的产品，（按账单bills支付的顺序）一次购买一杯。
每位顾客只买一杯柠檬水，然后向你付5美元、10美元或20美元。
你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付5美元。
注意，一开始你手头没有任何零钱。
给你一个整数数组bills，其中bills[i]是第i位顾客付的账。
如果你能给每位顾客正确找零，返回true，否则返回false 。

示例1：
输入：bills = [5,5,5,10,20]
输出：true
解释：
前3位顾客那里，我们按顺序收取3张5美元的钞票。
第4位顾客那里，我们收取一张10美元的钞票，并返还5美元。
第5位顾客那里，我们找还一张10美元的钞票和一张5美元的钞票。
由于所有客户都得到了正确的找零，所以我们输出true。

示例2：
输入：bills = [5,5,10,10,20]
输出：false
解释：
前2位顾客那里，我们按顺序收取2张5美元的钞票。
对于接下来的2位顾客，我们收取一张10美元的钞票，然后返还5美元。
对于最后一位顾客，我们无法退回15美元，
因为我们现在只有两张10美元的钞票。
由于不是每位顾客都得到了正确的找零，所以答案是false。

提示：
1 <= bills.length <= 10^5
bills[i]不是5就是10或是20
*/

// 贪心算法
bool lemonadeChange(int* bills, int billsSize) {
  int five = 0;
  int ten = 0;
  // int twenty = 0;  // 不用twenty也行，因为20不会被找零

  for (int i = 0; i < billsSize; ++i) {
    if (bills[i] == 5) {
      ++five;
    } else if (bills[i] == 10) {
      --five;
      ++ten;
    } else if (bills[i] == 20) {
      if (ten > 0) {
        --ten;
        --five;
      } else {
        five -= 3;
      }
      // ++twenty;
    }

    // if (five < 0 || ten < 0 || twenty < 0) {
    if (five < 0 || ten < 0) {
      return false;
    }
  }

  return true;
}

class Solution {
 public:
  bool lemonadeChange(vector<int>& bills) {
    int c5 = 0;
    int c10 = 0;

    for (int i = 0; i < bills.size(); ++i) {
      if (bills[i] == 5) {
        ++c5;
      } else if (bills[i] == 10) {
        ++c10;
        --c5;
      } else if (bills[i] == 20) {
        if (c10 > 0) {
          --c10;
          --c5;
        } else {
          c5 -= 3;
        }
      }
      if (c5 < 0) {
        return false;
      }
    }

    return true;
  }
};