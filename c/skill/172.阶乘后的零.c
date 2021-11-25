int trailingZeroes(int n) {
  int res = 0;
  for (int d = n; d / 5 > 0; d = d / 5) {
    res += d / 5;
  }
  return res;
}