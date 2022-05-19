/*
两个(具有不同单词的)文档的交集(intersection)中元素的个数除以并集(union)中元素的个数，就是这两个文档的相似度。
例如，{1, 5, 3}和{1, 7, 2, 3}的相似度是0.4，其中，交集的元素有2个，并集的元素有5个。
给定一系列的长篇文档，每个文档元素各不相同，并与一个ID相关联。
它们的相似度非常“稀疏”，也就是说任选2个文档，相似度都很接近0。
请设计一个算法返回每对文档的ID及其相似度。只需输出相似度大于0的组合。请忽略空文档。
为简单起见，可以假定每个文档由一个含有不同整数的数组表示。
输入为一个二维数组docs，docs[i]表示id为 的文档。
返回一个数组，其中每个元素是一个字符串，代表每对相似度大于0的文档，
其格式为{id1},{id2}:{similarity}，其中id1为两个文档中较小的id，similarity为相似度，精确到小数点后4位。
以任意顺序返回数组均可。

示例:
输入: 
[
  [14, 15, 100, 9, 3],
  [32, 1, 9, 3, 5],
  [15, 29, 2, 6, 8, 7],
  [7, 10]
]
输出:
[
  "0,1: 0.2500",
  "0,2: 0.1000",
  "2,3: 0.1429"
]

提示：
docs.length <= 500
docs[i].length <= 500
*/

// 冒泡排序
void bubbleSorted(int *nums, int size) {
  int i, j, temp;
  int flag;
  for (i = 0; i < size - 1; i++) {
    flag = 1;
    for (j = 0; j < size - 1 - i; j++) {
      if (nums[j] > nums[j + 1]) {
        temp = nums[j];
        nums[j] = nums[j + 1];
        nums[j + 1] = temp;
        flag = 0;
      }
    }
    if (flag == 1) {
      break;
    }
  }
}
int intersection(int *a, int *b, int sizeA, int sizeB) {
  int equalCount = 0;
  int i, j;
  for (i = 0, j = 0; i < sizeA && j < sizeB;) {
    if (a[i] > b[j]) {
      j++;
    } else if (a[i] < b[j]) {
      i++;
    } else {
      equalCount++;
      i++;
      j++;
    }
  }
  return equalCount;
}
char **computeSimilarities(int **docs, int docsSize, int *docsColSize,
                           int *returnSize) {
  int i, j;
  int rtn = 0;
  // 分配内存
  char **r = malloc(sizeof(char *) * docsSize * (docsSize - 1) / 2);
  memset(r, 0, sizeof(char *) * docsSize * (docsSize - 1) / 2);
  // 排序
  for (i = 0; i < docsSize; i++) {
    bubbleSorted(docs[i], docsColSize[i]);
  }
  // 当前文件与其他文件比较
  for (i = 0; i < docsSize - 1; i++) {
    for (j = i + 1; j < docsSize; j++) {
      int a = intersection(docs[i], docs[j], docsColSize[i], docsColSize[j]);
      int b = docsColSize[i] + docsColSize[j] - a;
      if (a > 0 && b != 0) {
        char *ss = (char *)malloc(30);
        memset(ss, 0, 30);
        sprintf(ss, "%d,%d: %.4f", i, j, a * 1.0 / b + 1e-9);  // 结果加上1e-9
        r[rtn++] = ss;
      }
    }
  }
  *returnSize = rtn;
  // 根据结果重新分配内存大小。
  r = realloc(r, sizeof(char *) * rtn);
  return r;
}