/*
给你一个正整数n，生成一个包含1到n^2所有元素，且元素按顺时针顺序螺旋排列的nxn正方形矩阵matrix
。

示例1：
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]

示例2：
输入：n = 1
输出：[[1]]

提示：
1 <= n <= 20
*/

// 这个循环可以转懵很多人
int **generateMatrix(int n, int *returnSize, int **returnColumnSizes) {
  *returnSize = n;
  int **res = (int **)malloc(sizeof(int *) * n);
  *returnColumnSizes = (int *)malloc(sizeof(int) * n);
  for (int k = 0; k < n; ++k) {
    res[k] = (int *)malloc(sizeof(int) * n);
    (*returnColumnSizes)[k] = n;
  }

  // 定义每循环一个圈的起始位置
  int startx = 0, starty = 0;
  // 每个圈循环几次，例如n为奇数3，那么loop=1
  // 只是循环一圈，矩阵中间的值需要单独处理
  int loop = n / 2;
  // 矩阵中间的位置，例如：n为3，中间的位置就是(1，1)，n为5，中间位置为(2,2)
  int mid = n / 2;
  int count = 1;   // 用来给矩阵中每一个空格赋值
  int offset = 1;  // 每一圈循环，需要控制每一条边遍历的长度
  int i, j;

  while (loop--) {
    i = startx;
    j = starty;
    // 下面开始的四个for就是模拟转了一圈
    // 模拟填充上行从左到右(左闭右开)
    for (j = starty; j < starty + n - offset; ++j) {
      res[startx][j] = count++;
    }
    // 模拟填充右列从上到下(左闭右开)
    for (i = startx; i < startx + n - offset; ++i) {
      res[i][j] = count++;
    }
    // 模拟填充下行从右到左(左闭右开)
    for (; j > starty; --j) {
      res[i][j] = count++;
    }
    // 模拟填充左列从下到上(左闭右开)
    for (; i > startx; --i) {
      res[i][j] = count++;
    }

    // 第二圈开始的时候，起始位置要各自加1，例如：第一圈起始位置是(0,0)，第二圈起始位置是(1,1)
    startx++;
    starty++;

    // offset控制每一圈里每一条边遍历的长度
    offset += 2;
  }
  // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
  if (n % 2) {
    res[mid][mid] = count;
  }

  return res;
}

// 参考[54.螺旋矩阵]
int **generateMatrix(int n, int *returnSize, int **returnColumnSizes) {
  *returnSize = n;
  int **res = (int **)malloc(sizeof(int *) * n);
  *returnColumnSizes = (int *)malloc(sizeof(int) * n);
  for (int k = 0; k < n; ++k) {
    res[k] = (int *)malloc(sizeof(int) * n);
    (*returnColumnSizes)[k] = n;
  }

  int count = 1;
  int left = 0, right = n - 1, top = 0, bottom = n - 1;
  while (left <= right && top <= bottom) {
    for (int col = left; col <= right; ++col) {
      res[top][col] = count++;
    }
    for (int row = top + 1; row <= bottom; ++row) {
      res[row][right] = count++;
    }
    for (int col = right - 1; col > left; col--) {
      res[bottom][col] = count++;
    }
    for (int row = bottom; row > top; row--) {
      res[row][left] = count++;
    }
    left++;
    right--;
    top++;
    bottom--;
  }

  return res;
}
