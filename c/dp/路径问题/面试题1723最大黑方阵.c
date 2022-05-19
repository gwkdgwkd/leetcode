/*
给定一个方阵，其中每个单元(像素)非黑即白。设计一个算法，找出4条边皆为黑色像素的最大子方阵。
返回一个数组[r, c, size]，其中r, c分别代表子方阵左上角的行号和列号，size是子方阵的边长。
若有多个满足条件的子方阵，返回r最小的，若r相同，返回c最小的子方阵。
若无满足条件的子方阵，返回空数组。

示例1:
输入:
[
   [1,0,1],
   [0,0,1],
   [0,0,1]
]
输出: [1,0,2]
解释: 输入中0代表黑色，1代表白色，标粗的元素即为满足条件的最大子方阵

示例2:
输入:
[
   [0,1,1],
   [1,0,1],
   [1,1,0]
]
输出: [0,0,1]

提示：matrix.length == matrix[0].length <= 200
*/

#define SIZE 200
int* findSquare(int** matrix, int matrixSize, int* matrixColSize,
                int* returnSize) {
  int* ret = calloc(3, sizeof(int));

  if (matrixSize == 0 || matrixColSize[0] == 0) {
    return ret;
  }
  *returnSize = 0;
  int col = matrixColSize[0];
  int horzions[SIZE][SIZE];
  memset(horzions, 0, sizeof(horzions));
  int heights[SIZE][SIZE];
  memset(heights, 0, sizeof(heights));

  // 使用horzions二维变量，保存每一行的黑色像素的前缀和
  for (int i = 0; i < matrixSize; i++) {
    horzions[i][0] = (matrix[i][0] == 0) ? 1 : 0;
    for (int j = 1; j < col; j++) {
      horzions[i][j] = horzions[i][j - 1] + ((matrix[i][j] == 0) ? 1 : 0);
    }
  }

  // 使用heights二维变量，保存每一列的黑色像素前缀和
  for (int j = 0; j < col; j++) {
    heights[0][j] = (matrix[0][j] == 0) ? 1 : 0;
    for (int i = 1; i < matrixSize; i++) {
      heights[i][j] = heights[i - 1][j] + ((matrix[i][j] == 0) ? 1 : 0);
    }
  }

  // 当需要求以i,j为起点，方阵为size + 1的四条边时，可以通过求得：
  // 行：
  // horzions[i][j + size] - ((j-1 >= 0) ? horzions[i][j - 1] : 0);
  // horzions[i + size][j + size] - ((j-1 >= 0) ? horzions[i + size][j - 1] : 0)
  // 列：
  // heights[i+ size][j] - ((i-1 >= 0) ? heights[i-1][j] : 0);
  // heights[i+ size][j + size] - ((i-1 >= 0) ? heights[i - 1][j + size] : 0);

  for (int i = matrixSize - 1; i >= 0; i--) {
    for (int j = col - 1; j >= 0; j--) {
      for (int size = 0; size + i < matrixSize && size + j < col; size++) {
        int newSize;
        newSize =
            horzions[i][j + size] - ((j - 1 >= 0) ? horzions[i][j - 1] : 0);
        if (newSize != size + 1) {
          continue;
        }
        newSize = horzions[i + size][j + size] -
                  ((j - 1 >= 0) ? horzions[i + size][j - 1] : 0);
        if (newSize != size + 1) {
          continue;
        }
        newSize = heights[i + size][j] - ((i - 1 >= 0) ? heights[i - 1][j] : 0);
        if (newSize != size + 1) {
          continue;
        }
        newSize = heights[i + size][j + size] -
                  ((i - 1 >= 0) ? heights[i - 1][j + size] : 0);
        if (newSize != size + 1) {
          continue;
        }
        if (size + 1 >= ret[2]) {
          ret[0] = i;
          ret[1] = j;
          ret[2] = size + 1;
          *returnSize = 3;
        }
      }
    }
  }

  return ret;
}