/*
正在使用一堆木板建造跳水板，有两种类型的木板，其中长度较短的木板长度为shorter，
长度较长的木板长度为longer，必须正好使用k块木板。
编写一个方法，生成跳水板所有可能的长度，返回的长度需要从小到大排列。

示例1
输入：
shorter = 1
longer = 2
k = 3
输出：[3,4,5,6]
解释：
可以使用3次shorter，得到结果3；
使用2次shorter和1次longer，得到结果4。
以此类推，得到最终结果。

提示：
0 < shorter <= longer
0 <= k <= 100000
*/

int* divingBoard(int shorter, int longer, int k, int* returnSize) {
  if (k == 0) {
    *returnSize = 0;
    return NULL;
  }
  if (shorter == longer) {
    int* p = (int*)malloc(sizeof(int));
    *p = shorter * k;
    *returnSize = 1;
    return p;
  }
  *returnSize = k + 1;
  int* lengths = (int*)malloc(sizeof(int) * (k + 1));
  for (int i = 0; i <= k; ++i) {
    lengths[i] = shorter * (k - i) + longer * i;
  }
  return lengths;
}

class Solution {
 public:
  vector<int> divingBoard(int shorter, int longer, int k) {
    if (k == 0) {
      return vector<int>();
    }

    if (shorter == longer) {
      return vector<int>(1, shorter * k);
    }

    vector<int> ans(k + 1);
    for (int i = 0; i <= k; ++i) {
      ans[i] = shorter * (k - i) + longer * i;
    }

    return ans;
  }
};