int hammingWeight(uint32_t n) {
  int count = 0;
  while (n) {
    n = n & (n - 1);
    count++;
  }
  return count;
}

int hammingWeight(uint32_t n) {
  int count = 0;
  while (n != -1) {
    ++count;
    n |= n + 1;
  }
  return 32 - count;
}