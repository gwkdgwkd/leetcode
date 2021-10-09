/*
 * @lc app=leetcode.cn id=904 lang=c
 *
 * [904] 水果成篮
 */

// @lc code=start

// 暴力法，超时
int totalFruit(int* fruits, int fruitsSize) {
  int f, s;
  int ret = INT_MIN;
  int sublen;
  for (int i = 0; i < fruitsSize; ++i) {
    f = s = -1;
    sublen = 0;
    for (int j = i; j < fruitsSize; ++j) {
      if (f == -1) {
        f = fruits[j];
        sublen++;
      } else if (f != -1 && fruits[j] == f) {
        sublen++;
      } else if (f != -1 && s == -1) {
        s = fruits[j];
        sublen++;
      } else if (f != -1 && s != -1) {
        if (f != fruits[j] && s != fruits[j]) {
          ret = fmax(ret, sublen);
          break;
        } else {
          sublen++;
        }
      }
    }
    ret = fmax(ret, sublen);
  }

  return ret;
}

// 滑动窗口
int totalFruit(int* fruits, int fruitsSize) {
  int i;
  int j = 0;
  int ret = 1;
  int cnt = 0;
  int count[fruitsSize];
  memset(count, 0, sizeof(count));
  for (i = 0; i < fruitsSize; i++) {
    count[fruits[i]]++;
    if (count[fruits[i]] == 1) {
      cnt++;
    }

    while (j < i && cnt > 2) {
      //  printf("     %d - %d: %d [ ",j,i,ret);
      //  for(int k = j; k <= i; ++k) {
      //    printf("%d ",fruits[k]);
      //  }
      //  printf("]\n");
      count[fruits[j]]--;
      if (count[fruits[j]] == 0) {
        cnt--;
      }
      j++;
    }
    ret = fmax(ret, (i - j + 1));
    //  printf("%d %d - %d: %d [ ",fruits[i], j,i,ret);
    //  for(int k = j; k <=i; ++k) {
    //    printf("%d ",fruits[k]);
    //  }
    //  printf("]\n");
  }

  // [3,3,3,1,2,1,1,2,3,3,4]

  // 3 0 - 0: 1 [ 3 ]
  // 3 0 - 1: 2 [ 3 3 ]
  // 3 0 - 2: 3 [ 3 3 3 ]
  // 1 0 - 3: 4 [ 3 3 3 1 ]
  //      0 - 4: 4 [ 3 3 3 1 2 ]
  //      1 - 4: 4 [ 3 3 1 2 ]
  //      2 - 4: 4 [ 3 1 2 ]
  // 2 3 - 4: 4 [ 1 2 ]
  // 1 3 - 5: 4 [ 1 2 1 ]
  // 1 3 - 6: 4 [ 1 2 1 1 ]
  // 2 3 - 7: 5 [ 1 2 1 1 2 ]
  //      3 - 8: 5 [ 1 2 1 1 2 3 ]
  //      4 - 8: 5 [ 2 1 1 2 3 ]
  //      5 - 8: 5 [ 1 1 2 3 ]
  //      6 - 8: 5 [ 1 2 3 ]
  // 3 7 - 8: 5 [ 2 3 ]
  // 3 7 - 9: 5 [ 2 3 3 ]
  //      7 - 10: 5 [ 2 3 3 4 ]
  // 4 8 - 10: 5 [ 3 3 4 ]

  return ret;
}

// @lc code=end
