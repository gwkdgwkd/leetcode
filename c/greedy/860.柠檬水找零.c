// 贪心算法
bool lemonadeChange(int* bills, int billsSize) {
  int five = 0;
  int ten = 0;
  int twenty = 0;

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
    }

    if (five < 0 || ten < 0 || twenty < 0) {
      return false;
    }
  }

  return true;
}