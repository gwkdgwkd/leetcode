/*
编写函数，实现许多图片编辑软件都支持的颜色填充功能。
待填充的图像用二维数组image表示，元素为初始颜色值。
初始坐标点的行坐标为sr列坐标为sc。需要填充的新颜色为newColor。
周围区域是指颜色相同且在上、下、左、右四个方向上存在相连情况的若干元素。
请用新颜色填充初始坐标点的周围区域，并返回填充后的图像。

示例：
输入：
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
输出：[[2,2,2],[2,2,0],[2,0,1]]
解释:
初始坐标点位于图像的正中间，坐标(sr,sc)=(1,1)。
初始坐标点周围区域上所有符合条件的像素点的颜色都被更改成2。
注意，右下角的像素没有更改为2，因为它不属于初始坐标点的周围区域。

提示：
image和image[0]的长度均在范围[1,50]内。
初始坐标点(sr,sc)满足0<=sr<image.length和0<=sc<image[0].length。
image[i][j]和newColor表示的颜色值在范围[0,65535]内。
*/

void dfs(int** image, int rowSize, int colSize, int r, int c, int newColor,
         int oldColor) {
  if (r < 0 || c < 0 || r >= rowSize || c >= colSize) {
    return;
  }
  int color = image[r][c];
  if (color == oldColor && color != newColor) {
    image[r][c] = newColor;
    dfs(image, rowSize, colSize, r - 1, c, newColor, oldColor);  // 上
    dfs(image, rowSize, colSize, r + 1, c, newColor, oldColor);  // 下
    dfs(image, rowSize, colSize, r, c - 1, newColor, oldColor);  // 左
    dfs(image, rowSize, colSize, r, c + 1, newColor, oldColor);  // 右
  }
}
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
                int newColor, int* returnSize, int** returnColumnSizes) {
  dfs(image, imageSize, imageColSize[0], sr, sc, newColor, image[sr][sc]);
  *returnSize = imageSize;
  *returnColumnSizes = imageColSize;
  return image;
}

class Solution {
 public:
  void dfs(vector<vector<int>>& image, int r, int c, int oldColor,
           int newColor) {
    if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size()) {
      return;
    }
    int color = image[r][c];
    if (color == oldColor && color != newColor) {
      image[r][c] = newColor;
      dfs(image, r + 1, c, oldColor, newColor);
      dfs(image, r - 1, c, oldColor, newColor);
      dfs(image, r, c + 1, oldColor, newColor);
      dfs(image, r, c - 1, oldColor, newColor);
    }
  }
  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                int newColor) {
    dfs(image, sr, sc, image[sr][sc], newColor);
    return image;
  }
};