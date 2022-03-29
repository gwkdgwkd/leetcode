/*
你正在探访一家农场，农场从左到右种植了一排果树。这些树用一个整数数组fruits表示，其中fruits[i]是第i棵树上的水果种类 。
你想要尽可能多地收集水果。然而，农场的主人设定了一些严格的规矩，你必须按照要求采摘水果：
你只有两个篮子，并且每个篮子只能装单一类型的水果。每个篮子能够装的水果总量没有限制。
你可以选择任意一棵树开始采摘，你必须从每棵树（包括开始采摘的树）上恰好摘一个水果。
采摘的水果应当符合篮子中的水果类型。每采摘一次，你将会向右移动到下一棵树，并继续采摘。
一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
给你一个整数数组fruits ，返回你可以收集的水果的最大数目。

示例1：
输入：fruits = [1,2,1]
输出：3
解释：可以采摘全部3棵树。

示例2：
输入：fruits = [0,1,2,2]
输出：3
解释：可以采摘[1,2,2]这三棵树。
如果从第一棵树开始采摘，则只能采摘[0,1]这两棵树。

示例3：
输入：fruits = [1,2,3,2,2]
输出：4
解释：可以采摘[2,3,2,2]这四棵树。
如果从第一棵树开始采摘，则只能采摘[1,2]这两棵树。

示例4：
输入：fruits = [3,3,3,1,2,1,1,2,3,3,4]
输出：5
解释：可以采摘[1,2,1,1,2]这五棵树。

提示：
1 <= fruits.length <= 105
0 <= fruits[i] < fruits.length
*/

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